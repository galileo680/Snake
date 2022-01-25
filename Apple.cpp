#include "Apple.h"

Apple::Apple() {
	Vector2f startingPosition(400, 300);
	sprite.setSize(Vector2f(20, 20));
	sprite.setFillColor(Color::Red);
	//
	sprite.setOutlineThickness(.5);
	sprite.setOutlineColor(sf::Color(250, 150, 100));
	//
	sprite.setPosition(startingPosition);
}

void Apple::setPosition(Vector2f newPosition) {
	sprite.setPosition(newPosition);
}

RectangleShape Apple::getSprite() {
	return sprite;
}