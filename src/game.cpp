#include <iostream>
#include <SFML/Graphics.hpp>

#include "fontlibrary.hpp"
#include "texturelibrary.hpp"
#include "game.hpp"
#include "displayinfo.hpp"
#include "level.hpp"

bool Game::init() {
    bool success = true;

    FontLibrary& fontLibrary = FontLibrary::getInstance();
    success &= fontLibrary.loadFont("VT", "res/VT323-Regular.ttf");

    TextureLibrary& textureLibrary = TextureLibrary::getInstance();
    success &= textureLibrary.loadTexture("square", "res/square.png");
    success &= textureLibrary.loadTexture("phone", "res/phone.png");
    success &= textureLibrary.loadTexture("background", "res/testbackground.png");

    Level* levelOne = new Level;
    sf::Sprite pic(textureLibrary.getTexture("square"));
    pic.setPosition(0, 0);
    levelOne->addSprite(pic);
    sf::Sprite otherPic(textureLibrary.getTexture("square"));
    otherPic.setPosition(48, 48);
    levelOne->addSprite(otherPic);
    levelOne->setTargetIndex(1);
    levels.push_back(levelOne);

    Level* levelTwo = new Level;
    sf::Sprite anotherPic(textureLibrary.getTexture("square"));
    anotherPic.setPosition(16, 16);
    levelTwo->addSprite(anotherPic);
    levelTwo->setTargetIndex(0);
    levels.push_back(levelTwo);

    return success;
}

void Game::play() {
    sf::Vector2u windowSize(600u, 480u);
    auto window = sf::RenderWindow{ {600u, 480u}, "snapshot", sf::Style::Titlebar | sf::Style::Close };

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
    const sf::Rect<unsigned int> gameRect = { 0u, 0u, 192u, 144u };
    const unsigned int units = 16u;
    sf::Vector2u fixedSize(getFixedDesktop());
    float windowScale = getScale(fixedSize);

    FontLibrary& fontLibrary = FontLibrary::getInstance();
    TextureLibrary& textureLibrary = TextureLibrary::getInstance();

    const int phoneScale = 4;

    sf::Vector2u windowSize = sf::Vector2u(fixedSize.y / phoneScale, fixedSize.x / phoneScale);

    sf::RenderWindow window(sf::VideoMode(windowSize.x, windowSize.y), "", sf::Style::None);
    window.setVerticalSyncEnabled(true);
    window.setVisible(true);
    window.setMouseCursorVisible(false);

    sf::Sprite phone(textureLibrary.getTexture("phone"));
    phone.setScale(windowScale, windowScale);

    sf::Sprite background(textureLibrary.getTexture("background"));
    background.setScale(windowScale, windowScale);
    background.setPosition(0, 0);

    sf::View view;
    view.setSize((float)window.getSize().x, (float)window.getSize().y);

    std::cout << window.getSize().x << " " << window.getSize().y << "\n";

    bool exit = false;
    bool lockedMouse = false;
    sf::Vector2i lockedMousePos(0, 0);

    sf::Clock clock;

    currentLevel = -1;

    loadLevel();

    while (!exit) {

        sf::Vector2i currentMousePos = getMousePosition();
        float delta = clock.restart().asSeconds();

        for (auto event = sf::Event{}; window.pollEvent(event);) {
            if (event.type == sf::Event::KeyPressed &&
                    event.key.scancode == sf::Keyboard::Scan::Escape) {
                exit = true;
            }

            if (event.type == sf::Event::MouseButtonPressed &&
                    event.mouseButton.button == sf::Mouse::Left) {
                lockedMouse = true;
                lockedMousePos = currentMousePos;
                clampMousePosition(lockedMousePos);

                if (levels[currentLevel]->captureTarget(view)) {
                    std::cout << "Captured!\n";
                }

                loadLevel();

                lockedMouse = false;
            }
        }

        window.clear(sf::Color(32, 255, 128, 255));

        if (lockedMouse) {
            window.setPosition(sf::Vector2i(lockedMousePos.x - windowSize.x / 2,
                lockedMousePos.y - windowSize.y / 2));
            view.setCenter((float)lockedMousePos.x, (float)lockedMousePos.y);
            setMousePosition(lockedMousePos);
        }
        else {
            sf::Vector2i clampedMousePos = getMousePosition();
            clampMousePosition(clampedMousePos);

            window.setPosition(sf::Vector2i(clampedMousePos.x - windowSize.x / 2, clampedMousePos.y - windowSize.y / 2));
            view.setCenter(clampedMousePos.x, clampedMousePos.y);
        }

        if (currentLevel == levels.size()) {
            break;
        }

        window.setView(view);
        levels[currentLevel]->drawLevel(window);

        window.setView(window.getDefaultView());
        window.draw(phone);

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

bool Game::loadLevel() {
    currentLevel++;

    return currentLevel == levels.size();
}

Game::~Game() {
    for (int i = 0; i < levels.size(); i++) {
        delete levels[i];
    }
}