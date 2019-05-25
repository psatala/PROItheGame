///Name: MenuObject.h
///Purpose: declaration of MenuObject class - used for creating menu
///Author: Piotr Satala

#pragma once

#include <string>

#include <SDL.h>
#include <SDL_ttf.h>

#include "GameObject.h"



class MenuObject
{
	SDL_Rect objectRect; //rectangle indicating position of the object

	std::string text; //text to be printed
	
	int returnValue = -1; //value to return when chosen

	const int scaleTextLengthBy = 20; //constant to scale the text

public:

	///function overriding abstract function from base class
	void OverrideMe() {}



	///constructor
	///parameters are: height, width, text of menu object and its return value
	MenuObject(int h = 0, int w = 0, std::string t = "", int returnVal = -1);




	///destructor
	~MenuObject();



	///function responsible for printing the object of menu onto the screen in a correct place
	///parameters are: renderer to print on, index of element from a vector, total count of elements in that part of menu
	void print(SDL_Renderer* rendererToPrintOn, int elementIndex, int elementCount);



	///function responsible for checking if user clicked the object
	///parameters are: x and y coordinates of a click
	bool checkIfClicked(int xMouse, int yMouse);



	///function responsible for getting the return value of element
	///function returns the return value of the element
	int returnHere();

};

