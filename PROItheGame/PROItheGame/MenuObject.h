///Name: MenuObject.h
///Purpose: declaration of MenuObject class - used for creating menu
///Author: Piotr Satala

#pragma once

#include <string>

#include <SDL.h>
#include <SDL_ttf.h>

#include "GameObject.h"



class MenuObject :
	public GameObject
{
	std::string text; //text to be printed
	
	const int scaleTextLengthBy = 20; //constant to scale the text

public:

	///function overriding abstract function from base class
	void OverrideMe() {}



	///constructor
	///parameters are: height, width and text of menu object
	MenuObject(int h = 0, int w = 0, std::string t = "");




	///destructor
	~MenuObject();



	///function responsible for printing the object of menu onto the screen in a correct place
	///parameters are: renderer to print on, index of element from a vector, total count of elements in that part of menu
	void print(SDL_Renderer* rendererToPrintOn, int elementIndex, int elementCount);



	///function responsible for checking if user clicked the object
	///parameters are: x and y coordinates of a click
	bool checkIfClicked(int xMouse, int yMouse);

};

