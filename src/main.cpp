#include <iostream>
#include <SFML/Graphics.hpp>

#include "fontlibrary.hpp"
#include "texturelibrary.hpp"

int main()
{
    auto window = sf::RenderWindow{ { 600u, 480u }, "CMake SFML Project" };
    window.setVerticalSyncEnabled(true);

    FontLibrary& fontLibrary = FontLibrary::getInstance();

    fontLibrary.loadFont("VT", "res/VT323-Regular.ttf");

    sf::Text text("Hello!", fontLibrary.getFont("VT"), 50U);
    text.setPosition({ 300, 300 });
    text.setFillColor(sf::Color::White);

    TextureLibrary& textureLibrary = TextureLibrary::getInstance();

    textureLibrary.loadTexture("square", "res/square.png");

    sf::Sprite sprite(textureLibrary.getTexture("square"));
    sprite.setPosition({ 600, 600 });
    sprite.setScale({ 5, 5 });
    sprite.setOrigin({ 8.0f, 8.0f });

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
        sprite.rotate(0.5f);
        window.draw(sprite);

        window.display();
    }
}