#include <SFML/Window.hpp>

sf::Vector2u getDesktopSize();

sf::Vector2u getFixedDesktop();

sf::Vector2i getMousePosition();

sf::Vector2i getWindowMousePosition(sf::Window& window);

void setMousePosition(sf::Vector2i pos);