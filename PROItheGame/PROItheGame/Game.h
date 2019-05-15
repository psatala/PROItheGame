#pragma once

#include <SDL.h>
#include <SDL_ttf.h>

#include <fstream>
#include <iostream>
#include <string>

#include "Enemy.h"
#include "HumanPlayer.h"
#include "Macros.h"
#include "Tree.h"


class Game
{
	SDL_Window* window;
	SDL_Renderer* renderer;

	Tree* myTree;
	TreeElement* root;

public:
	bool init(const int SCREEN_HEIGHT, const int SCREEN_WIDTH);

	void initTree();

	void buildTree();

	void handleMenuChoice(int functionID, const double TIME_BETWEEN_FRAMES);

	void showControls();

	void loadLevel(std::string pathToFile, HumanPlayer **myPlayer, std::vector<Obstacle*>*myObstacles, std::vector<Enemy*>*myEnemies, const double TIME_BETWEEN_FRAMES);

	void playLevel(std::string pathToFile, const double TIME_BETWEEN_FRAMES);

	void clear();

	void close();

};