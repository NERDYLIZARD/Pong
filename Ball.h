#pragma once
#include "SFML\Graphics.hpp"

class Paddle;

class Ball
{
	float x;
	float y;
	float r;
	float speed;
	float deltaSpeed;
	float angle;
	float maxAngle;
	const static float PI;
	sf::Vector2f vel;
	sf::CircleShape shape;


public:
	float getX();
	float getY();
	float getR();
	float getLeft();
	float getRight();
	float getTop();
	float getBottom();
	float getVelX() const;
	float getAngle();
	float getMaxAngle();

	void setX(float);
	void setAngle(float);
	void setPosition(float, float);

	float toRadians(float);

	void update(float);
	void draw(sf::RenderWindow &window);
	Ball(float, float);
	~Ball();
};
