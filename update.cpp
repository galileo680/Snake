#include "Engine.h"

void Engine::update() {
	if (timeSinceLastMove.asSeconds() >= seconds(1.f / float(speed)).asSeconds()) {
		Vector2f thisSectionPosition = snake[0].getPosition();
		Vector2f lastSectionPosition = thisSectionPosition;

		
		if (!directionQueue.empty()) {
			// sprawdzamy czy snake nie obroci sie o 180 stopni
			switch (snakeDirection) {
			case Direction::UP:
				if (directionQueue.front() != Direction::DOWN) {
					snakeDirection = directionQueue.front();
				}
				break;
			case Direction::DOWN:
				if (directionQueue.front() != Direction::UP) {
					snakeDirection = directionQueue.front();
				}
				break;
			case Direction::LEFT:
				if (directionQueue.front() != Direction::RIGHT) {
					snakeDirection = directionQueue.front();
				}
				break;
			case Direction::RIGHT:
				if (directionQueue.front() != Direction::LEFT) {
					snakeDirection = directionQueue.front();
				}
				break;

			}
			directionQueue.pop_front();
		}

		// zwwiekszamy rozmiar snake'a
		if (sectionsToAdd) {
			addSnakeSection();
			sectionsToAdd--;
		}


		// aktualizujemy pozycje glowy snake'a
		switch (snakeDirection) {
		case Direction::RIGHT:
			snake[0].setPosition(Vector2f(thisSectionPosition.x + 20, thisSectionPosition.y));
			break;
		case Direction::DOWN:
			snake[0].setPosition(Vector2f(thisSectionPosition.x, thisSectionPosition.y + 20));
			break;
		case Direction::LEFT:
			snake[0].setPosition(Vector2f(thisSectionPosition.x - 20, thisSectionPosition.y));
			break;
		case Direction::UP:
			snake[0].setPosition(Vector2f(thisSectionPosition.x, thisSectionPosition.y - 20));
			break;
		}

		// aktualizujemy reszte ciala (petla for przesuwamy kazdy element(section) w odpowiednim kierunku)
		for (int s = 1; s < snake.size(); s++) {
			thisSectionPosition = snake[s].getPosition();
			snake[s].setPosition(lastSectionPosition);
			lastSectionPosition = thisSectionPosition;
		}

		for (auto& s : snake) {
			s.update();
		}

		// sprawdzenie czy snake'a zjadl jablko
		if (snake[0].getShape().getGlobalBounds().intersects(apple.getSprite().getGlobalBounds())) {
			// zjedlismy jablko wiec ziwkeszamy rozmiar i wynik
			sectionsToAdd += 4;
			speed++;
			moveApple();
			score++;

		}

		// Badanie kolizji - Snake
		for (int s = 1; s < snake.size(); s++) {
			// Sprawdzenie czy snake nie "zjadl" samego siebie
			if (snake[0].getShape().getGlobalBounds().intersects(snake[s].getShape().getGlobalBounds())) {
				// Game over
				currentGameState = GameState::GAMEOVER;

				std::cout << "!!!GAME OVER!!!" << std::endl;
				std::cout << "Player score: " << score << std::endl;
				std::cout << std::endl;
				std::cout << "Press ESC to leave the game" << std::endl;
				std::cout << std::endl;
				break;
			}
			// Sprawdzenie czy snake nie uderzyl w bariery okna
			else if (snake[0].getPosition().x < 0 || snake[0].getPosition().x >= resolution.x || snake[0].getPosition().y < 0 || snake[0].getPosition().y >= resolution.y) {
				// Game over
				currentGameState = GameState::GAMEOVER;

				std::cout << "!!!GAME OVER!!!" << std::endl;
				std::cout << "Player score: " << score << std::endl;
				std::cout << std::endl;
				std::cout << "Press ESC to leave the game" << std::endl;
				std::cout << std::endl;
				break;
			}
		}

		// Resetujemy czas ktory minal od poprzedniego ruchu
		timeSinceLastMove = Time::Zero;

	} // End update 
}