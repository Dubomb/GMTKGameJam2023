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
    success &= textureLibrary.loadTexture("message-bg", "res/message-bg.png");
    success &= textureLibrary.loadTexture("schoolbg", "res/levelbackground1.png");
    success &= textureLibrary.loadTexture("bluesticky", "res/bluesticky.png");
    success &= textureLibrary.loadTexture("orangemarker", "res/orangemarker.png");
    success &= textureLibrary.loadTexture("grassblade", "res/grassblade.png");
    success &= textureLibrary.loadTexture("grassbg", "res/levelbackground2.png");
    success &= textureLibrary.loadTexture("rock", "res/rock.png");
    success &= textureLibrary.loadTexture("nightsky", "res/levelbackground3.png");
    success &= textureLibrary.loadTexture("moustache", "res/moustache.png");
    success &= textureLibrary.loadTexture("bedroom", "res/levelbackground4.png");
    success &= textureLibrary.loadTexture("darkgreentrain", "res/darkgreentrain.png");
    success &= textureLibrary.loadTexture("darkgreentraincut", "res/darkgreentraincut.png");
    success &= textureLibrary.loadTexture("flushedemoji", "res/flushedemoji.png");

    Level* levelOne = new Level;
    sf::Sprite sky(textureLibrary.getTexture("nightsky"));
    sky.setPosition(0, 0);
    levelOne->addSprite(sky);
    sf::Sprite moustache(textureLibrary.getTexture("moustache"));
    moustache.setPosition(173, 23);
    levelOne->addSprite(moustache);
    levelOne->setTargetIndex(1);
    levelOne->setTargetSprite(moustache);
    levels.push_back(levelOne);

    Level* levelTwo = new Level;
    sf::Sprite grassbg(textureLibrary.getTexture("grassbg"));
    grassbg.setPosition(0, 0);
    levelTwo->addSprite(grassbg);
    sf::Sprite grassblade(textureLibrary.getTexture("grassblade"));
    grassblade.setPosition(93, 79);
    levelTwo->addSprite(grassblade);
    levelTwo->setTargetIndex(1);
    levelTwo->setTargetSprite(grassblade);
    levels.push_back(levelTwo);

    Level* levelThree = new Level;
    sf::Sprite schoolbg(textureLibrary.getTexture("schoolbg"));
    schoolbg.setPosition(0, 0);
    levelThree->addSprite(schoolbg);
    sf::Sprite blue(textureLibrary.getTexture("bluesticky"));
    blue.setPosition(17, 118);
    levelThree->addSprite(blue);
    levelThree->setTargetIndex(1);
    levelThree->setTargetSprite(blue);
    levels.push_back(levelThree);

    Level* levelFour = new Level;
    grassbg = sf::Sprite(textureLibrary.getTexture("grassbg"));
    grassbg.setPosition(0, 0);
    levelFour->addSprite(grassbg);
    sf::Sprite rock(textureLibrary.getTexture("rock"));
    rock.setPosition(69, 113);
    levelFour->addSprite(rock);
    levelFour->setTargetIndex(1);
    levelFour->setTargetSprite(rock);
    levels.push_back(levelFour);

    Level* levelFive = new Level;
    schoolbg = sf::Sprite(textureLibrary.getTexture("schoolbg"));
    schoolbg.setPosition(0, 0);
    levelFive->addSprite(schoolbg);
    sf::Sprite orange(textureLibrary.getTexture("orangemarker"));
    orange.setPosition(56, 25);
    levelFive->addSprite(orange);
    levelFive->setTargetIndex(1);
    levelFive->setTargetSprite(orange);
    levels.push_back(levelFive);

    Level* levelSix = new Level;
    sf::Sprite bedroom(textureLibrary.getTexture("bedroom"));
    bedroom.setPosition(0, 0);
    levelSix->addSprite(bedroom);
    sf::Sprite train(textureLibrary.getTexture("darkgreentraincut"));
    train.setPosition(145, 107);
    levelSix->addSprite(train);
    levelSix->setTargetIndex(1);
    sf::Sprite trainFull(textureLibrary.getTexture("darkgreentrain"));
    levelSix->setTargetSprite(trainFull);
    levels.push_back(levelSix);

    Level* levelSeven = new Level;
    sky = sf::Sprite(textureLibrary.getTexture("nightsky"));
    sky.setPosition(0, 0);
    levelSeven->addSprite(sky);
    sf::Sprite flushed(textureLibrary.getTexture("flushedemoji"));
    flushed.setPosition(185, 91);
    levelSeven->addSprite(flushed);
    levelSeven->setTargetIndex(1);
    levelSeven->setTargetSprite(flushed);
    levels.push_back(levelSeven);

    return success;
}

void Game::play() {
    sf::Vector2u windowSize(600u, 480u);
    auto window = sf::RenderWindow{ {600u, 480u}, "snapshot", sf::Style::Titlebar | sf::Style::Close };

    FontLibrary& fontLibrary = FontLibrary::getInstance();
    TextureLibrary& textureLibrary = TextureLibrary::getInstance();

    sf::Vector2u fixed = getFixedDesktop();

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

    sf::RenderWindow popupWindow;
    popupWindow.setVerticalSyncEnabled(true);

    sf::Sprite phone(textureLibrary.getTexture("phone"));
    phone.setScale(windowScale, windowScale);

    sf::Sprite background(textureLibrary.getTexture("background"));
    background.setScale(windowScale, windowScale);
    background.setPosition(0, 0);

    sf::View view;
    view.setSize((float)window.getSize().x, (float)window.getSize().y);

    bool exit = false;
    bool lockedMouse = false;
    sf::Vector2i lockedMousePos(0, 0);

    sf::Clock clock;

    currentLevel = -1;

    loadLevel();

    popupWindow.create(sf::VideoMode(48 * windowScale, 32 * windowScale), "New message!", sf::Style::None);
    popupWindow.setPosition(sf::Vector2i(fixedSize.x * 0.85f - 32 * windowScale / 2, fixedSize.y * 0.5f - 48 * windowScale / 2));
    popupWindow.clear();
    sf::RenderTexture* texture = levels[currentLevel]->createPopup();
    popupWindow.draw(sf::Sprite(texture->getTexture()));
    popupWindow.display();
    delete texture;

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

        if (lockedMouse) {
            loadLevel();

            if (currentLevel == levels.size()) {
                break;
            }

            popupWindow.create(sf::VideoMode(48 * windowScale, 32 * windowScale), "New message!", sf::Style::None);
            popupWindow.setPosition(sf::Vector2i(fixedSize.x * 0.85f - 32 * windowScale / 2, fixedSize.y * 0.5f - 48 * windowScale / 2));
            popupWindow.clear();
            texture = levels[currentLevel]->createPopup();
            popupWindow.draw(sf::Sprite(texture->getTexture()));
            popupWindow.display();
            delete texture;

            lockedMouse = false;
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