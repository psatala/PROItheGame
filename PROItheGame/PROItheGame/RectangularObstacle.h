#pragma once

#include "RectangularObject.h"
#include "Player.h"


///forward declaration of Player
class Player;

class RectangularObstacle :
	public RectangularObject
{
public:
	///constructor
	RectangularObstacle(int x = 0, int y = 0, int h = 0, int w = 0) : RectangularObject(x, y, h, w) {};
	
	///destructor
	~RectangularObstacle();
	
	///function prints the object onto the window in relation to the player
	void print(SDL_Renderer* rendererToPrintOn, Player* myPlayer);
};

