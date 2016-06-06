#pragma once
#include "SFML\Graphics.hpp"

class Paddle
{
	int padNum;
	float x;
	float y;
	float width;
	float height;
	float speed;

	bool up;
	bool down;

	sf::RectangleShape shape;
	sf::Vector2f vel;

public:
	float getX() const;
	float getY() const;

	float getWidth() const;
	float getHeight() const;

	float getVelX() const;
	float getVelY() const;

	float getLeft() const;
	float getRight() const;
	float getTop() const;
	float getBottom() const;

	void setUp(bool);
	void setDown(bool);

	int getPadNum() const;

	void update();
	void draw(sf::RenderWindow&);
	Paddle(int, float, float);
	~Paddle();
};
