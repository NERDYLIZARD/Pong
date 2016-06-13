#include "GamePanel.h"
#include "Ball.h"
#include "Paddle.h"
#include <iostream>
#include <cmath>

const float Ball::PI = 3.14159265358979f;

Ball::Ball(float x, float y) :
	r(5.f),
	speed(10.f),
	deltaSpeed(600.f),
	angle(30.f),
	maxAngle(60.f),
	vel(speed * cos(toRadians(angle)), speed * sin(toRadians(angle)))
{
	shape.setPosition(x, y);
	shape.setRadius(r);
	shape.setFillColor(sf::Color::Red);
	shape.setOrigin(r, r);
}

float Ball::getX() { return shape.getPosition().x; }
float Ball::getY() { return shape.getPosition().y; }
float Ball::getR() { return r; }
float Ball::getLeft() { return getX() - r; }
float Ball::getRight() { return getX() + r; }
float Ball::getTop() { return getY() - r; }
float Ball::getBottom() { return getY() + r; }
float Ball::getVelX() const
{
	return vel.x;
}
float Ball::getAngle() { return angle; }
float Ball::getMaxAngle() { return maxAngle; }

void Ball::setX(float x) { this->x = x; }
void Ball::setAngle(float angle) { this->angle = angle; }


void Ball::update(float deltaTime) {

	//if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up))
	//	vel.y = -speed;
	//else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down))
	//	vel.y = speed;
	//else
	//	vel.y = 0;
	//
	//if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left))
	//	vel.x = -speed;
	//else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right))
	//	vel.x = speed;
	//else
	//	vel.x = 0;

	if (getLeft() < 0 || getRight() > float(GamePanel::WIDTH)) {
		angle = 180.f - angle;
	}

	if (getTop() < 0 && vel.y < 0) {
		angle = 360.f - angle;
		//y = 1.f;
	}

	if (getBottom() >= float(GamePanel::HEIGHT) && vel.y > 0) {
		angle = 360.f - angle;
		//y = GamePanel::HEIGHT - 1.f;
	}

	vel.x = cos(toRadians(angle)) * deltaSpeed * deltaTime;
	vel.y = sin(toRadians(angle)) * deltaSpeed * deltaTime;

	// x += dx, y += dy
	shape.move(vel);

}

float Ball::toRadians(float angle) {
	return angle * PI / 180.f;
}

void Ball::draw(sf::RenderWindow &window) {
	window.draw(shape);
}

Ball::~Ball()
{

}
