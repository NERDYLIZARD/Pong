#pragma once
#include "SFML\Graphics.hpp"

class Paddle;

class Ball
{
	float x;
	float y;
	float r;
	float maxSpeed;
	float speed;
	float angle;
	float elapse;
	const static float PI;
	sf::Vector2f vel;
	sf::CircleShape shape;


public:
	float getX();
	float getY();
	float getLeft();
	float getRight();
	float getTop();
	float getBottom();

	float toRadians(float);
	void collideWith(Paddle const &);

	void update(float);
	void draw(sf::RenderWindow &window);
	Ball(float, float);
	~Ball();
};
