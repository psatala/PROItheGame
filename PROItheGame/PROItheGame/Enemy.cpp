///Name: Enemy.cpp
///Purpose: definition of methods from Enemy class
///Author: Piotr Satala

#include "Enemy.h"




//behaviour funtions

void Enemy::behaveJump()
{
	jump();
}



void Enemy::behaveBounce()
{
	if (contact[RIGHT])
	{
		moveLeft();
		isAfterFirstBounce = true;
	}
	else if (contact[LEFT])
	{
		moveRight();
		isAfterFirstBounce = true;
	}
	else if (!isAfterFirstBounce)
		moveLeft();
}



void Enemy::behaveTeleportUP()
{
	//placeholder solution
	teleport(UP, std::vector<GameObject*>());
}



void Enemy::behaveTeleportDOWN()
{
	//placeholder solution
	teleport(DOWN, std::vector<GameObject*>());
}



void Enemy::behaveTeleportLEFT()
{
	//placeholder solution
	teleport(LEFT, std::vector<GameObject*>());
}



void Enemy::behaveTeleportRIGHT()
{
	//placeholder solution
	teleport(RIGHT, std::vector<GameObject*>());
}







//other

void Enemy::checkCollision(HumanPlayer* myPlayer)
{
	if (!this->getIsAlive()) //quit if enemy's dead
		return;

	bool contactWithThisObject[4] = { 0 };

	//check contact up
	if (contactWithThisObject[UP] = myPlayer->checkCollisionSide(this, DOWN))
	{
		//changing player's velocity in y to 0
		Momentum<double, double, double>* newMomentum = myPlayer->getPlayerMomentum();
		newMomentum->setYVelocity(0);
		myPlayer->setPlayerMomentum(*newMomentum);
		
		
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


