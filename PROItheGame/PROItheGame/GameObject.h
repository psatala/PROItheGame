///Name: GameObject.h
///Purpose: declaration and definition of abstract GameObject class
///Author: Piotr Satala

#pragma once

#include <SDL.h>

#include <vector>
#include <tuple>
#include <math.h>

#include "Camera.h"



class GameObject
{
protected:
	
	//coordinates in space
	double xCoordinate;
	double yCoordinate;

	//size of object
	int objectHeight;
	int objectWidth;

	//color of object
	std::tuple<unsigned int, unsigned int, unsigned int> color;

	//boolean determining whether or not this object is alive
	bool isAlive = true;


public:

	///function ensures the class is abstract
	virtual void OverrideMe() = 0;



	///enum indicating direction
	enum Direction { UP, DOWN, LEFT, RIGHT };


	
	///constructor
	///parameters are: x and y coordinates, width and height of the object
	GameObject(int x = 0, int y = 0, int w = 0, int h = 0) : xCoordinate(x), yCoordinate(y), objectWidth(w), objectHeight(h) {}; 
	


	///destructor
	virtual ~GameObject() {}
	




	//setters

	///setter for x coordinate
	void setXCoordinate(double newValue) { xCoordinate = newValue; }

	///setter for y coordinate
	void setYCoordinate(double newValue) { yCoordinate = newValue; }

	///setter for object's height
	void setObjectHeight(int newValue) { objectHeight = newValue; }

	///setter for object's width
	void setObjectWidth(int newValue) { objectWidth = newValue; }

	///setter for isAlive
	void setIsAlive(bool newValue) { isAlive = newValue; }
	
	

	//getters
	
	///getter for x coordinate
	double getXCoordinate() { return xCoordinate; }

	///getter for y coordinate
	double getYCoordinate() { return yCoordinate; }

	///gettter for object's height
	int getObjectHeight() { return objectHeight; }

	///getter for object's width
	int getObjectWidth() { return objectWidth; }

	///getter for isAlive
	bool getIsAlive() { return isAlive; }


	

	//methods to override

	///function responsible for calculating next position of the object after givne time
	///parameters are: time which passed since previous position
	///function body is empty, since its made to be overridden
	virtual void calculateNextPosition(const double timeDifference) {}


	///function responsible for checking collision with another GameObject
	///parameters are: pointer to another GameObject
	///function body is empty, since its made to be overridden
	virtual void checkCollision(GameObject* other) {}


	///function responsible for setting the color to print in
	///function body is empty, since its made to be overridden
	virtual void setColor() {}


	///function responsible for applying behaviour for the player
	///parameters are: vector of all objects
	///function body is empty, since its made to be overridden
	virtual void applyBehaviour(std::vector <GameObject*> myVector) {}




	//other

	
	///function responsible for checking if player's side collided with an obstacle
	///parameters are: obstacle to check, side to check
	bool checkCollisionSide(GameObject* obstacle, Direction dir);


	///function responsible for printing the object onto the screen in relation to camera position
	///parameters are: renderer to print on, camera to relate to
	void print(SDL_Renderer* renderer, Camera* myCamera);
};

