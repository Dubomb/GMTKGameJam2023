#include <SFML/Graphics.hpp>
#include <cmath>

#include "displayinfo.hpp"

sf::Vector2u getDesktopSize() {
	return sf::Vector2u{ sf::VideoMode::getDesktopMode().width, sf::VideoMode::getDesktopMode().height };
}

sf::Vector2u getFixedDesktop() {
	sf::Vector2u fixed = getDesktopSize();

	if (fixed.x > fixed.y) {
		if (fixed.x / fixed.y < 1.7778f) {
			fixed.y = std::ceil(fixed.x * 0.5624f);
		}

		fixed.x = fixed.y * 1.778f;
	}
	else {
		fixed.y = std::ceil(fixed.x * 0.5624f);
	}

	return fixed;
}

float getScale(sf::Vector2u dim) {
	return (float) dim.x / 256;
}

sf::Vector2i getMousePosition() {
	return sf::Mouse::getPosition();
}

sf::Vector2i getWindowMousePosition(sf::Window& window) {
	return sf::Mouse::getPosition(window);
}

void setMousePosition(sf::Vector2i pos) {
	sf::Mouse::setPosition(pos);
}

void clampMousePosition(sf::Vector2i& clampedMousePos) {
	const sf::Rect<unsigned int> gameRect = { 0u, 0u, 192u, 144u };
	const unsigned int units = 16u;
	float windowScale = getScale(getFixedDesktop());
	if (clampedMousePos.x / windowScale < units) {
		clampedMousePos.x = windowScale * units;
	}
	else if (clampedMousePos.x / windowScale > gameRect.width - units) {
		clampedMousePos.x = windowScale * (gameRect.width - units);
	}

	if (clampedMousePos.y / windowScale < units * 1.778f) {
		clampedMousePos.y = windowScale * units * 1.778f;
	}
	else if (clampedMousePos.y / windowScale > gameRect.height - (units * 1.778f)) {
		clampedMousePos.y = windowScale * (gameRect.height - (units * 1.778f));
	}
}