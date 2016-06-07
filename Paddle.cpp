#include <iostream>
#include "GamePanel.h"
#include "Paddle.h"


Paddle::Paddle(int padNum, float x, float y) :
	width(5.0f),
	height(50.0f),
	speed(10.f),
	vel(0, 0),
	up(false),
	down(false)
{
	this->padNum = padNum;
	if(padNum == 1)
		shape.setPosition(x + width / 2, y + height / 2);
	else if (padNum == 2)
		shape.setPosition(x - width / 2, y - height / 2);

	shape.setOrigin(width / 2, height / 2);
	shape.setSize(sf::Vector2f(width, height));
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

float Paddle::getSpeed() const
{
	return speed;
}

void Paddle::setUp(bool boo) { up = boo; }
void Paddle::setDown(bool boo) { down = boo; }

void Paddle::setVelY(float velY) { this->vel.y = velY;}

int Paddle::getPadNum() const { return padNum; }


void Paddle::update(float delta) {
	if (up && getTop() > 0)
		vel.y = -speed;
	else if (down && getBottom() < GamePanel::HEIGHT)
		vel.y = speed;

	shape.move(vel);
	vel.y = 0;
}

void Paddle::draw(sf::RenderWindow &window) {
	window.draw(shape);
}


Paddle::~Paddle()
{
}


