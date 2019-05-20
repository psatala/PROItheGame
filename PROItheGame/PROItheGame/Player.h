///Name: Player.h
///Purpose: declaration of functions responsible for handling the actions of the player
///Author: Piotr Satala

#pragma once

#include <vector>

#include "Obstacle.h"
#include "Momentum.h"



///forward declaration of RectangularObstacle
class Obstacle;

class Player :
	public GameObject
{
	//constants for velocity
	const double xConstant = 0;
	const double yConstant = 0;
	
	//other constants
	const double gravityConstant = 0;
	const int teleportDistance = 0;
	const unsigned int timeBetweenTeleports = 0;

	Momentum<double, double, double> playerMomentum;
	bool hasFinished = false; //has player finished the level
	Uint32 lastTeleportTime = 0; //time of the last teleport




	///function responsible for checking if player is inside any obstacle from the given vector
	///parameters are: vector of obstacles to check
	bool checkIfInsideAny(std::vector <GameObject*> myVector);

	///function responsible for checking if player is inside an obstacle
	///parameters are: obstacle to check
	bool checkIfInsideOneObject(GameObject* obstacle);


protected:

	///contact in each direction
	bool contact[4] = { 0 };


	///function responsible for jumping
	void jump();

	///function responsbile for moving to the left
	void moveRight();

	///funstion responsbile for moving to the right
	void moveLeft();

	///function responsible for stopping the player in x axis
	void stopX();

	///function responsible for teleporting
	///parameters are: direction in which teleport will take place, distance of the teleport, minimal time between two teleports in miliseconds and vector of obstacles
	void teleport(Direction dir, std::vector<GameObject*> myVector);



public:
	///function overriding abstract function from base class
	void OverrideMe() {}

	
	///default constructor
	Player() {}

	///parametrised constructor
	///parameters are object's: x coordinate, y coordinate, height, width, constant of speed in x and in y, gravity constant, distance covered by teleporting once and minimal time between teleports
	Player(int x, int y, int w, int h, double xC, double yC, double g, int tDist, int tTime):
		xConstant(xC),
		yConstant(yC),
		gravityConstant(g),
		playerMomentum(gravityConstant),		
		teleportDistance(tDist),
		timeBetweenTeleports(tTime)
	{
		xCoordinate = x;
		yCoordinate = y;
		objectWidth = w;
		objectHeight = h;
		color = std::make_tuple(0x00, 0x00, 0x00);
	};


	///destructor
	virtual ~Player() {}


	///function responsbile for calculating next position of the object based on previous position and speed
	///parameters are: time between frames
	void calculateNextPosition(const double timeDifference);

	
	
	///function responsible for checking if player collided with an obstacle and reacting accordingly to whatever part hit the obstacle
	///parameters are: obstacle to check
	void checkCollision(Obstacle* obstacle);

	



	//getters
	
	///getter for x constant of velocity
	double getXConstant() { return xConstant; }
	
	///getter for y constant of velocity
	double getYConstant() { return yConstant; }
	
	///getter for player's momentum
	Momentum<double, double, double>* getPlayerMomentum() { return &playerMomentum; }
	
	///getter for hasFinished
	bool getHasFinished() { return hasFinished; }



	//setters

	///setter for player momentum
	void setPlayerMomentum(Momentum<double, double, double> newValue) { playerMomentum = newValue; }
	
	///setter for hasFinished
	void setHasFinished(bool newValue) { hasFinished = newValue; }


};

