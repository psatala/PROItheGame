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

void load(string pathToFile, HumanPlayer **myPlayer, vector<Obstacle*>*myObstacles, vector<Enemy*>*myEnemies)
{
	//*myPlayer = &HumanPlayer(0, 0, 0, 0, 0, 0, 0, 0, 0);
	//myObstacles->push_back(&Obstacle());
	fstream myFile;
	myFile.open(pathToFile);

	if (!myFile.is_open())
		throw "Unable to open file!";
	else
	{
		
		char c;
		int xPos;
		int yPos;
		unsigned int width;
		unsigned int height;
		bool canKill;
		double xSpeed;
		double ySpeed;
		double gForce;
		int tDist;
		unsigned int tTime;
		string behaviourType;

		while (!myFile.eof())
		{
			
			myFile >> c >> xPos >> yPos >> width >> height;
			switch (c)
			{
			case 'P': //player
				myFile >> xSpeed >> ySpeed >> gForce >> tDist >> tTime;
				*myPlayer = new HumanPlayer(xPos, yPos, width, height, xSpeed, ySpeed, gForce, tDist, tTime);				
				break;
			case 'O': //obstacle
				myFile >> canKill;
				myObstacles->push_back(new Obstacle(xPos, yPos, width, height, canKill));
				break;
			case 'E': //enemy
				myFile >> xSpeed >> ySpeed >> gForce >> tDist >> tTime >> behaviourType;
				myEnemies->push_back(new Enemy(xPos, yPos, width, height, xSpeed, ySpeed, gForce, tDist, tTime, behaviourType));
				break;
			default:
				cout << "Wrong character\n";
				break;
			}
		}
		myFile.close();
	}
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

	HumanPlayer* myPlayer;
	vector <Obstacle*> myObstacles;
	vector <Enemy*> myEnemies;

	
	try
	{
		load("Levels/Level01.txt", &myPlayer, &myObstacles, &myEnemies);
	}
	catch (string message)
	{
		cerr << message << endl;
	}


	/*HumanPlayer myPlayer((SCREEN_WIDTH - PLAYER_WIDTH) / 2, (SCREEN_HEIGHT - PLAYER_HEIGHT) / 2, PLAYER_WIDTH, PLAYER_HEIGHT, x, y, g, tDist, tTime);

	vector <Obstacle*> myObstacles;
	myObstacles.push_back(&Obstacle((SCREEN_WIDTH - 400) / 2, (SCREEN_HEIGHT - 50) * 5 / 8, 400, 50));
	myObstacles.push_back(&Obstacle(440, 100, 30, 300));
	myObstacles.push_back(&Obstacle(0, SCREEN_HEIGHT - 30, SCREEN_WIDTH, 30));
	myObstacles.push_back(&Obstacle(0, 0, 15, SCREEN_HEIGHT));
	myObstacles.push_back(&Obstacle(SCREEN_WIDTH - 15, 0, 15, SCREEN_HEIGHT));
	myObstacles.push_back(&Obstacle(0, 0, SCREEN_WIDTH, 15));
	myObstacles.push_back(&Obstacle(0, SCREEN_HEIGHT + 300, SCREEN_WIDTH, 400, true));

	vector <Enemy*> myEnemies;
	myEnemies.push_back(&Enemy(100, 50, 25, 25, 0.5 * x, 0.5 * y, g, tDist, tTime, "JUMP"));
	myEnemies.push_back(&Enemy(50, 420, 30, 30, 0.5 * x, 0.5 * y, g, tDist, tTime, "BOUNCE"));
	myEnemies.push_back(&Enemy(0, -200, 150, 150, 0.5 * x, 0.5 * y, g, tDist, tTime));*/

	vector<GameObject*> allObjects(myObstacles.begin(), myObstacles.end());
	vector<GameObject*> auxiliaryVector(myEnemies.begin(), myEnemies.end());
	allObjects.insert(allObjects.end(), auxiliaryVector.begin(), auxiliaryVector.end());



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
		myPlayer->applyInput(allObjects);
		
		//applying behaviour for the enemies
		for(vector <Enemy*>::iterator jt = myEnemies.begin(); jt != myEnemies.end(); ++jt)
			(**jt).applyBehaviour();

		//updating objects positions
		myPlayer->calculateNextPosition(TIME_BETWEEN_FRAMES);
		for (vector <Enemy*>::iterator jt = myEnemies.begin(); jt != myEnemies.end(); ++jt)
			(**jt).calculateNextPosition(TIME_BETWEEN_FRAMES);
		
		
		
		//checking collisions
		
		
		//player
		for (vector<Obstacle*>::iterator it = myObstacles.begin(); it != myObstacles.end(); ++it)
			myPlayer->checkCollision(*it);
		
		
		//enemies
		for (vector <Enemy*>::iterator jt = myEnemies.begin(); jt != myEnemies.end(); ++jt)
		{
			for (vector<Obstacle*>::iterator it = myObstacles.begin(); it != myObstacles.end(); ++it)
				(**jt).checkCollision(*it);
			(**jt).checkCollision(myPlayer);
		}
		

		
		
		clear(renderer);
		
		//printing
		for (vector<Obstacle*>::iterator it = myObstacles.begin(); it != myObstacles.end(); ++it)
			(**it).print(renderer, myPlayer);
		for (vector <Enemy*>::iterator jt = myEnemies.begin(); jt != myEnemies.end(); ++jt)
			(**jt).print(renderer, myPlayer);
		myPlayer->print(renderer);



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