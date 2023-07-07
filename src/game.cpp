#include <iostream>
#include <SFML/Graphics.hpp>

#include "fontlibrary.hpp"
#include "texturelibrary.hpp"
#include "game.hpp"

bool Game::init() {
    bool success = true;

    FontLibrary& fontLibrary = FontLibrary::getInstance();
    success &= fontLibrary.loadFont("VT", "res/VT323-Regular.ttf");

    TextureLibrary& textureLibrary = TextureLibrary::getInstance();
    success &= textureLibrary.loadTexture("square", "res/square.png");

    return success;
}

void Game::play() {
    auto window = sf::RenderWindow{ { 600u, 480u }, "CMake SFML Project" };
    window.setVerticalSyncEnabled(true);
    bool grabbed = false;

    FontLibrary& fontLibrary = FontLibrary::getInstance();
    TextureLibrary& textureLibrary = TextureLibrary::getInstance();

    sf::Text text("Hello!", fontLibrary.getFont("VT"), 50U);
    text.setPosition({ 100, 100 });
    text.setFillColor(sf::Color::White);

    sf::Sprite sprite(textureLibrary.getTexture("square"));
    sprite.setPosition({ 300, 300 });
    sprite.setScale({ 3, 3 });
    sprite.setOrigin({ 8.0f, 8.0f });

    sf::Clock time;

    while (window.isOpen())
    {
        float delta = time.restart().asSeconds();

        window.requestFocus();

        for (auto event = sf::Event{}; window.pollEvent(event);)
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }

            if (event.type == sf::Event::MouseButtonPressed) {
                window.setMouseCursorGrabbed(!grabbed);
                grabbed = !grabbed;
            }
        }

        window.clear();

        window.draw(text);
        sprite.rotate(50.0f * delta);
        window.draw(sprite);

        window.display();
    }
}