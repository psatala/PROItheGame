#pragma once

#include <SDL.h>
#include <string>
#include <vector>

///forward declaration of HumanPlayer class
class HumanPlayer;

class AbstractObject
{
	std::string pathToImage;

public:
	AbstractObject();
	
	virtual ~AbstractObject() = 0;

	virtual void update(const double TimeDifference, std::vector<AbstractObject*> myVector, SDL_Renderer* rendererToPrintOn, HumanPlayer* myPlayer);

	
protected:
	virtual void print(SDL_Renderer* rendererToPrintOn, HumanPlayer* myPlayer) = 0;

	virtual void calculateNextPosition(const double TimeDifference) = 0;

	virtual void checkAllCollisions(std::vector<AbstractObject*> myVector) = 0;

	virtual void checkCollision(AbstractObject* myObject) {}

	virtual void checkCollision(HumanPlayer* myPlayer) = 0;
};

