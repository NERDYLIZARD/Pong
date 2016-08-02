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

		ball->reset(WIDTH / 2.f, HEIGHT / 2.f);
		paddle1->reset(20.f, HEIGHT / 2.f);
		paddle2->reset(WIDTH - 20.f, HEIGHT / 2.f);

		if (timeSinceReGame < 0.5f) return;
		
		timeSinceReGame = 0.f;
		isAPoint = false;
	}


// AI
	// deadline = -160; if visibility > -160 then there is 
		// posibility that it will fail
	
	int full_board_visibility = -(GamePanel::WIDTH / 2);
	int half_board_visibility = 0;
	int quarter_board_visibility = GamePanel::WIDTH / 4;
	int testAI = quarter_board_visibility;
	
	// right paddle
	if (ball->getX() >= GamePanel::WIDTH / 2 + testAI
		&& ball->getVelX() > 0)
	{
		if (ball->getY() <= paddle2->getY() )
			paddle2->setDirectionUp(true);
		else
			paddle2->setDirectionUp(false);

		if (ball->getY() > paddle2->getY() )
			paddle2->setDirectionDown(true);
		else
			paddle2->setDirectionDown(false);
	}

	//	left paddle
	else if (ball->getX() < GamePanel::WIDTH / 2 - testAI
		&& ball->getVelX() < 0)
	{
		if (ball->getTop() < paddle1->getTop() ) 
			paddle1->setDirectionUp(true);
		else
			paddle1->setDirectionUp(false);

		if (ball->getBottom() > paddle1->getBottom() )
			paddle1->setDirectionDown(true);
		else
			paddle1->setDirectionDown(false);
	}

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
		paddle1->resetDirection();
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
		paddle2->resetDirection();

	}

	paddle1->update(deltaTime);
	paddle2->update(deltaTime);
	ball->update(deltaTime);

}

void GamePanel::render() {
	window.clear();
	
	renderField();
	renderScoreBoard();
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

void GamePanel::renderField() {
	sf::CircleShape midCircle;
	sf::RectangleShape midLine;

	float r = 70.f;
	midCircle.setRadius(r);
	midCircle.setOrigin(r, r);
	midCircle.setPosition(WIDTH / 2, HEIGHT / 2);
	midCircle.setFillColor(sf::Color::Black);
	midCircle.setOutlineThickness(5);

	float w = 5.f, h = HEIGHT;
	midLine.setSize(sf::Vector2f(w, h));
	midLine.setOrigin(w / 2, h / 2);
	midLine.setPosition(WIDTH / 2, HEIGHT / 2);

	window.draw(midCircle);
	window.draw(midLine);
}

void GamePanel::renderScoreBoard() {
	sf::Text scoreTextLeft;
	sf::Text scoreTextRight;
	
	sf::Font font;
	font.loadFromFile("Resources/Sansation_Regular.ttf");

	scoreTextLeft.setFont(font);
	scoreTextLeft.setCharacterSize(40);
	scoreTextLeft.setPosition(GamePanel::WIDTH / 4.f, 10.f);
	scoreTextLeft.setString(std::to_string(paddle1->getScore()));

	scoreTextRight.setFont(font);
	scoreTextRight.setCharacterSize(40);
	scoreTextRight.setPosition(GamePanel::WIDTH - GamePanel::WIDTH / 4.f, 10.f);
	scoreTextRight.setString(std::to_string((long)paddle2->getScore()));

	window.draw(scoreTextLeft);
	window.draw(scoreTextRight);

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
			paddle1->setDirectionUp(true);
		else
			paddle1->setDirectionUp(false);
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
			paddle1->setDirectionDown(true);
		else
			paddle1->setDirectionDown(false);

		// right paddle input
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::O))
			paddle2->setDirectionUp(true);
		else
			paddle2->setDirectionUp(false);
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::L))
			paddle2->setDirectionDown(true);
		else
			paddle2->setDirectionDown(false);

	}

}



