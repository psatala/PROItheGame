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
			*renderer = SDL_CreateRenderer(*window, -1, SDL_RENDERER_PRESENTVSYNC);
			if (NULL == *renderer)
			{
				cout << "Error - creaing renderer. SDL returned: " << SDL_GetError();
				success = false;
			}
		}
	}
	return success;
}

void play(SDL_Window* window, SDL_Renderer* renderer, const int SCREEN_HEIGHT, const int SCREEN_WIDTH, const int PLAYER_HEIGHT, const int PLAYER_WIDTH, const double TIME_BETWEEN_FRAMES)
{
	bool quit = false;
	SDL_Event myEvent;

	const double x = 10 / TIME_BETWEEN_FRAMES;
	const double y = -14 / TIME_BETWEEN_FRAMES;
	const double g = 0.4 / (TIME_BETWEEN_FRAMES * TIME_BETWEEN_FRAMES);
	const int tDist = 200;
	const unsigned int tTime = 1000;

	HumanPlayer myPlayer((SCREEN_WIDTH - PLAYER_WIDTH) / 2, (SCREEN_HEIGHT - PLAYER_HEIGHT) / 2, PLAYER_WIDTH, PLAYER_HEIGHT, x, y, g, tDist, tTime);
	


	vector <Obstacle*> myObstacles;
	myObstacles.push_back(&Obstacle((SCREEN_WIDTH - 400) / 2, (SCREEN_HEIGHT - 50) * 5 / 8, 400, 50));
	myObstacles.push_back(&Obstacle(440, 100, 30, 300));
	myObstacles.push_back(&Obstacle(0, SCREEN_HEIGHT - 30, SCREEN_WIDTH, 30));
	myObstacles.push_back(&Obstacle(0, 0, 15, SCREEN_HEIGHT));
	myObstacles.push_back(&Obstacle(SCREEN_WIDTH - 15, 0, 15, SCREEN_HEIGHT));
	myObstacles.push_back(&Obstacle(0, 0, SCREEN_WIDTH, 15));
	myObstacles.push_back(&Obstacle(0, SCREEN_HEIGHT + 300, SCREEN_WIDTH, 400, true));
	

	vector <Enemy*> myEnemies;
	myEnemies.push_back(&Enemy(100, 50, 25, 25, 0.5 * x, 0.5 * y, g, tDist, tTime));
	myEnemies.push_back(&Enemy(50, 420, 30, 30, 0.5 * x, 0.5 * y, g, tDist, tTime));

	Uint32 startTime;
	Uint32 endTime;
	Uint32 delta;



	while (!quit)
	{
		startTime = SDL_GetTicks();

		

		//handling events
		while (SDL_PollEvent(&myEvent) != 0)
		{
			if (myEvent.type == SDL_QUIT)
				quit = true;	
		}


		//applying input for the player
		myPlayer.applyInput(myObstacles);
		
		//applying behaviour for the enemies
		(*myEnemies[0]).applyBehaviour(&Enemy::behaveJump);
		(*myEnemies[1]).applyBehaviour(&Enemy::behaveBounce);

		//updating objects positions
		myPlayer.calculateNextPosition(TIME_BETWEEN_FRAMES);
		(*myEnemies[0]).calculateNextPosition(TIME_BETWEEN_FRAMES);
		(*myEnemies[1]).calculateNextPosition(TIME_BETWEEN_FRAMES);
		
		
		
		//checking collisions
		
		
		//player
		for (vector<Obstacle*>::iterator it = myObstacles.begin(); it != myObstacles.end(); ++it)
			myPlayer.checkCollision(*it);
		
		
		//enemies
		for (vector<Obstacle*>::iterator it = myObstacles.begin(); it != myObstacles.end(); ++it)
			(*myEnemies[0]).checkCollision(*it);
		(*myEnemies[0]).checkCollision(&myPlayer);
		
		for (vector<Obstacle*>::iterator it = myObstacles.begin(); it != myObstacles.end(); ++it)
			(*myEnemies[1]).checkCollision(*it);
		(*myEnemies[1]).checkCollision(&myPlayer);

		
		
		clear(renderer);
		
		//printing
		for (vector<Obstacle*>::iterator it = myObstacles.begin(); it != myObstacles.end(); ++it)
			(**it).print(renderer, &myPlayer);
		(*myEnemies[0]).print(renderer, &myPlayer);
		(*myEnemies[1]).print(renderer, &myPlayer);

		myPlayer.print(renderer);

		SDL_RenderPresent(renderer);


		//waiting for the next frame
		endTime = SDL_GetTicks();
		delta = endTime - startTime;
		if (delta < (unsigned int)TIME_BETWEEN_FRAMES)
			SDL_Delay((unsigned int)TIME_BETWEEN_FRAMES - delta);
	}



}




void clear(SDL_Renderer* rendererToPrintOn)
{
	SDL_SetRenderDrawColor(rendererToPrintOn, 0x00, 0x00, 0x00, 0xFF);
	SDL_RenderClear(rendererToPrintOn);
}