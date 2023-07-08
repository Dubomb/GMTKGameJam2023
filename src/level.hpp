#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

class Level {
public:
	void setTargetIndex(int index);
	void addSprite(sf::Sprite sprite);
	bool captureTarget(sf::View& view);
	void drawLevel(sf::RenderWindow& window);
	sf::RenderTexture* createPopup();
private:
	void setTargetSprite(sf::Sprite& sprite);

	int targetIndex;
	std::vector<sf::Sprite> sprites;
	sf::Sprite targetSprite;
	const sf::Vector2i messageSize = { 48, 32 };
};