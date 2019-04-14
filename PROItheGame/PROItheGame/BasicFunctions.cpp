#include "BasicFunctions.h"

using namespace std;

bool init(SDL_Window** window, SDL_Renderer** renderer, const int SCREEN_HEIGHT, const int SCREEN_WIDTH)
{
	bool success = true;
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		cout << "Error - initalising SDL. SDL returned: " << SDL_GetError();
		success = false;
	}
	else
	{
		*window = SDL_CreateWindow("SpeedyBoi", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (NULL == *window)
		{
			cout << "Error - creating window. SDL returned: " << SDL_GetError();
			success = false;
		}
		else
		{
			*renderer = SDL_CreateRenderer(*window, -1, SDL_RENDERER_ACCELERATED);
			if (NULL == *renderer)
			{
				cout << "Error - creaing renderer. SDL returned: " << SDL_GetError();
				success = false;
			}
		}
	}
	return success;
}

void play(SDL_Window* window, SDL_Renderer* renderer, const int SCREEN_HEIGHT, const int SCREEN_WIDTH, const int PLAYER_HEIGHT, const int PLAYER_WIDTH, const int TIME_BETWEEN_FRAMES)
{
	bool quit = false;
	SDL_Event myEvent;

	const double x = 0.5;
	const double y = -0.7;
	const double g = 0.001;
	Player myPlayer((SCREEN_WIDTH - PLAYER_WIDTH) / 2, (SCREEN_HEIGHT - PLAYER_HEIGHT) / 2, PLAYER_HEIGHT, PLAYER_WIDTH, x, y, g);
	
	
	Uint32 startTime;
	Uint32 endTime;
	Uint32 delta;

	while (!quit)
	{
		startTime = SDL_GetTicks();
		while (SDL_PollEvent(&myEvent) != 0)
		{
			if (myEvent.type == SDL_QUIT)
				quit = true;
			else if (myEvent.type == SDL_KEYDOWN && myEvent.key.repeat == 0)
			{
				switch (myEvent.key.keysym.sym)
				{
					case SDLK_w:
						myPlayer.jump();
						break;
					case SDLK_d:
						myPlayer.moveRight();
						break;
					case SDLK_a:
						myPlayer.moveLeft();
						break;
				}
			}
			else if (myEvent.type == SDL_KEYUP && myEvent.key.repeat == 0)
			{
				switch (myEvent.key.keysym.sym)
				{
					case SDLK_d:
						myPlayer.getPlayerMomentum()->setXVelocity(0);
						break;
					case SDLK_a:
						myPlayer.getPlayerMomentum()->setXVelocity(0);
						break;
				}
			}
		}
		myPlayer.calculateNextPosition(TIME_BETWEEN_FRAMES);
		myPlayer.printPlayer(renderer);
		SDL_RenderPresent(renderer);

		endTime = SDL_GetTicks();
		delta = endTime - startTime;
		if(delta < TIME_BETWEEN_FRAMES)
			SDL_Delay(TIME_BETWEEN_FRAMES - delta);
	}

	
	/*    Playground    */




	//Player myPlayer(0, (SCREEN_HEIGHT - PLAYER_HEIGHT), PLAYER_HEIGHT, PLAYER_WIDTH, 0.1, -0.7, 0.001);
	/*myPlayer.printPlayer(renderer);
	SDL_RenderPresent(renderer);
	SDL_Delay(5000);*/
	/*myPlayer.jump();
	myPlayer.moveRight();
	for (int i = 0; i < 1000; i++)
	{
		myPlayer.calculateNextPosition(TIME_BETWEEN_FRAMES);
		myPlayer.printPlayer(renderer);
		SDL_RenderPresent(renderer);
		SDL_Delay(TIME_BETWEEN_FRAMES);
	}*/




	/*    End of playground    */
}