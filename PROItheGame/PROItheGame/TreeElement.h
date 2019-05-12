#pragma once

#include <vector>

#include "MenuObject.h"

class TreeElement
{
	MenuObject* ptrToObject;
	std::vector<MenuObject*> listOfSons;

	void (MenuObject::*ptrToPrintFunction)(SDL_Renderer* rendererToPrintOn, int xPos, int yPos);

public:
	TreeElement();
	
	TreeElement(void (MenuObject::*myFunction)(SDL_Renderer* rendererToPrintOn, int xPos, int yPos));
		
	virtual ~TreeElement();

	void printTreeElement(SDL_Renderer* rendererToPrintOn);
};

