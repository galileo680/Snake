#include "Engine.h"

void Engine::input() {
	Event event{};

	while (window.pollEvent(event)) {
		// jesli klikniemy X
		if (event.type == Event::Closed) {
			window.close();
		}

		// jesli klikniemy ESC
		if (event.type == Event::KeyPressed) {
			// wyjsice
			if (event.key.code == Keyboard::Escape) {
				window.close();
			}

			// pauza
			if (event.key.code == Keyboard::Pause) {
				togglePause();
			}

			// nowa gra
			if (currentGameState == GameState::GAMEOVER) {
				if (event.key.code == Keyboard::Enter) {
					startTheGame();
				}
			}
		}

		// Kierunek 
		if (event.key.code == Keyboard::Up) {
			addDirection(Direction::UP);
		}
		else if (event.key.code == Keyboard::Down)
		{
			addDirection(Direction::DOWN);
		}
		else if (event.key.code == Keyboard::Left)
		{
			addDirection(Direction::LEFT);
		}
		else if (event.key.code == Keyboard::Right)
		{
			addDirection(Direction::RIGHT);
		}
	}
}

// Dodajemy kierunek do kolejki kierunków
void Engine::addDirection(int newDirection) {
	if (directionQueue.empty()) {
		directionQueue.emplace_back(newDirection);
	}
	else {
		if (directionQueue.back() != newDirection) {
			directionQueue.emplace_back(newDirection);
		}
	}
}