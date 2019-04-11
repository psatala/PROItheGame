///Name: Player.h
///Purpose: declaration of functions responsible for handling the actions of the player
///Author: Piotr Satala

#pragma once

#include <SDL.h>

#include "RectangularObject.h"
class Player :
	public RectangularObject
{
	//Constant containing basic speeds
	const double xConstant = 0;
	const double yConstant = 0;

public:
	///default constructor
	Player();

	///parametrised constructor
	///parameters are object's: x coordinate, y coordinate, height, width, constant of speed in x and in y
	Player(int x, int y, int h, int w, double xC, double yC) : xConstant(xC), yConstant(yC), RectangularObject(x, y, h, w) {};

	///destructor
	~Player();

	///function responsible for jumping

	void jump();

	///funstion responsbile for moving to the right
	void moveLeft();

	///function responsbile for moving to the left
	void moveRight();

	///function responsbile for calculating next position of the object based on previous position and speed
	void calculateNextPosition();

	///function responsbile for printing the player onto the surface
	///parameters are: renderer to print the player on
	void printPlayer(SDL_Renderer* rendererToPrintOn);

	//getters
	double getXConstant();
	double getYConstant();
	
};

