#pragma once
#include "SFML\Graphics.hpp"

class Paddle
{
	int score;
	float x;
	float y;
	float width;
	float height;
	float speed;
	float deltaSpeed;

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

	float getSpeed() const;
	int getScore();

	void setUp(bool);
	void setDown(bool);
	void setVelY(float);
	void increaseScore();
	void setPosition(float, float);

	void update(float);
	void draw(sf::RenderWindow&);
	Paddle(float, float);
	~Paddle();
};
