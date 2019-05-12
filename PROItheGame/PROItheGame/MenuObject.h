#pragma once

#include <string>

#include "GameObject.h"

class MenuObject :
	public GameObject
{
	std::string text;
public:
	MenuObject();

	virtual ~MenuObject();

	void print(SDL_Renderer* rendererToPrintOn, int xPos, int yPos);
};

