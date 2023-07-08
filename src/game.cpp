#include <iostream>
#include <SFML/Graphics.hpp>

#include "fontlibrary.hpp"
#include "texturelibrary.hpp"
#include "game.hpp"
#include "displayinfo.hpp"

bool Game::init() {
    bool success = true;

    FontLibrary& fontLibrary = FontLibrary::getInstance();
    success &= fontLibrary.loadFont("VT", "res/VT323-Regular.ttf");

    TextureLibrary& textureLibrary = TextureLibrary::getInstance();
    success &= textureLibrary.loadTexture("square", "res/square.png");

    return success;
}

void Game::play() {
    sf::Vector2u windowSize(600u, 480u);
    auto window = sf::RenderWindow{ {600u, 480u}, "snapshot" };

    FontLibrary& fontLibrary = FontLibrary::getInstance();
    TextureLibrary& textureLibrary = TextureLibrary::getInstance();

    sf::Vector2u fixed = getFixedDesktop();
    std::cout << fixed.x << " " << fixed.y << std::endl;

    sf::Text playText("Play", fontLibrary.getFont("VT"), 64);
    playText.setFillColor(sf::Color::White);
    playText.setOrigin(playText.getGlobalBounds().width / 2.0f, playText.getGlobalBounds().height / 2.0f);
    playText.setPosition(float(windowSize.x * 0.5f), float(windowSize.y * 0.5f));
    sf::Text creditsText("Credits", fontLibrary.getFont("VT"), 64);
    creditsText.setFillColor(sf::Color::White);
    creditsText.setOrigin(creditsText.getGlobalBounds().width / 2.0f, creditsText.getGlobalBounds().height / 2.0f);
    creditsText.setPosition(float(windowSize.x * 0.5f), float(windowSize.y * 0.75f));

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

            if (event.type == sf::Event::MouseButtonPressed &&
                event.mouseButton.button == sf::Mouse::Left) {
                sf::Vector2i mousePos = getWindowMousePosition(window);

                if (playText.getGlobalBounds().contains(sf::Vector2f(mousePos))) {
                    sf::Vector2i windowPos = window.getPosition();
                    window.setPosition({ (int)getDesktopSize().x + 10, (int)getDesktopSize().y + 10 });
                    gameLoop();
                    window.setPosition(windowPos);
                }
                else if (creditsText.getGlobalBounds().contains(sf::Vector2f(mousePos))) {
                    sf::Vector2i windowPos = window.getPosition();
                    window.setPosition({ (int)getDesktopSize().x + 10, (int)getDesktopSize().y + 10 });
                    openCredits();
                    window.setPosition(windowPos);
                }
            }
        }

        window.clear();

        window.draw(playText);
        window.draw(creditsText);

        window.display();
    }

    window.close();
}

void Game::gameLoop() {
    std::cout << "Begin the game!\n";

    _sleep(1000);
}

void Game::openCredits() {
    auto window = sf::RenderWindow{ { 600u, 480u }, "Credits", sf::Style::Titlebar };

    bool exit = false;

    while (!exit) {
        for (auto event = sf::Event{}; window.pollEvent(event);) {
            if (event.type == sf::Event::KeyPressed && event.key.scancode == sf::Keyboard::Scan::Escape) {
                exit = true;
            }
        }
    }
}