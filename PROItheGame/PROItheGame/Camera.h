///Name: Camera.h
///Purpose: declaration and definition of camera class
///Author: Piotr Satala

#pragma once

class Camera
{

	//camera's position
	int xCoordinate;
	int yCoordinate;

public:

	//setters

	///setter for x
	void setXCoordinate(int newValue) { xCoordinate = newValue; }

	///setter for y
	void setYCoordinate(int newValue) { yCoordinate = newValue; }





	//getters

	///getter for x
	int getXCoordinate() { return xCoordinate; }

	///getter for y
	int getYCoordinate() { return yCoordinate; }

};
