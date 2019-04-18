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

void Player::calculateNextPosition(const double timeDifference)
{
	//updating vertical velocity
	if(!contact[DOWN])
		playerMomentum.setYVelocity(playerMomentum.getYVelocity() + playerMomentum.getGForce() * timeDifference);

	//updating vertical position
	yCoordinate += playerMomentum.getYVelocity() * timeDifference;

	//updating horizontal position
	xCoordinate += playerMomentum.getXVelocity() * timeDifference;
}

void Player::print(SDL_Renderer* rendererToPrintOn)
{
	SDL_Rect playerRect = { (int)xCoordinate, (int)yCoordinate, objectWidth, objectHeight };
	SDL_SetRenderDrawColor(rendererToPrintOn, 0xFF, 0x00, 0x00, 0xFF);
	SDL_RenderFillRect(rendererToPrintOn, &playerRect);

}

void Player::checkCollision(RectangularObstacle* obstacle)
{
	if (contact[UP] = checkCollisionSide(obstacle, UP))
		getPlayerMomentum()->setYVelocity(0);
	if (contact[DOWN] = checkCollisionSide(obstacle, DOWN))
	{
		getPlayerMomentum()->setYVelocity(0);
		yCoordinate = obstacle->getYCoordinate() - objectHeight;
	}
	if (contact[LEFT] = checkCollisionSide(obstacle, LEFT))
		getPlayerMomentum()->setXVelocity(0);
	if (contact[RIGHT] = checkCollisionSide(obstacle, RIGHT))
		getPlayerMomentum()->setXVelocity(0);

}

bool Player::checkCollisionSide(RectangularObstacle* obstacle, Direction dir)
{
	switch (dir)
	{
	case UP:
		return false;
		break;
	
	case DOWN:
		if (xCoordinate + objectWidth > obstacle->getXCoordinate() && xCoordinate < obstacle->getXCoordinate() + obstacle->getObjectWidth())
			if (yCoordinate + objectHeight > obstacle->getYCoordinate() && yCoordinate < obstacle->getYCoordinate())
				return true;
		return false;
		break;
	
	case LEFT:
		return false;
		break;
	
	case RIGHT:
		return false;
		break;
	}
	/*if (UP == dir || DOWN == dir)
	{
		if (xCoordinate + objectWidth > obstacle->getXCoordinate() && xCoordinate < obstacle->getXCoordinate() + obstacle->getObjectWidth())
			return true;
		return false;
	}
	else
	{
		if (yCoordinate + objectHeight > obstacle->getYCoordinate() && yCoordinate < obstacle->getYCoordinate() + obstacle->getObjectHeight())
			return true;
		return false;
	}*/
}
