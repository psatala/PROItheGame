#pragma once

#include <vector>

#include "MenuObject.h"

class TreeElement
{
	const int returnValue = -1;

	//pointer to printing function
	void (MenuObject::*ptrToPrintFunction)(SDL_Renderer* rendererToPrintOn, int elementIndex, int elementCount);

public:

	MenuObject* ptrToObject;

	TreeElement* ptrToFather;

	std::vector<TreeElement*> listOfSons;

	
	
	//constructors

	TreeElement();
	
	TreeElement(void (MenuObject::*myFunction)(SDL_Renderer* rendererToPrintOn, int elIndex, int elCount), MenuObject* objectToPointTo, int valueToReturn = -1) :
		ptrToPrintFunction(myFunction),
		returnValue(valueToReturn),
		ptrToFather(this),
		ptrToObject(objectToPointTo) {}




	//destructor
	~TreeElement();

	
	
	//returning from menu
	const int returnHere();

	
	
	//printing
	void printTreeElement(SDL_Renderer* rendererToPrintOn);
};

