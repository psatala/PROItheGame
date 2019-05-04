#pragma once

#include "GameObject.h"
#include "Player.h"


///forward declaration of Player
class Player;

class Obstacle :
	public GameObject
{
	bool canItKill;
public:
	///constructor
	Obstacle(int x = 0, int y = 0, int w = 0, int h = 0, bool canKill = false):
		canItKill(canKill) 
	{
		xCoordinate = x;
		yCoordinate = y;
		objectWidth = w;
		objectHeight = h;
	};
	
	///destructor
	~Obstacle();
	
	///function prints the object onto the window in relation to the player
	void print(SDL_Renderer* rendererToPrintOn, Player* myPlayer);

	///getters
	bool getCanItKill() { return canItKill; }

	///setters
	void setCanItKill(bool newValue) { canItKill = newValue; }
};

