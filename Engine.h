#pragma once

#include "SnakeSection.h"
#include "Apple.h"
#include "SFML/Graphics.hpp"
#include "SFML/Graphics/RectangleShape.hpp"

#include <vector>
#include <deque>

#include <iostream>

using namespace sf;
using namespace std;

class Engine
{
private:
	// Okno 
	Vector2f resolution;
	RenderWindow window;
	const unsigned int FPS = 60;
	static const Time TimePerFrame;

	vector<SnakeSection> snake;

	int snakeDirection;
	deque<int> directionQueue;
	int speed;
	int score = 0;
	int sectionsToAdd; // jak bardzo powiekszyc snake'a

	Apple apple;

	Time timeSinceLastMove;

	int currentGameState;
	int lastGameState;

public:
	enum Direction { UP, RIGHT, DOWN, LEFT};
	enum GameState { RUNNING, PAUSED, GAMEOVER };
	Engine();

	void input();
	void addDirection(int newDirection);
	void update();
	void draw();

	void newSnake();
	void addSnakeSection();

	void moveApple();

	void startTheGame();

	void togglePause();

	// The main loop will be in the run function
	void run();
};

