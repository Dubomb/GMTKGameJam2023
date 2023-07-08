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
    playText.setOrigin(playText.getGlobalBounds().width / 2.0f,
            playText.getGlobalBounds().height / 2.0f);
    playText.setPosition(float(windowSize.x * 0.5f), float(windowSize.y * 0.5f));

    sf::Text creditsText("Credits", fontLibrary.getFont("VT"), 64);
    creditsText.setFillColor(sf::Color::White);
    creditsText.setOrigin(creditsText.getGlobalBounds().width / 2.0f, 
            creditsText.getGlobalBounds().height / 2.0f);
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
                    window.setVisible(false);
                    gameLoop();
                    window.setVisible(true);
                }
                else if (creditsText.getGlobalBounds().contains(sf::Vector2f(mousePos))) {
                    window.setVisible(false);
                    openCredits();
                    window.setVisible(true);
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
    sf::Vector2u fixedSize(getFixedDesktop());

    FontLibrary& fontLibrary = FontLibrary::getInstance();
    TextureLibrary& textureLibrary = TextureLibrary::getInstance();

    const int windowScale = 6;

    sf::Vector2u windowSize = sf::Vector2u(fixedSize.y / windowScale, fixedSize.x / windowScale);

    sf::RenderWindow window(sf::VideoMode(windowSize.x, windowSize.y), "", sf::Style::None);
    window.setVerticalSyncEnabled(true);
    window.setVisible(true);
    window.setMouseCursorVisible(false);

    std::cout << "Begin the game!\n";

    bool exit = false;
    bool lockedMouse = true;

    sf::Clock clock;

    while (!exit) {
        for (auto event = sf::Event{}; window.pollEvent(event);) {
            if (event.type == sf::Event::KeyPressed &&
                event.key.scancode == sf::Keyboard::Scan::Escape) {
                exit = true;
            }
        }

        window.clear(sf::Color(255, 255, 255, 255));

        if (lockedMouse) {
            window.setPosition(sf::Vector2i(fixedSize.x / 2 - windowSize.x / 2, fixedSize.y / 2 - windowSize.y / 2));
        }
        else {
            window.setPosition(sf::Vector2i(getMousePosition().x - windowSize.x / 2, getMousePosition().y - windowSize.y / 2));
        }

        window.display();
    }
}

void Game::openCredits() {
    auto window = sf::RenderWindow{ { 600u, 480u }, "Credits", sf::Style::Titlebar };
    window.setVerticalSyncEnabled(true);

    bool exit = false;

    while (!exit) {
        for (auto event = sf::Event{}; window.pollEvent(event);) {
            if (event.type == sf::Event::KeyPressed &&
                        event.key.scancode == sf::Keyboard::Scan::Escape) {
                exit = true;
            }
        }
    }
}