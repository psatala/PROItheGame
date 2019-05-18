///Name: Game.cpp
///Purpose: definition of methods from the Game class
///Author: Piotr Satala


#include "Game.h"



using namespace std;



bool Game::init(const int SCREEN_HEIGHT, const int SCREEN_WIDTH)
{
	bool success = true;

	//SDL init
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		cout << "Error - initialising SDL. SDL returned: " << SDL_GetError() << endl;
		success = false;
	}
	else
	{
		//window init
		window = SDL_CreateWindow("SpeedyBoi", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (NULL == window)
		{
			cout << "Error - creating window. SDL returned: " << SDL_GetError() << endl;
			success = false;
		}
		else
		{
			//renderer init
			renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC);
			if (NULL == renderer)
			{
				cout << "Error - creaing renderer. SDL returned: " << SDL_GetError() << endl;
				success = false;
			}
		}
	}


	//SDL_ttf init
	if (TTF_Init() < 0)
	{
		cout << "Error - initialising SDL_ttf. SDL_ttf retrurned: " << TTF_GetError() << endl;
		success = false;
	}




	return success;
}




void Game::initMenu()
{
	menuRoot = new TreeElement(&MenuObject::print, &MenuObject::checkIfClicked, new MenuObject()); //initializing first element of the tree

	myMenu = new Tree(menuRoot); //initializing tree

}





void Game::buildMenuTree()
{


	//main menu
	myMenu->add(new TreeElement(&MenuObject::print, &MenuObject::checkIfClicked, new MenuObject(MENU_ELEMENT_HEIGHT, MENU_ELEMENT_WIDTH, "PLAY")));
	myMenu->add(new TreeElement(&MenuObject::print, &MenuObject::checkIfClicked, new MenuObject(MENU_ELEMENT_HEIGHT, MENU_ELEMENT_WIDTH, "OPTIONS")));


	myMenu->goTo(0); //go to "Play"

	//level choice menu
	myMenu->add(new TreeElement(&MenuObject::print, &MenuObject::checkIfClicked, new MenuObject(MENU_ELEMENT_HEIGHT, MENU_ELEMENT_WIDTH, "LEVEL 1"), ID_LEVEL_1));
	myMenu->add(new TreeElement(&MenuObject::print, &MenuObject::checkIfClicked, new MenuObject(MENU_ELEMENT_HEIGHT, MENU_ELEMENT_WIDTH, "LEVEL 2"), ID_LEVEL_2));
	myMenu->add(new TreeElement(&MenuObject::print, &MenuObject::checkIfClicked, new MenuObject(MENU_ELEMENT_HEIGHT, MENU_ELEMENT_WIDTH, "LEVEL 3"), ID_LEVEL_3));
	myMenu->add(new TreeElement(&MenuObject::print, &MenuObject::checkIfClicked, new MenuObject(MENU_ELEMENT_HEIGHT, MENU_ELEMENT_WIDTH, "LEVEL 4"), ID_LEVEL_4));

	myMenu->goTo(-1); //go back

	myMenu->goTo(1); //go to "Options"

	//options menu
	myMenu->add(new TreeElement(&MenuObject::print, &MenuObject::checkIfClicked, new MenuObject(MENU_ELEMENT_HEIGHT, MENU_ELEMENT_WIDTH, "CONTROLS"), ID_CONTROLS));

	myMenu->goTo(-1); //go back




}





void Game::simulateMenu()
{
	
	bool quit = false;
	SDL_Event myEvent;


	//print menu's root
	clear();
	myMenu->update(renderer);

	while (!quit)
	{
		while (SDL_PollEvent(&myEvent) != 0)
		{

			//quit
			if (myEvent.type == SDL_QUIT)
				quit = true;


			//get mouse click
			else if (myEvent.type == SDL_MOUSEBUTTONDOWN)
			{
				int x;
				int y;

				SDL_GetMouseState(&x, &y); //get mouse coordinates

				int indexOfClicked = myMenu->checkInput(x, y);

				if (indexOfClicked != -1) //go down
				{
					myMenu->goTo(indexOfClicked);

					handleMenuChoice(myMenu->tryReturning()); //try to call a function
					
					clear();
					myMenu->update(renderer);

				}
			}


			//escape - go back
			else if (myEvent.type == SDL_KEYDOWN)
			{
				if (myEvent.key.keysym.sym == SDLK_ESCAPE) 
				{
					myMenu->goTo(-1);

					clear();
					myMenu->update(renderer);

				}
			}
		}
	}

}





void Game::handleMenuChoice(int functionID)
{

	//call a function based on value of functionID
	switch (functionID)
	{

	case ID_LEVEL_1:
		playLevel("Levels/Level01.txt");
		myMenu->goTo(-1);
		break;
	
	case ID_LEVEL_2:
		playLevel("Levels/Level02.txt");
		myMenu->goTo(-1);
		break;

	case ID_LEVEL_3:
		playLevel("Levels/Level03.txt");
		myMenu->goTo(-1);
		break;

	case ID_LEVEL_4:
		playLevel("Levels/Level04.txt");
		myMenu->goTo(-1);
		break;

	case ID_CONTROLS:
		showControls();
		myMenu->goTo(-1);
		break;

	default:
		break;
	}

}





void Game::showControls()
{
	return;
}




void Game::loadLevel(string pathToFile, HumanPlayer **myPlayer, vector<Obstacle*>*myObstacles, vector<Enemy*>*myEnemies)
{

	fstream myFile;
	myFile.open(pathToFile);

	if (!myFile.is_open())
		throw "Unable to open file!";
	
	else
	{
		
		//temporary variables
		char c;
		int xPos;
		int yPos;
		unsigned int width;
		unsigned int height;
		bool canKill;
		bool isFinish;
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

				//reading necessary data from file
				myFile >> xSpeed >> ySpeed >> gForce >> tDist >> tTime;
				
				//calibrating speeds and acceleration
				xSpeed /= TIME_BETWEEN_FRAMES;
				ySpeed /= TIME_BETWEEN_FRAMES;
				gForce /= (TIME_BETWEEN_FRAMES * TIME_BETWEEN_FRAMES);
				
				//creating object
				*myPlayer = new HumanPlayer(xPos, yPos, width, height, xSpeed, ySpeed, gForce, tDist, tTime);				
				break;

			case 'O': //obstacle

				//reading necessary data from file
				myFile >> canKill >> isFinish;

				//adding object to vector
				myObstacles->push_back(new Obstacle(xPos, yPos, width, height, canKill, isFinish));
				break;

			case 'E': //enemy
				
				//reading necessary data from file
				myFile >> xSpeed >> ySpeed >> gForce >> tDist >> tTime >> behaviourType;

				//calibrating speeds and acceleration
				xSpeed /= TIME_BETWEEN_FRAMES;
				ySpeed /= TIME_BETWEEN_FRAMES;
				gForce /= (TIME_BETWEEN_FRAMES * TIME_BETWEEN_FRAMES);
				
				//adding object to vector
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





void Game::playLevel(string pathToFile)
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

	
	//load the level
	try { loadLevel(pathToFile, &myPlayer, &myObstacles, &myEnemies); }
	catch (const char* message) 
	{
		cerr << message << endl;
		return;
	}


	

	vector<GameObject*> allObjects(myObstacles.begin(), myObstacles.end());
	vector<GameObject*> auxiliaryVector(myEnemies.begin(), myEnemies.end());
	allObjects.insert(allObjects.end(), auxiliaryVector.begin(), auxiliaryVector.end());



	Uint32 startTime;
	Uint32 endTime;
	Uint32 delta;



	while (!quit && myPlayer->getIsAlive() && !myPlayer->getHasFinished())
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
		

		
		
		clear();
		
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






void Game::clear()
{
	SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0xFF);
	SDL_RenderClear(renderer);
}





void Game::close()
{
	//destroy sdl objects
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);


	//set pointers to NULL
	renderer = NULL;
	window = NULL;


	//quit SDL subsystems
	TTF_Quit();
	SDL_Quit();
}
