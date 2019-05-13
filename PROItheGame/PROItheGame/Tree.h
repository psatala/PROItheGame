#pragma once

#include "TreeElement.h"
#include "BasicFunctions.h"

class Tree
{
	TreeElement* ptrToCurrentElement;
public:
	
	//constructor
	Tree(TreeElement* firstElement = NULL):
		ptrToCurrentElement(firstElement) {}


	//destructor
	~Tree();


	//moving
	void goTo(int indexOfSon);
	void goTo(TreeElement* newCurrentElement);


	//adding new element
	void add(TreeElement* addHere, TreeElement* newElement);
	void add(TreeElement* newElement);


	//returning
	const int tryReturning();


	//printing
	void printTree(SDL_Renderer* rendererToPrintOn);


	//checking input
	int checkInput(int xMouse, int yMouse);


	//updating
	void update(SDL_Renderer* rendererToPrintOn);
};

