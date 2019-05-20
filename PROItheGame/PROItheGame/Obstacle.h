///Name: Obstacle.h
///Purpose: declaration of obstacle class
///Author: Piotr Satala

#pragma once

#include "GameObject.h"



class Obstacle :
	public GameObject
{

	//can this obstacle kill a player
	bool canItKill;

	//is this obstacle a finish line
	bool isItFinish;

public:

	///function overriding abstract function from base class
	void OverrideMe() {}


	///constructor
	///parameters are: x and y coordinates, width and height, information about whether or no can it kill and is it a finish line
	Obstacle(int x = 0, int y = 0, int w = 0, int h = 0, bool canKill = false, bool isFinish = false):
		canItKill(canKill),
		isItFinish(isFinish)
	{
		xCoordinate = x;
		yCoordinate = y;
		objectWidth = w;
		objectHeight = h;

		//set printing color
		if(isItFinish)
			color = std::make_tuple(0x00, 0x00, 0xFF);
		else if(canItKill)
			color = std::make_tuple(0xFF, 0xA5, 0x00);
		else
			color = std::make_tuple(0xFF, 0xFF, 0xFF);

	};
	

	///destructor
	~Obstacle() {}
	
	



	//setters

	///setter for can this object kill
	void setCanItKill(bool newValue) { canItKill = newValue; }
	
	///setter for is it finish line
	void setIsItFinish(bool newValue) { isItFinish = newValue; }





	//getters
	
	///getter for can this object kill
	bool getCanItKill() { return canItKill; }
	
	///getter for is it finish line
	bool getIsItFinish() { return isItFinish; }

};

