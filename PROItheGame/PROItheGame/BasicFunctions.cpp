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
	
	RectangularEnemy firstEnemy(100, 50, 25, 25, 0.5 * x, 0.5 * y, g, tDist, tTime);
	RectangularEnemy secondEnemy(50, 420, 30, 30, 0.5 * x, 0.5 * y, g, tDist, tTime);

	vector <RectangularObstacle*> myVector;


	myVector.push_back(&RectangularObstacle((SCREEN_WIDTH - 400) / 2, (SCREEN_HEIGHT - 50) * 5 / 8, 400, 50));
	myVector.push_back(&RectangularObstacle(440, 100, 30, 300));
	myVector.push_back(&RectangularObstacle(0, SCREEN_HEIGHT - 30, SCREEN_WIDTH, 30));
	myVector.push_back(&RectangularObstacle(0, 0, 15, SCREEN_HEIGHT));
	myVector.push_back(&RectangularObstacle(SCREEN_WIDTH - 15, 0, 15, SCREEN_HEIGHT));
	myVector.push_back(&RectangularObstacle(0, 0, SCREEN_WIDTH, 15));
	myVector.push_back(&RectangularObstacle(0, SCREEN_HEIGHT + 300, SCREEN_WIDTH, 400, true));
	
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
		myPlayer.applyInput(myVector);
		
		//applying behaviour for the enemies
		firstEnemy.applyBehaviour(&RectangularEnemy::behaveJump);
		secondEnemy.applyBehaviour(&RectangularEnemy::behaveBounce);

		//updating objects positions
		myPlayer.calculateNextPosition(TIME_BETWEEN_FRAMES);
		firstEnemy.calculateNextPosition(TIME_BETWEEN_FRAMES);
		secondEnemy.calculateNextPosition(TIME_BETWEEN_FRAMES);
		
		
		
		//checking collisions
		
		
		//player
		for (vector<RectangularObstacle*>::iterator it = myVector.begin(); it != myVector.end(); ++it)
			myPlayer.checkCollision(*it);
		
		
		//enemies
		for (vector<RectangularObstacle*>::iterator it = myVector.begin(); it != myVector.end(); ++it)
			firstEnemy.checkCollision(*it);
		firstEnemy.checkCollision(&myPlayer);
		
		for (vector<RectangularObstacle*>::iterator it = myVector.begin(); it != myVector.end(); ++it)
			secondEnemy.checkCollision(*it);
		secondEnemy.checkCollision(&myPlayer);

		
		
		clear(renderer);
		
		//printing
		for (vector<RectangularObstacle*>::iterator it = myVector.begin(); it != myVector.end(); ++it)
			(**it).print(renderer, &myPlayer);
		firstEnemy.print(renderer, &myPlayer);
		secondEnemy.print(renderer, &myPlayer);

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