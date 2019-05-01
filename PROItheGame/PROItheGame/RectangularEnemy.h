#pragma once
#include "HumanPlayer.h"

class RectangularEnemy :
	public Player
{
	
public:
	///unparametrised constructor
	RectangularEnemy();
	
	///parametrised constructor
	RectangularEnemy(int x, int y, int w, int h, double xC, double yC, double g, int tDist, int tTime):
		Player(x, y, w, h, xC, yC, g, tDist, tTime) {};

	///destructor
	virtual ~RectangularEnemy();


	///function responsbile for printing the enemy onto the surface in relation to the player
	///parameters are: renderer to print the enemy on, player to whose position function relates
	void print(SDL_Renderer* rendererToPrintOn, HumanPlayer* myPlayer);

	///function responsible for checking if enemy collided with a player and reacting accordingly to whatever part hit the player
	///parameters are: player to check
	void checkCollision(HumanPlayer* myPlayer);

	///using function from class Player to check collision with obstacles
	using Player::checkCollision;

	///function responsible for handling the enemy behaviour
	///parameters are: behaviour function
	void applyBehaviour(void (RectangularEnemy::*behaviour)());




	//behaviour functions

	///function responsible for handling the enemy behaviour - the enemy constantly jumps
	void behaveJump();

	///function responsible for handling the enemy behaviour - the enemy moves in x and bounces from obstacles
	void behaveBounce();

};

