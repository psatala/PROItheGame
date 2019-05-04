#pragma once
#include "Player.h"
class HumanPlayer :
	public Player
{
public:

	///default constructor
	HumanPlayer();

	///parametrised constructor
	HumanPlayer(int x, int y, int w, int h, double xC, double yC, double g, int tDist, int tTime):
		Player(x, y, w, h, xC, yC, g, tDist, tTime) {};
	
	///destructor
	virtual ~HumanPlayer();

	///function responsible for handling keyboard inputs for the player
	///parameters are: vector of obstacles 
	void applyInput(std::vector <Obstacle*> myVector);
};

