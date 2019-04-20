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

void Player::teleport(Direction dir, const int teleportDistance, const unsigned int timeBetweenTeleports)
{
	static Uint32 lastTime;
	Uint32 now = SDL_GetTicks();
	if (now - lastTime >= timeBetweenTeleports || 0 == lastTime)
	{
		int x[] = { 0, 0, -1, 1 };
		int y[] = { -1, 1, 0, 0 };
		xCoordinate += x[(int)dir] * teleportDistance;
		yCoordinate += y[(int)dir] * teleportDistance;
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
	int RENDERER_HEIGHT;
	int RENDERER_WIDTH;
	SDL_GetRendererOutputSize(rendererToPrintOn, &RENDERER_WIDTH, &RENDERER_HEIGHT);

	SDL_Rect playerRect = { (RENDERER_WIDTH - PLAYER_WIDTH) / 2, (RENDERER_HEIGHT - PLAYER_HEIGHT) / 2, objectWidth, objectHeight };
	SDL_SetRenderDrawColor(rendererToPrintOn, 0xFF, 0x00, 0x00, 0xFF);
	SDL_RenderFillRect(rendererToPrintOn, &playerRect);

}

void Player::checkCollision(RectangularObstacle* obstacle)
{
	bool contactWithThisObject[4] = { 0 };
	
	//check contact up
	if (contactWithThisObject[UP] = checkCollisionSide(obstacle, UP))
	{
		getPlayerMomentum()->setYVelocity(0);
		yCoordinate = obstacle->getYCoordinate() + obstacle->getObjectHeight();
	}

	//check contact down
	if (contactWithThisObject[DOWN] = checkCollisionSide(obstacle, DOWN))
	{
		getPlayerMomentum()->setYVelocity(0);
		yCoordinate = obstacle->getYCoordinate() - objectHeight;
	}

	//check contact left
	if (contactWithThisObject[LEFT] = checkCollisionSide(obstacle, LEFT))
	{
		getPlayerMomentum()->setXVelocity(0);
		xCoordinate = obstacle->getXCoordinate() + obstacle->getObjectWidth();
	}
	
	//check contact right
	if (contactWithThisObject[RIGHT] = checkCollisionSide(obstacle, RIGHT))
	{
		getPlayerMomentum()->setXVelocity(0);
		xCoordinate = obstacle->getXCoordinate() - objectWidth;
	}

	//update overall contact
	for (int i = 0; i < 4; i++)
		contact[i] |= contactWithThisObject[i];

}

bool Player::checkCollisionSide(RectangularObstacle* obstacle, Direction dir)
{
	switch (dir)
	{
	case UP:
		if (xCoordinate + objectWidth > obstacle->getXCoordinate() && xCoordinate < obstacle->getXCoordinate() + obstacle->getObjectWidth()) //check x
			if (yCoordinate <= obstacle->getYCoordinate() + obstacle->getObjectHeight() && yCoordinate + objectHeight >= obstacle->getYCoordinate() + obstacle->getObjectHeight()) //check y
				return true;
		return false;
		break;
	
	case DOWN:
		if (xCoordinate + objectWidth > obstacle->getXCoordinate() && xCoordinate < obstacle->getXCoordinate() + obstacle->getObjectWidth()) //check x
			if (yCoordinate + objectHeight >= obstacle->getYCoordinate() && yCoordinate <= obstacle->getYCoordinate()) //check y
				return true;
		return false;
		break;
	
	case LEFT:
		if (yCoordinate + objectHeight > obstacle->getYCoordinate() && yCoordinate < obstacle->getYCoordinate() + obstacle->getObjectHeight()) //check y
			if (xCoordinate <= obstacle->getXCoordinate() + obstacle->getObjectWidth() && xCoordinate + objectWidth >= obstacle->getXCoordinate() + obstacle->getObjectWidth()) //check x
				return true;
		return false;
		break;
	
	case RIGHT:
		if (yCoordinate + objectHeight > obstacle->getYCoordinate() && yCoordinate < obstacle->getYCoordinate() + obstacle->getObjectHeight()) //check y
			if (xCoordinate + objectWidth >= obstacle->getXCoordinate() && xCoordinate <= obstacle->getXCoordinate()) //check x
				return true;
		return false;
		break;
	default:
		return false;
	}
}
