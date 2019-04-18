#pragma once

#include "RectangularObject.h"

class RectangularObstacle :
	public RectangularObject
{
public:
	///constructor
	RectangularObstacle(int x = 0, int y = 0, int h = 0, int w = 0) : RectangularObject(x, y, h, w) {};
	
	///destructor
	~RectangularObstacle();
	
	///function prints the object onto the window
	void print(SDL_Renderer* rendererToPrintOn);
};

