#include "RectangularEnemy.h"



RectangularEnemy::RectangularEnemy()
{
	Player();
}


RectangularEnemy::~RectangularEnemy()
{
}


void RectangularEnemy::checkCollision(Player* myPlayer)
{
	if (!this->getIsAlive()) //quit if enemy's dead
		return;

	bool contactWithThisObject[4] = { 0 };

	//check contact up
	if (contactWithThisObject[UP] = myPlayer->checkCollisionSide(this, DOWN))
	{
		getPlayerMomentum()->setYVelocity(0);
		yCoordinate = round(myPlayer->getYCoordinate() + myPlayer->getObjectHeight());
		this->setIsAlive(false);
	}

	//check contact down
	else if (contactWithThisObject[DOWN] = myPlayer->checkCollisionSide(this, UP))
	{
		getPlayerMomentum()->setYVelocity(0);
		yCoordinate = round(myPlayer->getYCoordinate() - objectHeight);
		myPlayer->setIsAlive(false);
	}

	//check contact left
	else if (contactWithThisObject[LEFT] = myPlayer->checkCollisionSide(this, RIGHT))
	{
		getPlayerMomentum()->setXVelocity(0);
		xCoordinate = round(myPlayer->getXCoordinate() + myPlayer->getObjectWidth());
		myPlayer->setIsAlive(false);
	}

	//check contact right
	else if (contactWithThisObject[RIGHT] = myPlayer->checkCollisionSide(this, LEFT))
	{
		getPlayerMomentum()->setXVelocity(0);
		xCoordinate = round(myPlayer->getXCoordinate() - objectWidth);
		myPlayer->setIsAlive(false);
	}

	//update overall contact
	for (int i = 0; i < 4; i++)
		contact[i] |= contactWithThisObject[i];

}

void RectangularEnemy::print(SDL_Renderer* rendererToPrintOn, Player* myPlayer)
{
	if (!this->getIsAlive()) //quit if the enemy's dead
		return;

	int RENDERER_HEIGHT;
	int RENDERER_WIDTH;
	SDL_GetRendererOutputSize(rendererToPrintOn, &RENDERER_WIDTH, &RENDERER_HEIGHT);

	int playerMoveX = (int)myPlayer->getXCoordinate() - (RENDERER_WIDTH - myPlayer->getPlayerWidth()) / 2;
	int playerMoveY = (int)myPlayer->getYCoordinate() - (RENDERER_HEIGHT - myPlayer->getPlayerHeight()) / 2;

	SDL_Rect playerRect = { (int)xCoordinate - playerMoveX, (int)yCoordinate - playerMoveY, objectWidth, objectHeight };
	SDL_SetRenderDrawColor(rendererToPrintOn, 0xFF, 0x00, 0x00, 0xFF);
	SDL_RenderFillRect(rendererToPrintOn, &playerRect);
}