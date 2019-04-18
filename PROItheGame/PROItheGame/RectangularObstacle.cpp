#include "RectangularObstacle.h"





RectangularObstacle::~RectangularObstacle()
{
}

void RectangularObstacle::print(SDL_Renderer* rendererToPrintOn)
{
	SDL_Rect playerRect = { (int)xCoordinate, (int)yCoordinate, objectWidth, objectHeight };
	SDL_SetRenderDrawColor(rendererToPrintOn, 0xFF, 0xFF, 0xFF, 0xFF);
	SDL_RenderFillRect(rendererToPrintOn, &playerRect);
}
