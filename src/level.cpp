#include "level.hpp"
#include "displayinfo.hpp"
#include "fontlibrary.hpp"
#include "texturelibrary.hpp"
#include <iostream>

void Level::setTargetIndex(int index) {
	targetIndex = index;
	setTargetSprite(sprites[index]);
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

sf::RenderTexture* Level::createPopup() {
	sf::RenderTexture* texture = new sf::RenderTexture;
	float scale = getScale(getFixedDesktop());

	if (!texture->create(messageSize.x * scale, messageSize.y * scale)) {
		return nullptr;
	}

	texture->clear();

	TextureLibrary& tl = TextureLibrary::getInstance();
	sf::Sprite bg(tl.getTexture("message-bg"));
	bg.setScale(scale, scale);
	bg.setPosition(0, 0);
	texture->draw(bg);

	FontLibrary& fl = FontLibrary::getInstance();
	sf::Font font = fl.getFont("VT");
	sf::Text message("Find", font, scale * 6);
	message.setOrigin(message.getGlobalBounds().width * 0.5f, message.getGlobalBounds().height * 0.5f);
	message.setPosition(texture->getSize().x * 0.3f, texture->getSize().y * 0.4f);
	message.setOutlineThickness(2);
	message.setOutlineColor(sf::Color::Black);
	texture->draw(message);

	texture->display();

	return texture;
}

void Level::setTargetSprite(sf::Sprite& sprite) {
	targetSprite = sprite;
}