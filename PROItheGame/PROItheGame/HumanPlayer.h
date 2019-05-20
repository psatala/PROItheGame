///Name: HumanPlayer.h
///Purpose: declaration of class HumanPlayer - its instance is controlled by the user
///Author: Piotr Satala

#pragma once

#include "Player.h"

class HumanPlayer :
	public Player
{
public:

	///default constructor
	HumanPlayer() {}


	///parametrised constructor
	///parameters are object's: x coordinate, y coordinate, height, width, constant of speed in x and in y, gravity constant, distance covered by teleporting once and minimal time between teleports
	HumanPlayer(int x, int y, int w, int h, double xC, double yC, double g, int tDist, int tTime):
		Player(x, y, w, h, xC, yC, g, tDist, tTime) {};


	///destructor
	virtual ~HumanPlayer() {}



	///function responsible for setting the color to print in
	virtual void setColor();



	///function responsible for handling keyboard inputs for the player
	///parameters are: vector of all objects 
	virtual void applyBehaviour(std::vector <GameObject*> myVector);

};

