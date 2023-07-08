#include "level.hpp"
#include "displayinfo.hpp"
#include <iostream>

void Level::setTargetIndex(int index) {
	targetIndex = index;
}

void Level::addSprite(sf::Sprite sprite) {
	float scale = getScale(getFixedDesktop());
	sprite.setPosition(sprite.getPosition().x * scale, sprite.getPosition().y * scale);
	sprite.setScale(scale, scale);
	sprites.push_back(sprite);
}

bool Level::captureTarget(sf::View& view) {
	sf::Sprite& targetSprite = sprites[targetIndex];

	sf::Rect<float> viewRect = { view.getCenter().x - view.getSize().x / 2,
			view.getCenter().x - view.getSize().x / 2,
			view.getSize().x, view.getSize().y };

	return targetSprite.getGlobalBounds().intersects(viewRect);
}

void Level::drawLevel(sf::RenderWindow& window) {
	for (int i = 0; i < sprites.size(); i++) {
		window.draw(sprites[i]);
	}
}