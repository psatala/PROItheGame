#pragma once

#include <string>

#include <SDL.h>

class MenuObject
{
	std::string text;
	
	int height;
	int width;
public:

	//constructor
	MenuObject(int h = 0, int w = 0, std::string t = "") :
		height(h),
		width(w),
		text(t) {}

	//destructor
	~MenuObject();

	//setters
	void setHeight(int newValue) { height = newValue; }
	void setWidth(int newValue) { width = newValue; }

	//getters
	int getHeight() { return height; }
	int getWidth() { return width; }

	void print(SDL_Renderer* rendererToPrintOn, int elementIndex, int elementCount) {}
};

