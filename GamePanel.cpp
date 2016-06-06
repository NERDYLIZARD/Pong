#include <iostream>
#include "GamePanel.h"
// ball.h & paddle.h are required for func dec.
// forward dec in .h only determine the size of obj i.e data member
#include "Ball.h"
#include "Paddle.h"

sf::RenderWindow GamePanel::window(sf::VideoMode(WIDTH, HEIGHT), "POUNG");

GamePanel::GamePanel():
	pause(false),
	fps(60),
	framecap(1000000.f / fps),
	//interpolation(0.0),
	delta(0.0)
{
	ball = new Ball(WIDTH / 2.f, HEIGHT / 2.f);
	paddle1 = new Paddle(1, 20.f, 20.f);
	paddle2 = new Paddle(2, (float)WIDTH - 20.f + 1000 ,
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
		delta += clock.restart().asMicroseconds() / framecap;
		if (delta >= 1) {
			if (!pause)
				update(clock.restart().asMicroseconds());
			delta--;
			//interpolation = delta;
		}
		render();
	}
}


void GamePanel::update(float deltaTime) {
	// collision
	ball->collideWith(*paddle1);
	ball->collideWith(*paddle2);

	ball->update(deltaTime);
	paddle1->update();
	paddle2->update();
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
	window.setKeyRepeatEnabled(true);


	while (window.pollEvent(event)) {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::LControl))
			pause = !pause;

		if (event.type == sf::Event::Closed
			|| sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape)) {
			window.close();
			break;
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
			paddle1->setUp(true);
		else
			paddle1->setUp(false);

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
			paddle1->setDown(true);
		else
			paddle1->setDown(false);

	}


}
