#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

class Level {
public:
	void setTargetIndex(int index);
	void addSprite(sf::Sprite sprite);
	bool captureTarget(sf::View& view);
	void drawLevel(sf::RenderWindow& window);
private:
	int targetIndex;
	std::vector<sf::Sprite> sprites;
};