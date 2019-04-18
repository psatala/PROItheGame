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

void play(SDL_Window* window, SDL_Renderer* renderer, const int SCREEN_HEIGHT, const int SCREEN_WIDTH, const int PLAYER_HEIGHT, const int PLAYER_WIDTH, const unsigned int TIME_BETWEEN_FRAMES)
{
	bool quit = false;
	SDL_Event myEvent;

	const double x = 0.5;
	const double y = -0.7;
	const double g = 0.001;

	Player myPlayer((SCREEN_WIDTH - PLAYER_WIDTH) / 2, (SCREEN_HEIGHT - PLAYER_HEIGHT) / 2, PLAYER_HEIGHT, PLAYER_WIDTH, x, y, g);
	RectangularObstacle firstObstacle((SCREEN_WIDTH - 200) / 2, (SCREEN_HEIGHT - 50) * 3 / 4, 50, 200);
	
	
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
		}

		const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);


		if (currentKeyStates[SDL_SCANCODE_W])
			myPlayer.jump();

		if (!currentKeyStates[SDL_SCANCODE_A] && !currentKeyStates[SDL_SCANCODE_D])
			myPlayer.getPlayerMomentum()->setXVelocity(0);
		else if (currentKeyStates[SDL_SCANCODE_A] && !currentKeyStates[SDL_SCANCODE_D])
			myPlayer.moveLeft();
		else if (!currentKeyStates[SDL_SCANCODE_A] && currentKeyStates[SDL_SCANCODE_D])
			myPlayer.moveRight();


		myPlayer.checkCollision(&firstObstacle);
		myPlayer.calculateNextPosition(TIME_BETWEEN_FRAMES);
		
		
		clear(renderer);
		firstObstacle.print(renderer);
		myPlayer.print(renderer);

		SDL_RenderPresent(renderer);

		endTime = SDL_GetTicks();
		delta = endTime - startTime;
		if (delta < TIME_BETWEEN_FRAMES)
			SDL_Delay(TIME_BETWEEN_FRAMES - delta);
	}



}



void clear(SDL_Renderer* rendererToPrintOn)
{
	SDL_SetRenderDrawColor(rendererToPrintOn, 0x00, 0x00, 0x00, 0xFF);
	SDL_RenderClear(rendererToPrintOn);
}