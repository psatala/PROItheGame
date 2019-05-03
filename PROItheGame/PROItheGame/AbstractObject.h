#pragma once

#include <SDL.h>

#include <string>

class AbstractObject
{
public:
	AbstractObject();
	virtual ~AbstractObject() = 0;
	std::string pathToImage;
	virtual void print(SDL_Renderer* rendererToPrintOn) = 0;
	
};

