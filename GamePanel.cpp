#include <iostream>
#include "GamePanel.h"
// ball.h & paddle.h are required for func dec.
// forward dec in .h only determine the size of obj i.e data member
#include "Ball.h"
#include "Paddle.h"

// declare in .cpp as static is a class member (!obj member)
const int GamePanel::WIDTH = 640;
const int GamePanel::HEIGHT = 480;
sf::RenderWindow GamePanel::window(sf::VideoMode(WIDTH, HEIGHT), "POUNG");

GamePanel::GamePanel() :
	pause(false),
	fps(60),
	framecap(1000000.f / fps),
	accumulatedTime(0.f),
	//interpolation(0.0),
	delta(0.f)
{
	ball = new Ball(WIDTH / 2.f, HEIGHT / 2.f);
	paddle1 = new Paddle(1, 20.f, 20.f);
	paddle2 = new Paddle(2, (float)WIDTH - 20.f ,
							(float)HEIGHT - 20.f);

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

		delta = clock.restart().asMicroseconds();
		accumulatedTime += delta;
		while (accumulatedTime >= framecap) {
			if (!pause) {
				//std::cout << delta / 1000000.f << '\n';
				update(delta/1000000.f);
			}
			accumulatedTime -= framecap;
			//interpolation = accumulatedTime;
		}
		render();
	}
}


void GamePanel::update(float deltaTime) {

	paddle1->update(deltaTime);
	paddle2->update(deltaTime);
	ball->update(deltaTime);

// ball-paddle collision
	//left paddle
	if (ball->getLeft() < paddle1->getRight() &&
		ball->getVelX() < 0 &&
		ball->getBottom() >= paddle1->getTop() &&
		ball->getTop() <= paddle1->getBottom() )
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
		ball->setAngle( normalizedRelativeIntersectY * ball->getMaxAngle() );
		ball->setX(paddle1->getRight() + ball->getR() + 0.1f);
	}

	// right paddle
	if (ball->getRight() > paddle2->getLeft() &&
		ball->getVelX() > 0 &&
		ball->getBottom() >= paddle2->getTop() && 
		ball->getTop() <= paddle2->getBottom() )
	{
		float relativeIntersectY = paddle2->getY() - ball->getY();
		float normalizedRelativeIntersectY = relativeIntersectY / (paddle2->getHeight()/2);
		normalizedRelativeIntersectY = -normalizedRelativeIntersectY;

		ball->setAngle( 180.f - (normalizedRelativeIntersectY * ball->getMaxAngle()) );
		ball->setX(paddle2->getLeft() - ball->getR() - 0.1f);
	}

// AI
	int testAI = 150;
	if (ball->getX() > GamePanel::WIDTH / 2 + testAI )
	{
		if (ball->getTop() < paddle2->getTop() &&
			ball->getVelX() > 0)  {
			paddle2->setUp(true);
		}
		else {
			paddle2->setUp(false);
		}
		
		if (ball->getBottom() > paddle2->getBottom() &&
			ball->getVelX() > 0)  {
			paddle2->setDown(true);
		}
		else {
			paddle2->setDown(false);
		}
	}

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

	ball->draw(window);
	paddle1->draw(window);
	paddle2->draw(window);

	window.display();
}

void GamePanel::input() {
	sf::Event event;
	//window.setKeyRepeatEnabled(true);

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

