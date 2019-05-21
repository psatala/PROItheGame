///Name: GameArea.h
///Purpose: Declaration and definition of GameArea class
///Author: Piotr Satala

#pragma once

#include <SDL.h>

#include "HumanPlayer.h"

class GameArea
{
	
	SDL_Rect area; //rectangle specifying area to play in

public:

	///constructor
	///parameters are: x and y coordinates of the upper left corner, width and height of the rectangle indicating game area
	GameArea(int x = 0, int y = 0, int w = 0, int h = 0)
	{
		area.x = x;
		area.y = y;
		area.w = w;
		area.h = h;
	}

	///destructor
	~GameArea() {}


	///function responsible for checking if the user's character has left game area
	///parameters are: pointer to an instance of human player - object controlled by the user
	///function throws an exception if user is outside the game area
	void checkIfInside(HumanPlayer* myPlayer)
	{
		if (!(area.x + area.w > myPlayer->getXCoordinate() && area.x < myPlayer->getXCoordinate() + myPlayer->getObjectWidth()    //check x
			&& area.y + area.h> myPlayer->getYCoordinate() && area.y < myPlayer->getYCoordinate() + myPlayer->getObjectHeight())) //check y
			throw "Out of game area!";		
	}

};

