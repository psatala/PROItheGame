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

	const double TIME_BETWEEN_FRAMES = 0;

	const int MENU_ELEMENT_HEIGHT = 0;
	const int MENU_ELEMENT_WIDTH = 0;


	
	bool init(const int SCREEN_HEIGHT, const int SCREEN_WIDTH);

	void initTree();

	void buildTree();

	void showControls();

	void loadLevel(std::string pathToFile, HumanPlayer **myPlayer, std::vector<Obstacle*>*myObstacles, std::vector<Enemy*>*myEnemies, const double TIME_BETWEEN_FRAMES);

	void playLevel(std::string pathToFile, const double TIME_BETWEEN_FRAMES);


public:

	Game(int screenHeight, int screenWidth, int menuHeight, int menuWidth, double timeBetweenFrames) :
		TIME_BETWEEN_FRAMES(timeBetweenFrames), MENU_ELEMENT_HEIGHT(menuHeight), MENU_ELEMENT_WIDTH(menuWidth)
	{
		init(screenHeight, screenWidth);
	}

	
	void handleMenuChoice(int functionID, const double TIME_BETWEEN_FRAMES);

	void clear();

	void close();

};