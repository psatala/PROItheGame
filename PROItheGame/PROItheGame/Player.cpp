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
	playerMomentum.setYAcceleration(2000 * yConstant);
}

void Player::moveRight()
{
	playerMomentum.setXVeloctity(xConstant);
}

void Player::moveLeft()
{
	playerMomentum.setXVeloctity(-xConstant);
}

void Player::calculateNextPosition(const double timeDifference)
{
	//updating vertical acceleration
	playerMomentum.setYAcceleration(playerMomentum.getYAcceleration() - playerMomentum.getGForce() * timeDifference);

	//updating vertical velocity
	playerMomentum.setYVeloctity(playerMomentum.getYVelocity() - playerMomentum.getYAcceleration() * timeDifference);

	//updating vertical position
	yCoordinate += playerMomentum.getYVelocity() * timeDifference;

	//updating horizontal position
	xCoordinate += playerMomentum.getXVelocity() * timeDifference;
}

void Player::printPlayer(SDL_Renderer* rendererToPrintOn)
{
	SDL_SetRenderDrawColor(rendererToPrintOn, 0x00, 0x00, 0x00, 0xFF);
	SDL_RenderClear(rendererToPrintOn);

	SDL_Rect playerRect = { (int)xCoordinate, (int)yCoordinate, objectWidth, objectHeight };
	SDL_SetRenderDrawColor(rendererToPrintOn, 0xFF, 0x00, 0x00, 0xFF);
	SDL_RenderFillRect(rendererToPrintOn, &playerRect);

}
