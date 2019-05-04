#pragma once
#include <SDL.h>



class GameObject
{
protected:
	double xCoordinate;
	double yCoordinate;
	int objectHeight;
	int objectWidth;

public:
	///function ensures the class is abstract
	virtual void OverrideMe() = 0;

	GameObject(int x = 0, int y = 0, int w = 0, int h = 0) : xCoordinate(x), yCoordinate(y), objectWidth(w), objectHeight(h) {};
	
	virtual ~GameObject();
	
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


};

