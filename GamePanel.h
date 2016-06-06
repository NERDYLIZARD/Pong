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
	float delta;
	//float interpolation;
	Ball *ball;
	Paddle *paddle1;
	Paddle *paddle2;

public:
	static const int WIDTH = 640;
	static const int HEIGHT = 480;
	static sf::RenderWindow window;
public:
	GamePanel();
	~GamePanel();
	void gameLoop();
	void input();
	void update(long long);
	void render();
};
