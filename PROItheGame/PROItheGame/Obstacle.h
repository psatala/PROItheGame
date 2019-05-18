#pragma once

#include "GameObject.h"
#include "Player.h"


///forward declaration of Player
class Player;

class Obstacle :
	public GameObject
{

	bool canItKill;
	bool isItFinish;

public:
	///function overriding abstract function from base class
	void OverrideMe() {}

	///constructor
	Obstacle(int x = 0, int y = 0, int w = 0, int h = 0, bool canKill = false, bool isFinish = false):
		canItKill(canKill),
		isItFinish(isFinish)
	{
		xCoordinate = x;
		yCoordinate = y;
		objectWidth = w;
		objectHeight = h;
	};
	
	///destructor
	~Obstacle();
	
	///function prints the object onto the window in relation to the player
	///parameters are: renderer to print on, player to relate to
	void print(SDL_Renderer* rendererToPrintOn, Player* myPlayer);

	///getters
	bool getCanItKill() { return canItKill; }
	bool getIsItFinish() { return isItFinish; }

	///setters
	void setCanItKill(bool newValue) { canItKill = newValue; }
	void setIsItFinish(bool newValue) { isItFinish = newValue; }
};

