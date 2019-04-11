#include <SDL.h>
#undef main

#include <iostream>

#include "Player.h"

using namespace std;

int main()
{
	
	const int SCREEN_HEIGHT = 480;
	const int SCREEN_WIDTH = 640;

	const int PLAYER_HEIGHT = 20;
	const int PLAYER_WIDTH = 20;
	SDL_Window* window = NULL;
	SDL_Surface* screenSurface = NULL;
	SDL_Renderer* renderer = NULL;

	if (SDL_Init(SDL_INIT_VIDEO) < 0)
		cout << "Error - initalising SDL. SDL returned: " << SDL_GetError();
	else 
	{	
		cout << "SDL works" << endl;
		window = SDL_CreateWindow("SpeedyBoi", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (NULL == window)
			cout << "Error - creating window. SDL returned: " << SDL_GetError();
		else
		{
			renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
			if (NULL == renderer)
				cout << "Error - creaing renderer. SDL returned: " << SDL_GetError();
			else
			{
				//screenSurface = SDL_GetWindowSurface(window);
				Player myPlayer((SCREEN_WIDTH - PLAYER_WIDTH) / 2, SCREEN_HEIGHT - PLAYER_HEIGHT, PLAYER_HEIGHT, PLAYER_WIDTH, 1, 1);
				myPlayer.printPlayer(renderer);
				SDL_RenderPresent(renderer);
				SDL_Delay(2000);
			}
			
		}
	}
		


	
	

	return 0;
}

