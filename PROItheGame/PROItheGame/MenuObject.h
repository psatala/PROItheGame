#pragma once

#include <string>

#include <SDL.h>
#include <SDL_ttf.h>

#include "GameObject.h"

class MenuObject :
	public GameObject
{
	std::string text;
	
	const int scaleTextLengthBy = 20;
public:
	void OverrideMe() {}


	//constructor
	MenuObject(int h = 0, int w = 0, std::string t = "");


	//destructor
	~MenuObject();


	//print function
	void print(SDL_Renderer* rendererToPrintOn, int elementIndex, int elementCount);

	bool checkIfClicked(int xMouse, int yMouse);
};

