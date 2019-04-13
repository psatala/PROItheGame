#include <SDL.h>
#undef main

#include <iostream>

#include "Player.h"

using namespace std;

int main()
{
	const double timeBetweenFrames = 20;

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
				/*    Playground    */
				
				
				

				Player myPlayer(0, (SCREEN_HEIGHT - PLAYER_HEIGHT), PLAYER_HEIGHT, PLAYER_WIDTH, 0.1, -0.7, 0.001);
				myPlayer.jump();
				myPlayer.moveRight();
				for (int i = 0; i < 1000; i++)
				{
					myPlayer.calculateNextPosition(timeBetweenFrames);
					myPlayer.printPlayer(renderer);
					if (myPlayer.getYCoordinate() <= (SCREEN_HEIGHT - PLAYER_HEIGHT))
					{
						int aa = 0;
						//do sth
					}
					SDL_RenderPresent(renderer);
					SDL_Delay(timeBetweenFrames);
				}




				/*    End of playground    */
			}
			
		}
	}
		


	
	

	return 0;
}

