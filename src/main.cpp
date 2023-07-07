#include <iostream>
#include <SFML/Graphics.hpp>

#include "fontlibrary.hpp"
#include "texturelibrary.hpp"
#include "game.hpp"

int main(void)
{
    Game game;

    if (game.init()) {
        game.play();
    }
    else {
        std::cout << "Game failed to initialize!" << '\n';
        return 1;
    }

    return 0;
}