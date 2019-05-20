///Name: Enemy.h
///Purpose: declaration of Enemy class
///Author: Piotr Satala

#pragma once

#include <string>

#include "HumanPlayer.h"


class Enemy :
	public Player
{
	
	//auxiliary variable for behaveBounce function
	//determines wether or not the enemy's sides have made contact with anything
	bool isAfterFirstBounce = false;


	//pointer to behaviour function
	void (Enemy::*ptrToBehaviourFunction)();



	//behaviour functions


	///function responsible for handling the enemy behaviour - the enemy constantly jumps
	void behaveJump();


	///function responsible for handling the enemy behaviour - the enemy moves in x and bounces from obstacles
	void behaveBounce();


	///function responsible for handling the enemy behaviour - the enemy does nothing
	void behaveNothing() {}


	///function responsible for handling the enemy behaviour - the enemy teleports upwards
	void behaveTeleportUP();


	///function responsible for handling the enemy behaviour - the enemy teleports downwards
	void behaveTeleportDOWN();

	
	///function responsible for handling the enemy behaviour - the enemy teleports leftwards
	void behaveTeleportLEFT();

	
	///function responsible for handling the enemy behaviour - the enemy teleports rightwards
	void behaveTeleportRIGHT();


public:

	///default constructor
	Enemy() {}
	

	///parametrised constructor
	Enemy(int x, int y, int w, int h, double xC, double yC, double g, int tDist, int tTime, std::string behaviourType = ""):
		Player(x, y, w, h, xC, yC, g, tDist, tTime) 
	{
		//setting the pointer to a behaviour function
		
		if ("JUMP" == behaviourType)
			ptrToBehaviourFunction = &Enemy::behaveJump;

		else if ("BOUNCE" == behaviourType)
			ptrToBehaviourFunction = &Enemy::behaveBounce;

		else if ("TELEPORT_UP" == behaviourType)
			ptrToBehaviourFunction = &Enemy::behaveTeleportUP;

		else if ("TELEPORT_DOWN" == behaviourType)
			ptrToBehaviourFunction = &Enemy::behaveTeleportDOWN;

		else if ("TELEPORT_LEFT" == behaviourType)
			ptrToBehaviourFunction = &Enemy::behaveTeleportLEFT;

		else if ("TELEPORT_RIGHT" == behaviourType)
			ptrToBehaviourFunction = &Enemy::behaveTeleportRIGHT;

		else
			ptrToBehaviourFunction = &Enemy::behaveNothing;

		
	};

	
	
	///destructor
	virtual ~Enemy() {}



	///function responsible for setting the color to print in
	virtual void setColor();


	
	///function responsible for checking if enemy collided with a player and reacting accordingly to whatever part hit the player
	///parameters are: player to check
	void checkCollision(HumanPlayer* myPlayer);

	
	///using function from class Player to check collision with obstacles
	using Player::checkCollision;

	
	///function responsible for handling the enemy behaviour
	void applyBehaviour(std::vector <GameObject*> myVector) { (this->*ptrToBehaviourFunction)(); }


};

