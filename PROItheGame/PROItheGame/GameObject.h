///Name: GameObject.h
///Purpose: declaration and definition of abstract GameObject class
///Author: Piotr Satala

#pragma once

#include <SDL.h>



class GameObject
{
protected:
	
	//coordinates in space
	double xCoordinate;
	double yCoordinate;

	//size of object
	int objectHeight;
	int objectWidth;

public:

	///function ensures the class is abstract
	virtual void OverrideMe() = 0;

	
	///constructor
	///parameters are: x and y coordinates, width and height of the object
	GameObject(int x = 0, int y = 0, int w = 0, int h = 0) : xCoordinate(x), yCoordinate(y), objectWidth(w), objectHeight(h) {};
	

	///destructor
	virtual ~GameObject() {}
	




	//setters

	///setter for x coordinate
	void setXCoordinate(double newValue) { xCoordinate = newValue; }

	///setter for y coordinate
	void setYCoordinate(double newValue) { yCoordinate = newValue; }

	///setter for object's height
	void setObjectHeight(int newValue) { objectHeight = newValue; }

	///setter for object's width
	void setObjectWidth(int newValue) { objectWidth = newValue; }

	
	
	

	//getters
	
	///getter for x coordinate
	double getXCoordinate() { return xCoordinate; }

	///getter for y coordinate
	double getYCoordinate() { return yCoordinate; }

	///gettter for object's height
	int getObjectHeight() { return objectHeight; }

	///getter for object's width
	int getObjectWidth() { return objectWidth; }


};

