///Name: Player.h
///Purpose: definition of functions responsible for handling the actions of the player
///Author: Piotr Satala

#include "Player.h"


Player::Player()
{
	RectangularObject();
}



Player::~Player()
{

}



void Player::jump()
{
	if(contact[DOWN])
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



void Player::teleport(Direction dir, std::vector<RectangularObstacle*> myVector)
{
	static Uint32 lastTime;
	Uint32 now = SDL_GetTicks();
	if (now - lastTime >= timeBetweenTeleports || 0 == lastTime)
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
			lastTime = now;
	}
}



void Player::calculateNextPosition(const double timeDifference)
{
	//updating vertical velocity
	if(!contact[DOWN])
		playerMomentum.setYVelocity(playerMomentum.getYVelocity() + playerMomentum.getGForce() * timeDifference);

	//updating vertical position
	yCoordinate += playerMomentum.getYVelocity() * timeDifference;

	//updating horizontal position
	xCoordinate += playerMomentum.getXVelocity() * timeDifference;

	//reseting contact
	for (int i = 0; i < 4; i++)
		contact[i] = false;
}



void Player::print(SDL_Renderer* rendererToPrintOn)
{
	if (!isAlive) //quit if the player's dead
		return;

	int RENDERER_HEIGHT;
	int RENDERER_WIDTH;
	SDL_GetRendererOutputSize(rendererToPrintOn, &RENDERER_WIDTH, &RENDERER_HEIGHT);

	SDL_Rect playerRect = { (RENDERER_WIDTH - PLAYER_WIDTH) / 2, (RENDERER_HEIGHT - PLAYER_HEIGHT) / 2, objectWidth, objectHeight };
	SDL_SetRenderDrawColor(rendererToPrintOn, 0x00, 0xFF, 0x00, 0xFF);
	SDL_RenderFillRect(rendererToPrintOn, &playerRect);

}



void Player::checkCollision(RectangularObstacle* obstacle)
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

	//check if player was killed by the obstacle
	for (int i = 0; i < 4; i++)
		if (obstacle->getCanItKill() and contactWithThisObject[i])
			isAlive = false;

}




bool Player::checkCollisionSide(RectangularObject* obstacle, Direction dir)
{
	switch (dir)
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



bool Player::checkIfInsideAny(std::vector <RectangularObstacle*> myVector)
{
	bool result = false;
	for (std::vector <RectangularObstacle*>::iterator it = myVector.begin(); it != myVector.end(); ++it)
		result |= checkIfInsideOneObject(*it);
	return result;
}



bool Player::checkIfInsideOneObject(RectangularObstacle* obstacle)
{
	return	xCoordinate + objectWidth > obstacle->getXCoordinate() && xCoordinate < obstacle->getXCoordinate() + obstacle->getObjectWidth()
		&& yCoordinate + objectHeight > obstacle->getYCoordinate() && yCoordinate < obstacle->getYCoordinate() + obstacle->getObjectHeight();
}