#pragma once

#include <vector>

#include "MenuObject.h"

class TreeElement
{
	const int returnValue = -1;

	//pointer to printing function
	void (MenuObject::*ptrToPrintFunction)(SDL_Renderer* rendererToPrintOn, int elementIndex, int elementCount);

	//pointer to check if clicked function
	bool (MenuObject::*ptrToInputCheckingFunction)(int xMouse, int yMouse);

public:

	MenuObject* ptrToObject;

	TreeElement* ptrToFather;

	std::vector<TreeElement*> listOfSons;

	
	
	//constructors

	TreeElement();
	


	TreeElement(void (MenuObject::*myPrintingFunction)(SDL_Renderer* rendererToPrintOn, int elIndex, int elCount),
				bool (MenuObject::*myInputCheckingFunction)(int xM, int yM),
				MenuObject* objectToPointTo, int valueToReturn = -1) :

		ptrToPrintFunction(myPrintingFunction),
		ptrToInputCheckingFunction(myInputCheckingFunction),
		returnValue(valueToReturn),
		ptrToFather(this),
		ptrToObject(objectToPointTo) {}




	
	//destructor
	~TreeElement();

	
	
	//returning from menu
	const int returnHere();

	
	
	//printing
	void printTreeElement(SDL_Renderer* rendererToPrintOn);


	//checking input
	bool checkInput(int xMouse, int yMouse);

};

