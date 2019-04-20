#include "RectangularObstacle.h"





RectangularObstacle::~RectangularObstacle()
{
}

void RectangularObstacle::print(SDL_Renderer* rendererToPrintOn, Player* myPlayer)
{
	int RENDERER_HEIGHT;
	int RENDERER_WIDTH;
	SDL_GetRendererOutputSize(rendererToPrintOn, &RENDERER_WIDTH, &RENDERER_HEIGHT);

	int playerMoveX = (int)myPlayer->getXCoordinate() - (RENDERER_WIDTH - myPlayer->getPlayerWidth()) / 2;
	int playerMoveY = (int)myPlayer->getYCoordinate() - (RENDERER_HEIGHT - myPlayer->getPlayerHeight()) / 2;

	SDL_Rect playerRect = { (int)xCoordinate - playerMoveX, (int)yCoordinate - playerMoveY, objectWidth, objectHeight };
	SDL_SetRenderDrawColor(rendererToPrintOn, 0xFF, 0xFF, 0xFF, 0xFF);
	SDL_RenderFillRect(rendererToPrintOn, &playerRect);
}
