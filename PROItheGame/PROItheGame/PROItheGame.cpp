#include <SDL.h>
#undef main

#include <iostream>

#include "Game.h"


using namespace std;

int main()
{
	const double FPS = 60;
	const double TIME_BETWEEN_FRAMES = 1000 / FPS;

	const int SCREEN_HEIGHT = 480;
	const int SCREEN_WIDTH = 640;


	const int MENU_ELEMENT_HEIGHT = 50;
	const int MENU_ELEMENT_WIDTH = 100;


	Game myGame(SCREEN_HEIGHT, SCREEN_WIDTH, MENU_ELEMENT_HEIGHT, MENU_ELEMENT_WIDTH, TIME_BETWEEN_FRAMES);

	myGame.simulateMenu();

	


	
	return 0;
}

