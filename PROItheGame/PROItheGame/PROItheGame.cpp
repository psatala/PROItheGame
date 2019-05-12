#include <SDL.h>
#undef main

#include <iostream>

#include "BasicFunctions.h"
#include "Tree.h"
#include "Macros.h"

using namespace std;

int main()
{
	const double FPS = 60;
	const double TIME_BETWEEN_FRAMES = 1000 / FPS;

	const int SCREEN_HEIGHT = 480;
	const int SCREEN_WIDTH = 640;

	const int PLAYER_HEIGHT = 20;
	const int PLAYER_WIDTH = 20;
	SDL_Window* window = NULL;
	SDL_Renderer* renderer = NULL;

	if (init(&window, &renderer, SCREEN_HEIGHT, SCREEN_WIDTH))
	{
		//playLevel("Levels/Level03.txt", window, renderer, SCREEN_HEIGHT, SCREEN_WIDTH, PLAYER_HEIGHT, PLAYER_WIDTH, TIME_BETWEEN_FRAMES);
		//close();
	}
	



	const int menuElementHeight = 50;
	const int menuElementWidth = 100;

	TreeElement* root = new TreeElement(&MenuObject::print, new MenuObject()); //initializing first element of the tree
	
	Tree* myTree = new Tree(root); //initializing tree


	//main menu
	myTree->add(new TreeElement(&MenuObject::print, new MenuObject(menuElementHeight, menuElementWidth, "Play")));
	myTree->add(new TreeElement(&MenuObject::print, new MenuObject(menuElementHeight, menuElementWidth, "Options")));


	myTree->goTo(0); //go to "Play"
	
	//level choice menu
	myTree->add(new TreeElement(&MenuObject::print, new MenuObject(menuElementHeight, menuElementWidth, "Level 1"), ID_LEVEL_1));
	myTree->add(new TreeElement(&MenuObject::print, new MenuObject(menuElementHeight, menuElementWidth, "Level 2"), ID_LEVEL_2));
	myTree->add(new TreeElement(&MenuObject::print, new MenuObject(menuElementHeight, menuElementWidth, "Level 3"), ID_LEVEL_3));

	myTree->goTo(-1); //go back

	myTree->goTo(1); //go to "Options"
	
	//options menu
	myTree->add(new TreeElement(&MenuObject::print, new MenuObject(menuElementHeight, menuElementWidth, "Controls"), ID_CONTROLS));

	myTree->goTo(-1); //go back

	

	return 0;
}

