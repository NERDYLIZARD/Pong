#pragma once
#include "SFML\Graphics.hpp"
// Q: why declare here,, why not only include Ball.h in GamePanel.cpp?
// A: declare first, so that compiler will know. Otw, error in GamePanel.cpp due to undeclaration of Ball;
class Ball;
class Paddle;
// compile faster, no unnecessary inclusion
// reduce recompilation chance (tweaking of nasted header)

class GamePanel
{
	bool pause;
	int fps;
	float framecap;
	float elapsed;
	float accumulatedTime;
	float timeSinceReGame;
	//float interpolator;
	Ball *ball;
	Paddle *paddle1;
	Paddle *paddle2;

public:
	static const int WIDTH;
	static const int HEIGHT;
	static sf::RenderWindow window;
	static bool isAPoint;


public:
	GamePanel();
	~GamePanel();
	
	void scoreUp();
	void renderField();
	void renderScoreBoard();

	void gameLoop();
	void input();
	void update(float);
	void render();

};
