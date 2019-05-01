///Name: Player.h
///Purpose: declaration of functions responsible for handling the actions of the player
///Author: Piotr Satala

#pragma once

#include <vector>
#include <math.h>

#include "RectangularObstacle.h"
#include "Momentum.h"



///forward declaration of RectangularObject
class RectangularObject;

class Player :
	public RectangularObject
{
	//Constants for velocity
	const double xConstant = 0;
	const double yConstant = 0;
	const double gravityConstant = 0;
	const int teleportDistance = 0;
	const unsigned int timeBetweenTeleports = 0;

	Momentum playerMomentum;
	bool isAlive;



protected:

	const int PLAYER_HEIGHT = 0;
	const int PLAYER_WIDTH = 0;

	///contact in each direction
	bool contact[4] = { 0 };

public:

	///enum indicating direction
	enum Direction { UP, DOWN, LEFT, RIGHT };

	///default constructor
	Player();

	///parametrised constructor
	///parameters are object's: x coordinate, y coordinate, height, width, constant of speed in x and in y, gravity constant, distance covered by teleporting once and minimal time between teleports
	Player(int x, int y, int w, int h, double xC, double yC, double g, int tDist, int tTime):
		xConstant(xC),
		yConstant(yC),
		gravityConstant(g),
		RectangularObject(x, y, w, h),
		playerMomentum(gravityConstant),
		PLAYER_WIDTH(w),
		PLAYER_HEIGHT(h),
		teleportDistance(tDist),
		timeBetweenTeleports(tTime)

	{};

	///destructor
	virtual ~Player();

	///function responsible for jumping
	void jump();

	///funstion responsbile for moving to the right
	void moveLeft();

	///function responsbile for moving to the left
	void moveRight();

	///function responsible for teleporting
	///parameters are: direction in which teleport will take place, distance of the teleport, minimal time between two teleports in miliseconds and vector of obstacles
	void teleport(Direction dir, std::vector<RectangularObstacle*> myVector);

	///function responsbile for calculating next position of the object based on previous position and speed
	///parameters are: time between frames
	void calculateNextPosition(const double timeDifference);

	///function responsbile for printing the player onto the surface
	///parameters are: renderer to print the player on
	virtual void print(SDL_Renderer* rendererToPrintOn);

	///function responsible for checking if player collided with an obstacle and reacting accordingly to whatever part hit the obstacle
	///parameters are: obstacle to check
	void checkCollision(RectangularObject* obstacle);

	///function responsible for checking if player's side collided with an obstacle
	///parameters are: obstacle to check, side to check
	bool checkCollisionSide(RectangularObject* obstacle, Direction dir);


	///getters
	double getXConstant() { return xConstant; }
	double getYConstant() { return yConstant; }
	Momentum* getPlayerMomentum() { return &playerMomentum; }
	int getPlayerHeight() { return PLAYER_HEIGHT; }
	int getPlayerWidth() { return PLAYER_WIDTH; }
	bool getIsAlive() { return isAlive; }

	///setters
	void setIsAlive(bool newValue) { isAlive = newValue; }
	void setPlayerMomentum(Momentum newValue) { playerMomentum = newValue; }



private:

	///function responsible for checking if player is inside any obstacle from the given vector
	///parameters are: vector of obstacles to check
	bool checkIfInsideAny(std::vector <RectangularObstacle*> myVector);

	///function responsible for checking if player is inside an obstacle
	///parameters are: obstacle to check
	bool checkIfInsideOneObject(RectangularObstacle* obstacle);
};

