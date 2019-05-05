#pragma once

#include <string>

#include "HumanPlayer.h"

class Enemy :
	public Player
{
	void (Enemy::*ptrToBehaviourFunction)();
public:
	///unparametrised constructor
	Enemy();
	
	///parametrised constructor
	Enemy(int x, int y, int w, int h, double xC, double yC, double g, int tDist, int tTime, std::string behaviourType = ""):
		Player(x, y, w, h, xC, yC, g, tDist, tTime) 
	{
		if ("JUMP" == behaviourType)
			ptrToBehaviourFunction = &Enemy::behaveJump;
		else if ("BOUNCE" == behaviourType)
			ptrToBehaviourFunction = &Enemy::behaveBounce;
		else
			ptrToBehaviourFunction = &Enemy::behaveNothing;
	};

	///destructor
	virtual ~Enemy();


	///function responsbile for printing the enemy onto the surface in relation to the player
	///parameters are: renderer to print the enemy on, player to whose position function relates
	void print(SDL_Renderer* rendererToPrintOn, HumanPlayer* myPlayer);

	///function responsible for checking if enemy collided with a player and reacting accordingly to whatever part hit the player
	///parameters are: player to check
	void checkCollision(HumanPlayer* myPlayer);

	///using function from class Player to check collision with obstacles
	using Player::checkCollision;

	///function responsible for handling the enemy behaviour
	void applyBehaviour() { (this->*ptrToBehaviourFunction)(); }




	//behaviour functions

	///function responsible for handling the enemy behaviour - the enemy constantly jumps
	void behaveJump();

	///function responsible for handling the enemy behaviour - the enemy moves in x and bounces from obstacles
	void behaveBounce();

	///function responsible for handling the enemy behaviour - the enemy does nothing
	void behaveNothing() {}
};

