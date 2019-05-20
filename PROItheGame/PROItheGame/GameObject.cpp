///Name: GameObject.cpp
///Purpose: definition of methods from GameObject class
///Author: Piotr Satala

#include "GameObject.h"


using namespace std;


bool GameObject::checkCollisionSide(GameObject* obstacle, Direction dir)
{

	switch (dir) //select direction
	{
	
	case UP:
		if (round(obstacle->getXCoordinate()) < round(xCoordinate + objectWidth) && round(xCoordinate) < round(obstacle->getXCoordinate() + obstacle->getObjectWidth())) //check x
			if (round(yCoordinate) < round(obstacle->getYCoordinate() + obstacle->getObjectHeight()) && round(yCoordinate + objectHeight) > round(obstacle->getYCoordinate() + obstacle->getObjectHeight())) //check y
				return true;
		return false;
		break;

	case DOWN:
		if (round(obstacle->getXCoordinate()) < round(xCoordinate + objectWidth) && round(xCoordinate) < round(obstacle->getXCoordinate() + obstacle->getObjectWidth())) //check x
			if (round(yCoordinate + objectHeight) > round(obstacle->getYCoordinate()) && round(yCoordinate) < round(obstacle->getYCoordinate())) //check y
				return true;
		return false;
		break;

	case LEFT:
		if (round(obstacle->getYCoordinate()) < round(yCoordinate + objectHeight) && round(yCoordinate) < round(obstacle->getYCoordinate() + obstacle->getObjectHeight())) //check y
			if (round(xCoordinate) < round(obstacle->getXCoordinate() + obstacle->getObjectWidth()) && round(xCoordinate + objectWidth) > round(obstacle->getXCoordinate() + obstacle->getObjectWidth())) //check x
				return true;
		return false;
		break;

	case RIGHT:
		if (round(obstacle->getYCoordinate()) < round(yCoordinate + objectHeight) && round(yCoordinate) < round(obstacle->getYCoordinate() + obstacle->getObjectHeight())) //check y
			if (round(xCoordinate + objectWidth) > round(obstacle->getXCoordinate()) && round(xCoordinate) < round(obstacle->getXCoordinate())) //check x
				return true;
		return false;
		break;
	
	default:
		return false;
	}

}



void GameObject::print(SDL_Renderer* renderer, Camera* myCamera)
{
	if (!this->getIsAlive()) //quit if the object's dead
		return;


	//get size of renderer
	int RENDERER_HEIGHT;
	int RENDERER_WIDTH;
	SDL_GetRendererOutputSize(renderer, &RENDERER_WIDTH, &RENDERER_HEIGHT);

	//calculate enemy's displacement
	int objectMoveX = (int)xCoordinate - (int)myCamera->getXCoordinate();
	int objectMoveY = (int)yCoordinate - (int)myCamera->getYCoordinate();


	//print
	SDL_Rect objectRect = { RENDERER_HEIGHT/2 + objectMoveX , RENDERER_WIDTH/2 + objectMoveY, objectWidth, objectHeight };
	SDL_SetRenderDrawColor(renderer, get<0>(color), get<1>(color), get<2>(color), 0xFF);
	SDL_RenderFillRect(renderer, &objectRect);
}
