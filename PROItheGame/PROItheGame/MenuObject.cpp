#include "MenuObject.h"





MenuObject::MenuObject(int h, int w, std::string t)
{
	objectHeight = h;
	objectWidth = w;
	text = t;
}



MenuObject::~MenuObject()
{
}


void MenuObject::print(SDL_Renderer* rendererToPrintOn, int elementIndex, int elementCount)
{
	//box

	//getting renderer size
	int RENDERER_HEIGHT;
	int RENDERER_WIDTH;
	SDL_GetRendererOutputSize(rendererToPrintOn, &RENDERER_WIDTH, &RENDERER_HEIGHT);

	//calculating x and y coordinates
	xCoordinate = (RENDERER_WIDTH - objectWidth) / 2;
	yCoordinate = RENDERER_HEIGHT / 2 + 2 * objectHeight * (elementIndex - elementCount / 2);

	//applying
	SDL_Rect myRect = { (int)xCoordinate, (int)yCoordinate, objectWidth, objectHeight};
	SDL_SetRenderDrawColor(rendererToPrintOn, 0xFF, 0xFF, 0xFF, 0xFF);
	SDL_RenderFillRect(rendererToPrintOn, &myRect);
	
	
	//text
	int newWidth = text.size() * scaleTextLengthBy; //width proportional to width of the text
	TTF_Font* myFont = TTF_OpenFont("Fonts/OpenSans-Semibold.ttf", 1000);
	SDL_Color Black = { 0, 0, 0};
	SDL_Surface* surfaceMessage = TTF_RenderText_Solid(myFont, text.c_str(), Black);
	SDL_Texture* Message = SDL_CreateTextureFromSurface(rendererToPrintOn, surfaceMessage);
	SDL_Rect innerRect = { (int)xCoordinate + objectWidth /2 - newWidth / 4, (int)yCoordinate + objectHeight / 4, newWidth / 2, objectHeight / 2 };
	SDL_RenderCopy(rendererToPrintOn, Message, NULL, &innerRect);
	

}



bool MenuObject::checkIfClicked(int xMouse, int yMouse)
{
	return xCoordinate < xMouse && xCoordinate + objectWidth > xMouse
		&& yCoordinate < yMouse && yCoordinate + objectHeight > yMouse;
}