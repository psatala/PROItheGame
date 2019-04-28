#pragma once
#include "Player.h"
class RectangularEnemy :
	public Player
{
public:
	///unparametrised constructor
	RectangularEnemy();
	
	///parametrised constructor
	RectangularEnemy(int x, int y, int w, int h, double xC, double yC, double g, const int pW, const int pH) :
		Player(x, y, w, h, xC, yC, g, pW, pH) {};

	///destructor
	~RectangularEnemy();


	///function responsbile for printing the enemy onto the surface in relation to the player
	///parameters are: renderer to print the enemy on, player to whose position function relates
	void print(SDL_Renderer* rendererToPrintOn, Player* myPlayer);

	///function responsible for checking if enemy collided with a player and reacting accordingly to whatever part hit the player
	///parameters are: player to check
	void checkCollision(Player* myPlayer);

	///using function from class Player to check collision with obstacles
	using Player::checkCollision;
};

