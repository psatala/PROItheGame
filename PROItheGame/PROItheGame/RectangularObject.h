#pragma once

#include "AbstractObject.h"
#include "Player.h"


///forward declaration of Player
class Player;

class RectangularObject :
	public AbstractObject
{
protected:
	double xCoordinate;
	double yCoordinate;
	int objectHeight;
	int objectWidth;

public:
	RectangularObject(int x = 0, int y = 0, int w = 0, int h = 0) : xCoordinate(x), yCoordinate(y), objectWidth(w), objectHeight(h) {};
	
	virtual ~RectangularObject();

	///function responsbile for checking if the object of this class has killed the given player
	///parameters are: player to check, array indicating contact in each direction
	virtual void checkIfKilled(Player* myPlayer, bool* contactWithThisObject) {}

	///setters
	void setXCoordinate(double newValue) { xCoordinate = newValue; }
	void setYCoordinate(double newValue) { yCoordinate = newValue; }
	void setObjectHeight(int newValue) { objectHeight = newValue; }
	void setObjectWidth(int newValue) { objectWidth = newValue; }

	///getters
	double getXCoordinate() { return xCoordinate; }
	double getYCoordinate() { return yCoordinate; }
	int getObjectHeight() { return objectHeight; }
	int getObjectWidth() { return objectWidth; }


	virtual void print(SDL_Renderer* rendererToPrintOn);
};

