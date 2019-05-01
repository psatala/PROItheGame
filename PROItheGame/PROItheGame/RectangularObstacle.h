#pragma once

#include "RectangularObject.h"



class RectangularObstacle :
	public RectangularObject
{
	bool canItKill;
public:
	///constructor
	RectangularObstacle(int x = 0, int y = 0, int w = 0, int h = 0, bool canKill = false) : RectangularObject(x, y, w, h), canItKill(canKill) {};
	
	///destructor
	~RectangularObstacle();

	///function responsbile for checking if the object of this class has killed the given player
	///parameters are: player to check, array indicating contact in each direction
	void checkIfKilled(Player* myPlayer, bool* contactWithThisObject);
	
	///function prints the object onto the window in relation to the player
	void print(SDL_Renderer* rendererToPrintOn, Player* myPlayer);

	///getters
	bool getCanItKill() { return canItKill; }

	///setters
	void setCanItKill(bool newValue) { canItKill = newValue; }
};

