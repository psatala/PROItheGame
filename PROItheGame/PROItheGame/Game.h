///Name: Game.h
///Purpose: declaration of Game class, which is responsible for handling the entire application
///Author: Piotr Satala

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
	SDL_Window* window;  //window to render to
	SDL_Renderer* renderer; //renderer to print on


	Tree* myMenu; //menu structure
	TreeElement* menuRoot; //menu root

	
	const double TIME_BETWEEN_FRAMES = 0;

	const int MENU_ELEMENT_HEIGHT = 0;
	const int MENU_ELEMENT_WIDTH = 0;




	///function responsible for initializing SDL2 and  SDL2_ttf, creating a window and a renderer
	///parameters are: height of the screen, width of the screen
	///function returns wether or not the initialization was succcessful
	bool init(const int SCREEN_HEIGHT, const int SCREEN_WIDTH);


	///function responsible for initialising menu
	void initMenu();


	///function responsible for building menu tree
	void buildMenuTree();


	///function responsible for showing the game's controls
	void showControls();


	///function responsible for loading a level from a text file
	///parameters are: path to the text file, double pointer to human player, pointer to vector of obstacles, pointer to vector of enemies
	void loadLevel(std::string pathToFile, HumanPlayer **myPlayer, std::vector<Obstacle*>*myObstacles, std::vector<Enemy*>*myEnemies);


	///function responsible for allowing the user to play a level
	///parameters are: path to text file containing information about the level
	void playLevel(std::string pathToFile);



public:

	///default constructor
	Game() {}


	///parametrised constructor
	///parameters are: height and width of the screen, height and width of each menu element, time between two frames
	Game(int screenHeight, int screenWidth, int menuHeight, int menuWidth, double timeBetweenFrames) :
		TIME_BETWEEN_FRAMES(timeBetweenFrames), MENU_ELEMENT_HEIGHT(menuHeight), MENU_ELEMENT_WIDTH(menuWidth)
	{
		if (!init(screenHeight, screenWidth))
			throw "Initialization unsuccessful";
		initMenu();
		buildMenuTree();
	}



	///destructor
	~Game() { close(); }



	///function responsbile for simulating interaction with the menu
	void simulateMenu();


	///function responsible for responding to user's interaction with the menu
	///parameters are: ID of function returned by element of menu chosen by the user
	void handleMenuChoice(int functionID);


	///function responsible for clearing the screen
	void clear();


	///function responsible for closing the game
	void close();

};