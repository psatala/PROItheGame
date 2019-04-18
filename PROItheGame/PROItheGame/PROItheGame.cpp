#include <SDL.h>
#undef main

#include <iostream>

#include "BasicFunctions.h"

using namespace std;

int main()
{
	const unsigned int TIME_BETWEEN_FRAMES = 20;

	const int SCREEN_HEIGHT = 480;
	const int SCREEN_WIDTH = 640;

	const int PLAYER_HEIGHT = 20;
	const int PLAYER_WIDTH = 20;
	SDL_Window* window = NULL;
	SDL_Renderer* renderer = NULL;

	if (init(&window, &renderer, SCREEN_HEIGHT, SCREEN_WIDTH))
	{
		play(window, renderer, SCREEN_HEIGHT, SCREEN_WIDTH, PLAYER_HEIGHT, PLAYER_WIDTH, TIME_BETWEEN_FRAMES);
		//close();
	}
		


	
	

	return 0;
}

