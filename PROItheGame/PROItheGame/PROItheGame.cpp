#include <SDL.h>
#undef main

#include <iostream>

#include "BasicFunctions.h"


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


	TreeElement* root = new TreeElement(&MenuObject::print, &MenuObject::checkIfClicked, new MenuObject()); //initializing first element of the tree
	
	Tree* myTree = new Tree(root); //initializing tree


	//main menu
	myTree->add(new TreeElement(&MenuObject::print, &MenuObject::checkIfClicked, new MenuObject(menuElementHeight, menuElementWidth, "PLAY")));
	myTree->add(new TreeElement(&MenuObject::print, &MenuObject::checkIfClicked, new MenuObject(menuElementHeight, menuElementWidth, "OPTIONS")));


	myTree->goTo(0); //go to "Play"
	
	//level choice menu
	myTree->add(new TreeElement(&MenuObject::print, &MenuObject::checkIfClicked, new MenuObject(menuElementHeight, menuElementWidth, "LEVEL 1"), ID_LEVEL_1));
	myTree->add(new TreeElement(&MenuObject::print, &MenuObject::checkIfClicked, new MenuObject(menuElementHeight, menuElementWidth, "LEVEL 2"), ID_LEVEL_2));
	myTree->add(new TreeElement(&MenuObject::print, &MenuObject::checkIfClicked, new MenuObject(menuElementHeight, menuElementWidth, "LEVEL 3"), ID_LEVEL_3));

	myTree->goTo(-1); //go back

	myTree->goTo(1); //go to "Options"
	
	//options menu
	myTree->add(new TreeElement(&MenuObject::print, &MenuObject::checkIfClicked, new MenuObject(menuElementHeight, menuElementWidth, "CONTROLS"), ID_CONTROLS));

	myTree->goTo(-1); //go back


	



	bool quit = false;
	SDL_Event myEvent;

	clear(renderer);
	myTree->update(renderer);

	while (!quit)
	{
		while (SDL_PollEvent(&myEvent) != 0)
		{
			if (myEvent.type == SDL_QUIT) //quit
				quit = true;
			else if (myEvent.type == SDL_MOUSEBUTTONDOWN) //get mouse click
			{
				int x;
				int y;
				
				SDL_GetMouseState(&x, &y); //get mouse coordinates

				int indexOfClicked = myTree->checkInput(x, y);
				
				if (indexOfClicked != -1) //go down
				{
					myTree->goTo(indexOfClicked);
					
					clear(renderer);
					myTree->update(renderer);

				}
			}
			else if (myEvent.type == SDL_KEYDOWN)
			{
				if (myEvent.key.keysym.sym == SDLK_ESCAPE) //escape - go back
				{
					myTree->goTo(-1);

					clear(renderer);
					myTree->update(renderer);

				}
			}
		}
	}

	return 0;
}

