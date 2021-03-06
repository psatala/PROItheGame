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
#include "MenuObject.h"
#include "GameArea.h"


class Game
{
	SDL_Window* window;  //window to render to
	SDL_Renderer* renderer; //renderer to print on

	Tree<MenuObject>* myMenu = new Tree<MenuObject>(); //menu structure

	
	const double TIME_BETWEEN_FRAMES = 0;

	const int SCREEN_HEIGHT = 0;
	const int SCREEN_WIDTH = 0;

	const int MENU_ELEMENT_HEIGHT = 0;
	const int MENU_ELEMENT_WIDTH = 0;




	///function responsible for initializing SDL2 and  SDL2_ttf, creating a window and a renderer
	///parameters are: height of the screen, width of the screen
	///function returns wether or not the initialization was succcessful
	bool init(const int SCREEN_HEIGHT, const int SCREEN_WIDTH);


	///function responsible for building menu tree
	void buildMenuTree();


	///function responsible for handling user input whilst in menu
	///parameters are: x and y position of mouse click
	///function returns index of clicked element or -1, if no element was clicked
	int checkMenuInput(int x, int y);


	///function responsible for updating menu - printing its content and updating renderer
	void updateMenu();


	///function responsible for showing the game's controls
	void showControls();


	///function responsible for printing text onto the given part of the screen
	///parameters are: text, rectangle in which it will be printed and color of the text
	void printText(std::string text, SDL_Rect myRect, SDL_Color myColor);


	///function responsible for watiting for user to press any key in oreder to progress
	void waitForKeypress();


	///function responsible for loading a level from a text file
	///parameters are: path to the text file, pointer to vector of objects, double pointer to player and game area
	void loadLevel(std::string pathToFile, std::vector<GameObject*> *myObjects, HumanPlayer** myPlayer, GameArea** myGameArea);


	///function responsible for allowing the user to play a level
	///parameters are: path to text file containing information about the level
	void playLevel(std::string pathToFile);


	///function responsible for updating the game's camera
	///parameters are: camera to update, human player to determine the camera
	void updateCamera(Camera* myCamera, HumanPlayer* myPlayer);

public:

	///default constructor
	Game() {}


	///parametrised constructor
	///parameters are: height and width of the screen, height and width of each menu element, time between two frames
	Game(int screenHeight, int screenWidth, int menuHeight, int menuWidth, double timeBetweenFrames) :
		TIME_BETWEEN_FRAMES(timeBetweenFrames), 
		MENU_ELEMENT_HEIGHT(menuHeight), MENU_ELEMENT_WIDTH(menuWidth), 
		SCREEN_HEIGHT(screenHeight), SCREEN_WIDTH(screenWidth)
	{
		if (!init(screenHeight, screenWidth))
			throw "Initialization unsuccessful";
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