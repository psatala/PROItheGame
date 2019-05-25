///Name: GameArea.h
///Purpose: declaration of GameArea class
///Author: Piotr Satala

#pragma once

#include <SDL.h>

#include "HumanPlayer.h"

class GameArea
{
	
	SDL_Rect area; //rectangle specifying area to play in

	static int count; //number of instances of this class created

public:

	///constructor
	///parameters are: x and y coordinates of the upper left corner, width and height of the rectangle indicating game area
	GameArea(int x = 0, int y = 0, int w = 0, int h = 0);

	///destructor
	~GameArea() { --count; }


	///function responsible for checking if the user's character has left game area
	///parameters are: pointer to an instance of human player - object controlled by the user
	///function throws an exception if user is outside the game area
	void checkIfInside(HumanPlayer* myPlayer);

	//getters

	///getter for count
	static int getCount() { return count; }

};

