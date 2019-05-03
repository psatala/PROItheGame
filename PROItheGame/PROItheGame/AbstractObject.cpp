#include "AbstractObject.h"



AbstractObject::AbstractObject()
{
}


AbstractObject::~AbstractObject()
{
}

void AbstractObject::update(const double TimeDifference, std::vector<AbstractObject*> myVector, SDL_Renderer* rendererToPrintOn, HumanPlayer* myPlayer)
{
	calculateNextPosition(TimeDifference);
	checkAllCollisions(myVector);
	print(rendererToPrintOn, myPlayer);
}
