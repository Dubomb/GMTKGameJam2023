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
    auto window = sf::RenderWindow{ { 600u, 480u }, "snapshot" };
    window.setVerticalSyncEnabled(true);

    FontLibrary& fontLibrary = FontLibrary::getInstance();
    TextureLibrary& textureLibrary = TextureLibrary::getInstance();

    sf::Clock time;

    bool quit = false;

    while (!quit)
    {
        float delta = time.restart().asSeconds();

        for (auto event = sf::Event{}; window.pollEvent(event);)
        {
            if (event.type == sf::Event::Closed)
            {
                quit = true;
            }
        }

        window.clear();

        window.display();
    }

    window.close();
}