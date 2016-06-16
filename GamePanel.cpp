#include <iostream>
#include <string>
#include "GamePanel.h"
// ball.h & paddle.h are required for func dec.
// forward dec in .h only determine the size of obj i.e data member
#include "Ball.h"
#include "Paddle.h"

// declare in .cpp as static is a class member (!obj member)
const int GamePanel::WIDTH = 640;
const int GamePanel::HEIGHT = 480;
sf::RenderWindow GamePanel::window(sf::VideoMode(WIDTH, HEIGHT), "POUNG", 
							sf::Style::Default, sf::ContextSettings(24, 8, 4) );
bool GamePanel::isAPoint = false;

GamePanel::GamePanel() :
	pause(false),
	fps(60),
	//framecap(1000000.f / fps),
	framecap(1.f / fps),
	accumulatedTime(0.f),
	timeSinceReGame(0.f),
	elapsed(0.f)
{

	ball = new Ball(WIDTH / 2.f, HEIGHT / 2.f);
	paddle1 = new Paddle(20.f, HEIGHT / 2.f);
	paddle2 = new Paddle((float)WIDTH - 20.f, HEIGHT / 2.f);

	sf::Font font;
	font.loadFromFile("Resources/Sansation_Regular.ttf");

//	ScoreBoard
	scoreTextLeft.setFont(font);
	scoreTextLeft.setCharacterSize(40);
	scoreTextLeft.setPosition(GamePanel::WIDTH / 4.f, 10.f);
	scoreTextLeft.setString(std::to_string(paddle1->getScore()) );

	scoreTextRight.setFont(font);
	scoreTextRight.setCharacterSize(40);
	scoreTextRight.setPosition(GamePanel::WIDTH - GamePanel::WIDTH / 4.f, 10.f);
	scoreTextRight.setString(std::to_string((long)paddle2->getScore()));

// Field
	float r = 70.f;
	circleField.setRadius(r);
	circleField.setOrigin(r, r);
	circleField.setPosition(WIDTH / 2, HEIGHT / 2);
	circleField.setFillColor(sf::Color::Black);
	circleField.setOutlineThickness(5);

	float w = 5.f, h = HEIGHT;
	lineField.setSize(sf::Vector2f(w, h));
	lineField.setOrigin(w/2, h/2);
	lineField.setPosition(WIDTH / 2, HEIGHT/2);
	
	gameLoop();

}

GamePanel::~GamePanel()
{
	delete ball;
	delete paddle1;
	delete paddle2;
}

void GamePanel::gameLoop() {
	sf::Clock clock;

	while (window.isOpen()) {

		input();
		elapsed = clock.restart().asSeconds();
		//accumulatedTime += elapsed;
		//while (accumulatedTime >= framecap) {
		//	if (!pause) {
		//		update(elapsed);
		//	}
		//	accumulatedTime -= framecap;
		//} 
		if (!pause) {
			update(elapsed);
		}
		render();
	}
}


void GamePanel::update(float deltaTime) {


	if(isAPoint) {
		
		timeSinceReGame += deltaTime;
		scoreUp();
		scoreTextLeft.setString(std::to_string((long)paddle1->getScore()));
		scoreTextRight.setString(std::to_string((long)paddle2->getScore()));
		
		ball->setPosition(WIDTH / 2.f, HEIGHT / 2.f);
		ball->setAngle(rand() % 360 + 1);
		paddle1->setPosition(20.f, HEIGHT / 2.f);
		paddle2->setPosition(WIDTH - 20.f, HEIGHT / 2.f);

		if (timeSinceReGame < .5f) return;
		
		timeSinceReGame = 0.f;
		GamePanel::isAPoint = false;
	}

	paddle1->update(deltaTime);
	paddle2->update(deltaTime);
	ball->update(deltaTime);

	// ball-paddle collision
		//left paddle
	if (ball->getLeft() < paddle1->getRight() &&
		ball->getVelX() < 0 &&
		ball->getBottom() >= paddle1->getTop() &&
		ball->getTop() <= paddle1->getBottom())
	{
		// relative with intersecting paddle-ball
			// hit center, ball bounds horizontally
			// hit edges, ball bounds by maxAngle
		float relativeIntersectY = paddle1->getY() - ball->getY();
		float normalizedRelativeIntersectY = relativeIntersectY / (paddle1->getHeight() / 2);
		// minus sign for realistic direction
			// hit bottom, ball bounds down
			// hit top, ball bounds up
		normalizedRelativeIntersectY = -normalizedRelativeIntersectY;
		// normalized: [-1, 1]
		// angle = [-maxAngle, maxAngle]
		ball->setAngle(normalizedRelativeIntersectY * ball->getMaxAngle());
		ball->setX(paddle1->getRight() + ball->getR() + 0.1f);
	}

	// right paddle
	if (ball->getRight() > paddle2->getLeft() &&
		ball->getVelX() > 0 &&
		ball->getBottom() >= paddle2->getTop() &&
		ball->getTop() <= paddle2->getBottom())
	{
		float relativeIntersectY = paddle2->getY() - ball->getY();
		float normalizedRelativeIntersectY = relativeIntersectY / (paddle2->getHeight() / 2);
		normalizedRelativeIntersectY = -normalizedRelativeIntersectY;

		ball->setAngle(180.f - (normalizedRelativeIntersectY * ball->getMaxAngle()));
		ball->setX(paddle2->getLeft() - ball->getR() - 0.1f);
	}

	// AI
		// right paddle
	int testAI = 200;
	if (ball->getX() > GamePanel::WIDTH / 2 + testAI
		&& ball->getX() < GamePanel::WIDTH)
	{
		if (ball->getY() <= paddle2->getY() &&
			ball->getVelX() > 0) {
			paddle2->setUp(true);
		}
		else {
			paddle2->setUp(false);
		}

		if (ball->getY() > paddle2->getY() &&
			ball->getVelX() > 0) {
			paddle2->setDown(true);
		}
		else {
			paddle2->setDown(false);
		}
	}

	//	left paddle
	if (ball->getX() < GamePanel::WIDTH / 2 - testAI)
	{
		if (ball->getTop() < paddle1->getTop() &&
			ball->getVelX() < 0) {
			paddle1->setUp(true);
		}
		else {
			paddle1->setUp(false);
		}

		if (ball->getBottom() > paddle1->getBottom() &&
			ball->getVelX() < 0) {
			paddle1->setDown(true);
		}
		else {
			paddle1->setDown(false);
		}
	}

}

void GamePanel::render() {
	window.clear();
	
	window.draw(scoreTextLeft);
	window.draw(scoreTextRight);
	window.draw(circleField);
	window.draw(lineField);
	ball->draw(window);
	paddle1->draw(window);
	paddle2->draw(window);

	window.display();
}

void GamePanel::scoreUp() {
	if (ball->getX() < GamePanel::WIDTH / 2.f)
		paddle2->increaseScore();
	else if (ball->getX() > GamePanel::WIDTH / 2.f)
		paddle1->increaseScore();
}

void GamePanel::input() {
	sf::Event event;

	while (window.pollEvent(event)) {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::LControl))
			pause = !pause;

		if (event.type == sf::Event::Closed
			|| sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape)) {
			window.close();
			break;
		}

		// left paddle input
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
			paddle1->setUp(true);
		else
			paddle1->setUp(false);
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
			paddle1->setDown(true);
		else
			paddle1->setDown(false);

		// right paddle input
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::O))
			paddle2->setUp(true);
		else
			paddle2->setUp(false);
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::L))
			paddle2->setDown(true);
		else
			paddle2->setDown(false);

	}

}

