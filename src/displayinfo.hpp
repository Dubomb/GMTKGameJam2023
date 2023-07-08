#pragma once

#include <SFML/Window.hpp>

sf::Vector2u getDesktopSize();

sf::Vector2u getFixedDesktop();

float getScale(sf::Vector2u dim);

sf::Vector2i getMousePosition();

sf::Vector2i getWindowMousePosition(sf::Window& window);

void setMousePosition(sf::Vector2i pos);

void clampMousePosition(sf::Vector2i& clampedMousePos);