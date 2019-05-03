#pragma once

#include "RectangularObject.h"
#include "Player.h"


///forward declaration of Player
class Player;

class RectangularObstacle :
	public RectangularObject
{
	bool canItKill;
public:
	///constructor
	RectangularObstacle(int x = 0, int y = 0, int w = 0, int h = 0, bool canKill = false) : RectangularObject(x, y, w, h), canItKill(canKill) {};
	
	///destructor
	~RectangularObstacle();
	
	///function prints the object onto the window in relation to the player
	void print(SDL_Renderer* rendererToPrintOn, Player* myPlayer);

	///getters
	bool getCanItKill() { return canItKill; }

	///setters
	void setCanItKill(bool newValue) { canItKill = newValue; }
};

