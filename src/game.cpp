#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

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
    success &= textureLibrary.loadTexture("credits", "res/creditsbackground.png");
    success &= textureLibrary.loadTexture("menu", "res/menubackground.png");
    success &= textureLibrary.loadTexture("logo", "res/logo.png");
    success &= textureLibrary.loadTexture("incorrect", "res/incorrect.png");
    success &= textureLibrary.loadTexture("correct", "res/correct.png");
    success &= textureLibrary.loadTexture("results", "res/resultsbackground.png");

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
    train.setPosition(144, 107);
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
    playText.setPosition(float(windowSize.x * 0.5f), float(windowSize.y * 0.6f));
    playText.setOutlineThickness(4);

    sf::Text creditsText("Credits", fontLibrary.getFont("VT"), 64);
    creditsText.setFillColor(sf::Color::White);
    creditsText.setOrigin(creditsText.getGlobalBounds().width / 2.0f, 
            creditsText.getGlobalBounds().height / 2.0f);
    creditsText.setPosition(float(windowSize.x * 0.5f), float(windowSize.y * 0.75f));
    creditsText.setOutlineThickness(4);

    sf::Sprite menubg(textureLibrary.getTexture("menu"));
    menubg.setScale(10, 10);

    sf::Sprite logo(textureLibrary.getTexture("logo"));
    logo.setOrigin(logo.getGlobalBounds().width * 0.5f,
            logo.getGlobalBounds().height * 0.5f);
    logo.setPosition(float(windowSize.x * 0.5f), float(windowSize.y * 0.3f));
    logo.setScale(6, 6);

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

        window.draw(menubg);
        window.draw(logo);
        window.draw(playText);
        window.draw(creditsText);

        window.display();
    }

    window.close();
}

void Game::gameLoop() {
    // Game info
    const sf::Rect<unsigned int> gameRect = { 0u, 0u, 192u, 144u };
    const unsigned int units = 16u;
    sf::Vector2u fixedSize(getFixedDesktop());
    float windowScale = getScale(fixedSize);
    const int phoneScale = 4;

    // Libraries
    FontLibrary& fontLibrary = FontLibrary::getInstance();
    TextureLibrary& textureLibrary = TextureLibrary::getInstance();

    // Windows
    sf::Vector2u windowSize = sf::Vector2u(fixedSize.y / phoneScale, fixedSize.x / phoneScale);

    sf::RenderWindow window(sf::VideoMode(windowSize.x, windowSize.y), "", sf::Style::None);
    window.setVerticalSyncEnabled(true);
    window.setVisible(true);
    window.setMouseCursorVisible(false);

    sf::RenderWindow popupWindow;
    popupWindow.setVerticalSyncEnabled(true);

    // Sprites
    sf::Sprite overlay(textureLibrary.getTexture("square"));
    overlay.setColor(sf::Color(0, 0, 0, 0));
    overlay.setPosition(0, 0);
    overlay.setScale(windowScale, windowScale);

    sf::Sprite phone(textureLibrary.getTexture("phone"));
    phone.setScale(windowScale, windowScale);

    sf::Sprite correct(textureLibrary.getTexture("correct"));
    correct.setOrigin(correct.getGlobalBounds().width * 0.5f,
        correct.getGlobalBounds().height * 0.5f);
    correct.setPosition(windowSize.x * 0.5f, windowSize.y * 0.5f);
    correct.setScale(windowScale, windowScale);
    correct.setColor(sf::Color(255, 255, 255, 0));

    sf::Sprite incorrect(textureLibrary.getTexture("incorrect"));
    incorrect.setOrigin(incorrect.getGlobalBounds().width * 0.5f,
        incorrect.getGlobalBounds().height * 0.5f);
    incorrect.setPosition(windowSize.x * 0.5f, windowSize.y * 0.5f);
    incorrect.setScale(windowScale, windowScale);
    incorrect.setColor(sf::Color(255, 255, 255, 0));

    sf::View view;
    view.setSize((float)window.getSize().x, (float)window.getSize().y);

    // Audio
    sf::Music bgMusic;
    if (!bgMusic.openFromFile("res/celeste.ogg")) {
        return;
    }
    bgMusic.setVolume(80);
    bgMusic.setLoop(true);
    bgMusic.play();

    sf::SoundBuffer snapBuf;
    if (!snapBuf.loadFromFile("res/snap.wav")) {
        return;
    }
    sf::Sound snap(snapBuf);

    // Game state
    bool exit = false;
    bool lockedMouse = false;
    sf::Vector2i lockedMousePos(0, 0);
    int correctCount = 0;
    int incorrectCount = 0;

    // Misc
    sf::Clock clock;

    currentLevel = -1;

    loadLevel();

    popupWindow.create(sf::VideoMode(48 * windowScale, 32 * windowScale), "New message!", sf::Style::None);
    popupWindow.setPosition(sf::Vector2i(fixedSize.x - windowSize.x * 1.5f, fixedSize.y * 0.5f - 48 * windowScale / 2));
    popupWindow.clear();
    sf::RenderTexture* texture = levels[currentLevel]->createPopup();
    popupWindow.draw(sf::Sprite(texture->getTexture()));
    popupWindow.display();
    delete texture;

    const float clickMax = 1.0f;
    float timeSinceClick = 0;

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
                snap.play();
                overlay.setColor(sf::Color(0, 0, 0, 255));
                if (levels[currentLevel]->captureTarget(view)) {
                    correct.setColor(sf::Color(255, 255, 255, 255));
                    incorrect.setColor(sf::Color(255, 255, 255, 0));
                    timeSinceClick = 0;
                    correctCount++;
                }
                else {
                    incorrect.setColor(sf::Color(255, 255, 255, 255));
                    correct.setColor(sf::Color(255, 255, 255, 0));
                    timeSinceClick = 0;
                    incorrectCount++;
                }
            }
        }

        window.clear();

        sf::Vector2i clampedMousePos = getMousePosition();
        clampMousePosition(clampedMousePos);

        window.setPosition(sf::Vector2i(clampedMousePos.x - windowSize.x / 2, clampedMousePos.y - windowSize.y / 2));
        view.setCenter(clampedMousePos.x, clampedMousePos.y);

        if (lockedMouse) {
            loadLevel();

            if (currentLevel == levels.size()) {
                break;
            }

            popupWindow.create(sf::VideoMode(48 * windowScale, 32 * windowScale), "New message!", sf::Style::None);
            popupWindow.setPosition(sf::Vector2i(fixedSize.x - windowSize.x * 1.5f, fixedSize.y * 0.5f - 48 * windowScale / 2));
            popupWindow.clear();
            texture = levels[currentLevel]->createPopup();
            popupWindow.draw(sf::Sprite(texture->getTexture()));
            popupWindow.display();
            delete texture;

            lockedMouse = false;
        }

        window.setView(view);
        levels[currentLevel]->drawLevel(window);

        int a = overlay.getColor().a;
        if (a > 0) {
            window.draw(overlay);
            overlay.setColor(sf::Color(0, 0, 0, std::max(0.0f, a - delta * 1020.0f)));
        }

        window.setView(window.getDefaultView());
        window.draw(phone);

        if (timeSinceClick < clickMax) {
            timeSinceClick += delta;

            if (timeSinceClick > clickMax) {
                correct.setColor(sf::Color(255, 255, 255, 0));
                incorrect.setColor(sf::Color(255, 255, 255, 0));
            }
        }
        window.draw(correct);
        window.draw(incorrect);

        window.display();
    }

    window.close();
    popupWindow.close();

    sf::RenderWindow results(sf::VideoMode(600, 480), "Results!", sf::Style::Titlebar | sf::Style::Close);

    correct.setPosition(150, 200);
    correct.setColor(sf::Color::White);
    incorrect.setPosition(450, 200);
    incorrect.setColor(sf::Color::White);

    sf::Text correctText(std::to_string(correctCount), fontLibrary.getFont("VT"), 64);
    correctText.setOrigin(correctText.getGlobalBounds().width * 0.5f,
        correctText.getGlobalBounds().height * 0.5f);
    correctText.setPosition(150, 340);
    correctText.setOutlineThickness(4);

    sf::Text incorrectText(std::to_string(incorrectCount), fontLibrary.getFont("VT"), 64);
    incorrectText.setOrigin(incorrectText.getGlobalBounds().width * 0.5f,
        incorrectText.getGlobalBounds().height * 0.5f);
    incorrectText.setPosition(450, 340);
    incorrectText.setOutlineThickness(4);

    sf::Sprite resultsbg(textureLibrary.getTexture("results"));
    resultsbg.setPosition(0, 0);
    resultsbg.setScale(10, 10);

    while (results.isOpen()) {
        for (sf::Event event = sf::Event{}; results.pollEvent(event);) {
            if (event.type == sf::Event::Closed) {
                results.close();
            }
        }

        results.clear();

        results.draw(resultsbg);
        results.draw(correct);
        results.draw(incorrect);
        results.draw(correctText);
        results.draw(incorrectText);

        results.display();
    }

    clock.restart();

    while (bgMusic.getVolume() > 0.0f) {
        bgMusic.setVolume(std::max(bgMusic.getVolume() - 200.0f * clock.restart().asSeconds(), 0.0f));
    }

    bgMusic.stop();
}

void Game::openCredits() {
    const sf::Vector2u windowSize(600u, 480u);
    auto window = sf::RenderWindow{ { 600u, 480u }, "Credits", sf::Style::Titlebar };
    window.setVerticalSyncEnabled(true);

    FontLibrary& fl = FontLibrary::getInstance();
    TextureLibrary& tl = TextureLibrary::getInstance();

    sf::Font font = fl.getFont("VT");

    sf::Text programming("Programming: Dubomb", font, 40);
    programming.setOrigin(programming.getGlobalBounds().width * 0.5f,
        programming.getGlobalBounds().height * 0.5f);
    programming.setPosition(windowSize.x * 0.5f, windowSize.y * 0.1f);
    programming.setOutlineThickness(2);

    sf::Text art("Art: Dubomb", font, 40);
    art.setOrigin(art.getGlobalBounds().width * 0.5f,
        art.getGlobalBounds().height * 0.5f);
    art.setPosition(windowSize.x * 0.5f, windowSize.y * 0.3f);
    art.setOutlineThickness(2);

    sf::Text gameDesign("Game Design: Dubomb", font, 40);
    gameDesign.setOrigin(gameDesign.getGlobalBounds().width * 0.5f,
        gameDesign.getGlobalBounds().height * 0.5f);
    gameDesign.setPosition(windowSize.x * 0.5f, windowSize.y * 0.5f);
    gameDesign.setOutlineThickness(2);

    sf::Text soundEffects("Sound Effects: Dubomb", font, 40);
    soundEffects.setOrigin(soundEffects.getGlobalBounds().width * 0.5f,
        soundEffects.getGlobalBounds().height * 0.5f);
    soundEffects.setPosition(windowSize.x * 0.5f, windowSize.y * 0.7f);
    soundEffects.setOutlineThickness(2);

    sf::Text music("Music: Epsidev - Celeste (ft. Artifact & M4N)", font, 32);
    music.setOrigin(music.getGlobalBounds().width * 0.5f,
        music.getGlobalBounds().height * 0.5f);
    music.setPosition(windowSize.x * 0.5f, windowSize.y * 0.9f);
    music.setOutlineThickness(2);
    music.setStyle(sf::Text::Underlined);

    sf::Sprite creditsbg(tl.getTexture("credits"));
    creditsbg.setScale(10, 10);
    creditsbg.setColor(sf::Color(125, 125, 125, 255));

    bool exit = false;

    while (!exit) {
        for (auto event = sf::Event{}; window.pollEvent(event);) {
            if (event.type == sf::Event::KeyPressed &&
                    event.key.scancode == sf::Keyboard::Scan::Escape) {
                exit = true;
            }

            if (event.type == sf::Event::MouseButtonPressed &&
                    event.mouseButton.button == sf::Mouse::Left) {
                if (music.getGlobalBounds().contains(getWindowMousePosition(window).x, getWindowMousePosition(window).y)) {
                    std::string op = "start https://www.youtube.com/watch?v=8JjL1tVnBHw";
                    std::system(op.c_str());
                }
            }
        }

        window.clear();

        window.draw(creditsbg);
        window.draw(programming);
        window.draw(art);
        window.draw(gameDesign);
        window.draw(soundEffects);
        window.draw(music);

        window.display();
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