#pragma once

#include "level.hpp"

class Game {
public:
	~Game();

	bool init();
	void play();

	int currentLevel;
	std::vector<Level*> levels;

private:
	void openMenu();
	void gameLoop();
	void openCredits();
	bool loadLevel();
};