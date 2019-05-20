///Name: Obstacle.cpp
///Purpose: definition of methods from obstacle class
///Author: Piotr Satala

#include "Obstacle.h"



void Obstacle::setColor()
{
	//set printing color
	if (isItFinish)
		color = std::make_tuple(0x00, 0x00, 0xFF);
	else if (canItKill)
		color = std::make_tuple(0xFF, 0xA5, 0x00);
	else
		color = std::make_tuple(0xFF, 0xFF, 0xFF);
}