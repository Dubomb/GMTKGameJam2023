#include "displayinfo.hpp"

sf::Vector2u getDesktopSize() {
	return sf::Vector2u{ sf::VideoMode::getDesktopMode().width, sf::VideoMode::getDesktopMode().height };
}

sf::Vector2u getFixedDesktop() {
	sf::Vector2u fixed = getDesktopSize();

	if (fixed.x > fixed.y) {
		fixed.x = fixed.y * 1.778f;
	}
	else {
		fixed.y = std::ceil(fixed.x * 0.5624f);
	}

	return fixed;
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