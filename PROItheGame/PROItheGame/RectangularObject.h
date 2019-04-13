#pragma once

#include "AbstractObject.h"

class RectangularObject :
	public AbstractObject
{
protected:
	double xCoordinate;
	double yCoordinate;
	int objectHeight;
	int objectWidth;

public:
	RectangularObject(int x = 0, int y = 0, int h = 0, int w = 0) : xCoordinate(x), yCoordinate(y), objectHeight(h), objectWidth(w) {};
	~RectangularObject();

	///setters
	void setXCoordinate(double newValue);
	void setYCoordinate(double newValue);
	void setObjectHeight(int newValue);
	void setObjectWidth(int newValue);

	///getters
	double getXCoordinate();
	double getYCoordinate();
	int getObjectHeight();
	int getObjectWidth();

};

