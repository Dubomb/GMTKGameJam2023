#include <iostream>
#include <SFML/Graphics.hpp>

#include "fontlibrary.hpp"

int main()
{
    auto window = sf::RenderWindow{ { 1920u, 1080u }, "CMake SFML Project" };
    window.setVerticalSyncEnabled(true);

    FontLibrary& fontLibrary = FontLibrary::getInstance();

    fontLibrary.loadFont("VT", "res/VT323-Regular.ttf");

    sf::Text text("Hello!", fontLibrary.getFont("VT"), 50U);
    text.setPosition({ 300, 300 });
    text.setFillColor(sf::Color::White);

    while (window.isOpen())
    {
        for (auto event = sf::Event{}; window.pollEvent(event);)
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
        }

        window.clear();

        window.draw(text);

        window.display();
    }
}