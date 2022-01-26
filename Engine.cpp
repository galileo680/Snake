#include "Engine.h"

const sf::Time Engine::TimePerFrame = seconds(1.f / 60.f);

Engine::Engine() {

	// Tworzenie okna gry o wymiarach 800x600
	resolution = Vector2f(800, 600);
	window.create(VideoMode(resolution.x, resolution.y), "Snake Game", Style::Default);
	window.setFramerateLimit(FPS);

	startTheGame();

}

void Engine::startTheGame() {
	// Inicjalizacja podstawowych zmiennych
	speed = 2;
	snakeDirection = Direction::RIGHT;
	timeSinceLastMove = Time::Zero;
	sectionsToAdd = 0;
	directionQueue.clear();
	newSnake();
	moveApple();
	currentGameState = GameState::RUNNING;
	lastGameState = currentGameState;

	std::cout << "    				 _______  _        _______  _     _______ " << std::endl
		<< "    				(  ____ \( (    /|(  ___  )| \    /\(  ____ \ " << std::endl
		<< "    				| (    \/|  \  ( || (   ) ||  \  / /| (    \/" << std::endl
		<< "    				| (_____ |   \ | || (___) ||  (_/ / | (__    " << std::endl
		<< "    				(_____  )| (\ \) ||  ___  ||   _ (  |  __)" << std::endl
		<< "    				      ) || | \   || (   ) ||  ( \ \ | (      " << std::endl
		<< "    				/\____) || )  \  || )   ( ||  /  \ \| (____/\ " << std::endl
		<< "    				\_______)|/    )_)|/     \||_/    \/(_______/" << std::endl;
	cout << std::endl;
	cout << std::endl;
	std::cout << "					+++++++++NEW GAME+++++++++" << std::endl;

	// std::cout << "Wynik gracza: " << wynik << endl;
	 
}

// Tworzenie nowego snake na poczatku gry
void Engine::newSnake() {
	snake.clear();
	snake.emplace_back(Vector2f(100, 100));
	snake.emplace_back(Vector2f(80, 100));
	snake.emplace_back(Vector2f(60, 100));
}
// Zwikeszenie dlugosci snake'a po zjedzeniu jablka
void Engine::addSnakeSection() {
	Vector2f newSectionPosition = snake[snake.size() - 1].getPosition();
	snake.emplace_back(newSectionPosition);
}

void Engine::moveApple() {
	// gdzie ma pojawic sie jablko (nie moze byc wewnatrz snake'a)
	Vector2f appleResolution = Vector2f(resolution.x / 20 - 2, resolution.y / 20 - 2);
	Vector2f newAppleLocation;
	bool badLocation = false;
	srand(time(nullptr));
	// Szukamy w petli while odpowiedniego miejsca na pojawienie sie jablka
	do {
		badLocation = false;
		newAppleLocation.x = (float)(1 + rand() / ((RAND_MAX) / (int)appleResolution.x)) * 20;
		newAppleLocation.y = (float)(1 + rand() / ((RAND_MAX) / (int)appleResolution.y)) * 20;

		// sprawdzamy czy miejsca wybrane dla jablka nie pokrywa sie z cialem snake'a
		for (auto& s : snake)
		{
			if (s.getShape().getGlobalBounds().intersects(Rect<float>(newAppleLocation.x, newAppleLocation.y, 20, 20))) {
				badLocation = true;
				break;
			}
		}
	} while (badLocation);
	apple.setPosition(newAppleLocation);
}

void Engine::togglePause() {
	if (currentGameState == GameState::RUNNING) {
		lastGameState = currentGameState;
		currentGameState = GameState::PAUSED;
	}
	else if (currentGameState == GameState::PAUSED) {
		currentGameState = lastGameState;
	}
}

void Engine::run() {
	Clock clock;

	// Game loop 
	while (window.isOpen()) {

		Time dt = clock.restart();

		if (currentGameState == GameState::PAUSED || currentGameState == GameState::GAMEOVER) {
			// Spradzamy czy gracz nie odpauzowal gry
			input();

			// Koniec gry 
			if (currentGameState == GameState::GAMEOVER) {
				draw();
			}

			
			continue;
		}

		timeSinceLastMove += dt;

		input();
		update();
		draw();
	}
}
