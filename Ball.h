#pragma once
#include "SFML\Graphics.hpp"

class Paddle;

class Ball
{
	float x;
	float y;
	float r;
	float speed;
	float angle;
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

	void setX(float);
	void setAngle(float);
	
	float toRadians(float);

	void update(float);
	void draw(sf::RenderWindow &window);
	Ball(float, float);
	~Ball();
};
