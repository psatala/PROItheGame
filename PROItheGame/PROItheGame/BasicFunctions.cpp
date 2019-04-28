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
	const int tp = 200;
	const unsigned int tTime = 1000;

	Player myPlayer((SCREEN_WIDTH - PLAYER_WIDTH) / 2, (SCREEN_HEIGHT - PLAYER_HEIGHT) / 2, PLAYER_WIDTH, PLAYER_HEIGHT, x, y, g, PLAYER_WIDTH, PLAYER_HEIGHT);
	RectangularEnemy firstEnemy(100, 50, 25, 25, x, y, g, PLAYER_WIDTH, PLAYER_HEIGHT);

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

		//if (firstEnemy.getYCoordinate() > 244)
		//	int a = 0;

		//handling events
		while (SDL_PollEvent(&myEvent) != 0)
		{
			if (myEvent.type == SDL_QUIT)
				quit = true;	
		}


		//getting and applying input
		const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);
		applyInput(&myPlayer, currentKeyStates, tp, tTime, myVector);
		


		//updating objects positions
		myPlayer.calculateNextPosition(TIME_BETWEEN_FRAMES);
		firstEnemy.calculateNextPosition(TIME_BETWEEN_FRAMES);
		
		//checking collisions
		
		//player
		for (vector<RectangularObstacle*>::iterator it = myVector.begin(); it != myVector.end(); ++it)
			myPlayer.checkCollision(*it);
		//enemies
		for (vector<RectangularObstacle*>::iterator it = myVector.begin(); it != myVector.end(); ++it)
			firstEnemy.checkCollision(*it);
		firstEnemy.checkCollision(&myPlayer);


		clear(renderer);
		
		//printing
		for (vector<RectangularObstacle*>::iterator it = myVector.begin(); it != myVector.end(); ++it)
			(**it).print(renderer, &myPlayer);
		firstEnemy.print(renderer, &myPlayer);
		
		myPlayer.print(renderer);

		SDL_RenderPresent(renderer);


		//waiting for the next frame
		endTime = SDL_GetTicks();
		delta = endTime - startTime;
		if (delta < (unsigned int)TIME_BETWEEN_FRAMES)
			SDL_Delay((unsigned int)TIME_BETWEEN_FRAMES - delta);
	}



}


void applyInput(Player* myPlayer, const Uint8* currentKeyStates, const int teleportDistance, const unsigned int timeBetweenTeleports, vector <RectangularObstacle*> myVector)
{
	//jump
	if (currentKeyStates[SDL_SCANCODE_W])
		myPlayer->jump();
	
	//no horizontal movement
	if (!currentKeyStates[SDL_SCANCODE_A] && !currentKeyStates[SDL_SCANCODE_D])
		myPlayer->getPlayerMomentum()->setXVelocity(0);
	//horizontal movement
	else if (currentKeyStates[SDL_SCANCODE_A] && !currentKeyStates[SDL_SCANCODE_D])
		myPlayer->moveLeft();
	else if (!currentKeyStates[SDL_SCANCODE_A] && currentKeyStates[SDL_SCANCODE_D])
		myPlayer->moveRight();
	
	//teleports
	if (currentKeyStates[SDL_SCANCODE_UP])
		myPlayer->teleport(Player::UP, teleportDistance, timeBetweenTeleports, myVector);
	if (currentKeyStates[SDL_SCANCODE_DOWN])
		myPlayer->teleport(Player::DOWN, teleportDistance, timeBetweenTeleports, myVector);
	if (currentKeyStates[SDL_SCANCODE_LEFT])
		myPlayer->teleport(Player::LEFT, teleportDistance, timeBetweenTeleports, myVector);
	if (currentKeyStates[SDL_SCANCODE_RIGHT])
		myPlayer->teleport(Player::RIGHT, teleportDistance, timeBetweenTeleports, myVector);
}


void clear(SDL_Renderer* rendererToPrintOn)
{
	SDL_SetRenderDrawColor(rendererToPrintOn, 0x00, 0x00, 0x00, 0xFF);
	SDL_RenderClear(rendererToPrintOn);
}