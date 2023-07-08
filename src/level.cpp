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
	std::cout << targetSprite.getGlobalBounds().left << " " << targetSprite.getGlobalBounds().top << "\n";
	std::cout << targetSprite.getGlobalBounds().width << " " << targetSprite.getGlobalBounds().height << "\n";

	sf::Rect<float> viewRect = { view.getCenter().x - view.getSize().x / 2,
			view.getCenter().y - view.getSize().y / 2,
			view.getSize().x, view.getSize().y };

	std::cout << viewRect.left << " " << viewRect.top << "\n";
	std::cout << viewRect.width << " " << viewRect.height << "\n";

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

	texture->draw(targetSprite);

	FontLibrary& fl = FontLibrary::getInstance();
	sf::Font font = fl.getFont("VT");
	sf::Text message("Find", font, scale * 6);
	message.setOrigin(message.getGlobalBounds().width * 0.5f, message.getGlobalBounds().height * 0.5f);
	message.setPosition(texture->getSize().x * 0.3f, texture->getSize().y * 0.4f);
	message.setOutlineThickness(4);
	message.setOutlineColor(sf::Color::Black);
	texture->draw(message);

	texture->display();

	return texture;
}

void Level::setTargetSprite(sf::Sprite& sprite) {
	float scale = getScale(getFixedDesktop());
	targetSprite = sprite;
	sf::Rect<float> spriteSize = targetSprite.getGlobalBounds();
	sf::Vector2i area(12.8f * scale, 12.8f * scale);
	targetSprite.setScale(area.x * scale / spriteSize.width, area.y * scale / spriteSize.height);
	targetSprite.setPosition(26 * scale, 8 * scale);
}