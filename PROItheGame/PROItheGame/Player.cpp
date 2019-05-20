///Name: Player.h
///Purpose: definition of functions responsible for handling the actions of the player
///Author: Piotr Satala

#include "Player.h"




//private methods

bool Player::checkIfInsideAny(std::vector <GameObject*> myVector)
{
	bool result = false;
	for (std::vector <GameObject*>::iterator it = myVector.begin(); it != myVector.end(); ++it)
		result |= checkIfInsideOneObject(*it);
	return result;
}



bool Player::checkIfInsideOneObject(GameObject* obstacle)
{
	if (this == obstacle) return false; //not checking if the player is inside himself


	return	xCoordinate + objectWidth > obstacle->getXCoordinate() && xCoordinate < obstacle->getXCoordinate() + obstacle->getObjectWidth()
		&& yCoordinate + objectHeight > obstacle->getYCoordinate() && yCoordinate < obstacle->getYCoordinate() + obstacle->getObjectHeight();
}




//protected methods

void Player::jump()
{
	if(gravityConstant >= 0 && contact[DOWN] || gravityConstant < 0 && contact[UP])
		playerMomentum.setYVelocity(yConstant);
}



void Player::moveRight()
{
	playerMomentum.setXVelocity(xConstant);
}



void Player::moveLeft()
{
	playerMomentum.setXVelocity(-xConstant);
}


void Player::stopX()
{
	playerMomentum.setXVelocity(0);
}



void Player::teleport(Direction dir, std::vector<GameObject*> myVector)
{
	Uint32 now = SDL_GetTicks();
	if (now - lastTeleportTime >= timeBetweenTeleports || 0 == lastTeleportTime)
	{
		//auxiliary arrays
		int x[] = { 0, 0, -1, 1 };
		int y[] = { -1, 1, 0, 0 };

		//teleporting
		xCoordinate += x[(int)dir] * teleportDistance;
		yCoordinate += y[(int)dir] * teleportDistance;
		
		
		if (checkIfInsideAny(myVector)) //reversing teleport in case player is inside an object
		{
			xCoordinate -= x[(int)dir] * teleportDistance;
			yCoordinate -= y[(int)dir] * teleportDistance;
		}
		else //updating timer
			lastTeleportTime = now;
	}
}




//public methods

void Player::calculateNextPosition(const double timeDifference)
{
	//updating vertical velocity
	if((playerMomentum.getGForce() > 0 && !contact[DOWN]) || (playerMomentum.getGForce() < 0 && !contact[UP]))
		playerMomentum.setYVelocity(playerMomentum.getYVelocity() + playerMomentum.getGForce() * timeDifference);

	//updating vertical position
	yCoordinate += playerMomentum.getYVelocity() * timeDifference;

	//updating horizontal position
	xCoordinate += playerMomentum.getXVelocity() * timeDifference;

	//reseting contact
	for (int i = 0; i < 4; i++)
		contact[i] = false;
}






void Player::checkCollision(Obstacle* obstacle)
{
	if (!isAlive)
		return;

	bool contactWithThisObject[4] = { 0 };
	
	//check contact up
	if (contactWithThisObject[UP] = checkCollisionSide(obstacle, UP))
	{
		getPlayerMomentum()->setYVelocity(0);
		yCoordinate = round(obstacle->getYCoordinate() + obstacle->getObjectHeight());
	}

	//check contact down
	if (contactWithThisObject[DOWN] = checkCollisionSide(obstacle, DOWN))
	{
		getPlayerMomentum()->setYVelocity(0);
		yCoordinate = round(obstacle->getYCoordinate() - objectHeight);
	}

	//check contact left
	if (contactWithThisObject[LEFT] = checkCollisionSide(obstacle, LEFT))
	{
		getPlayerMomentum()->setXVelocity(0);
		xCoordinate = round(obstacle->getXCoordinate() + obstacle->getObjectWidth());
	}
	
	//check contact right
	if (contactWithThisObject[RIGHT] = checkCollisionSide(obstacle, RIGHT))
	{
		getPlayerMomentum()->setXVelocity(0);
		xCoordinate = round(obstacle->getXCoordinate() - objectWidth);
	}

	//update overall contact
	for (int i = 0; i < 4; i++)
		contact[i] |= contactWithThisObject[i];


	//check if contact with the obstacle killed the player
	for (int i = 0; i < 4; i++)
	{
		if (contactWithThisObject[i])
		{
			if (obstacle->getIsItFinish())
				hasFinished = true;
			else if (obstacle->getCanItKill())
				isAlive = false;
		}
		

	}
		

}



