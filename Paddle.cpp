#include <iostream>
#include "GamePanel.h"
#include "Paddle.h"


Paddle::Paddle(float x, float y) :
	width(5.0f),
	height(50.0f),
	speed(10.f),
	deltaSpeed(600.f),
	vel(0.f, 0.f),
	score(0),
	up(false),
	down(false)
{
	shape.setOrigin(width / 2, height / 2);
	shape.setSize(sf::Vector2f(width, height));
	shape.setPosition(x, y);
}

float Paddle::getX() const { return shape.getPosition().x; }
float Paddle::getY() const { return shape.getPosition().y; }

float Paddle::getWidth() const { return width; }
float Paddle::getHeight() const { return height; }

float Paddle::getVelX() const { return vel.x; }
float Paddle::getVelY() const { return vel.y; }


float Paddle::getLeft() const { return getX() - width / 2; }
float Paddle::getRight() const { return getX() + width / 2; }
float Paddle::getTop() const { return getY() - height / 2; }
float Paddle::getBottom() const { return getY() + height / 2; }

float Paddle::getSpeed() const { return speed; }
int Paddle::getScore() {return score;}
void Paddle::increaseScore() {score++;}

void Paddle::setDirectionUp(bool boo) { up = boo; }
void Paddle::setDirectionDown(bool boo) { down = boo; }

void Paddle::setVelY(float velY) { this->vel.y = velY;}

void Paddle::setPosition(float x, float y) {
	shape.setPosition(x, y);
}

void Paddle::update(float deltaTime) {
	if (up && getTop() > 0)
		vel.y = -deltaSpeed * deltaTime;
	else if (down && getBottom() < GamePanel::HEIGHT)
		vel.y = deltaSpeed * deltaTime;

	shape.move(vel);
	vel.y = 0.f;
}

void Paddle::draw(sf::RenderWindow &window) {
	window.draw(shape);
}


Paddle::~Paddle()
{
}

void Paddle::reset(float x, float y)
{
	setPosition(x,y);
	resetDirection();
}

void Paddle::resetDirection()
{
	setDirectionUp(false);
	setDirectionDown(false);
}

