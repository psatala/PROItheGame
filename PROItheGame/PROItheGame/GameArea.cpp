///Name: GameArea.h
///Purpose: definition of methods from GameArea class
///Author: Piotr Satala

#include "GameArea.h"



//initialization of class GameArea static member
int GameArea::count = 0;



GameArea::GameArea(int x, int y, int w, int h)
{
	area.x = x;
	area.y = y;
	area.w = w;
	area.h = h;
	++count;
}



void GameArea::checkIfInside(HumanPlayer* myPlayer)
{
	if (!(area.x + area.w > myPlayer->getXCoordinate() && area.x < myPlayer->getXCoordinate() + myPlayer->getObjectWidth()    //check x
		&& area.y + area.h> myPlayer->getYCoordinate() && area.y < myPlayer->getYCoordinate() + myPlayer->getObjectHeight())) //check y
		throw "Out of game area!";
}