///Name: MenuObject.cpp
///Purpose: definition of methods from MenuObject class
///Author: Piotr Satala

#include "MenuObject.h"





MenuObject::MenuObject(int h, int w, std::string t, int returnVal)
{
	objectRect.h = h;
	objectRect.w = w;
	text = t;
	returnValue = returnVal;
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


	//equation for determining x coordinate
	objectRect.x = (RENDERER_WIDTH - objectRect.w) / 2;	
	//equation for determining y coordinate based on how many elements are in this part of the menu and the index of this element
	objectRect.y = (int)((double)RENDERER_HEIGHT / 2 + 2 * (double)objectRect.h * ((double)elementIndex - (double)elementCount / 2));


	//applying
	SDL_Rect myRect = { objectRect.x, objectRect.y, objectRect.w, objectRect.h};
	SDL_SetRenderDrawColor(rendererToPrintOn, 0xFF, 0xFF, 0xFF, 0xFF);
	SDL_RenderFillRect(rendererToPrintOn, &myRect);
	
	
	//text
	int newWidth = text.size() * scaleTextLengthBy; //width proportional to width of the text
	TTF_Font* myFont = TTF_OpenFont("Fonts/OpenSans-Semibold.ttf", 1000);
	SDL_Color Black = { 0, 0, 0};
	SDL_Surface* surfaceMessage = TTF_RenderText_Solid(myFont, text.c_str(), Black);
	SDL_Texture* Message = SDL_CreateTextureFromSurface(rendererToPrintOn, surfaceMessage);
	SDL_Rect innerRect = { objectRect.x + objectRect.w /2 - newWidth / 4, objectRect.y + objectRect.h / 4, newWidth / 2, objectRect.h / 2 };
	SDL_RenderCopy(rendererToPrintOn, Message, NULL, &innerRect);
	
	SDL_DestroyTexture(Message);
	Message = NULL;

	SDL_FreeSurface(surfaceMessage);
	surfaceMessage = NULL;

	TTF_CloseFont(myFont);
	myFont = NULL;
}




bool MenuObject::checkIfClicked(int xMouse, int yMouse)
{
	return objectRect.x < xMouse && objectRect.x + objectRect.w > xMouse     //check x coordinate
		&& objectRect.y < yMouse && objectRect.y + objectRect.h > yMouse;   //check y coordinate
}



int MenuObject::returnHere()
{
	return returnValue;
}