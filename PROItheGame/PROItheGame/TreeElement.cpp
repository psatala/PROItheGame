#include "TreeElement.h"

using namespace std;

TreeElement::TreeElement()
{
}

TreeElement::TreeElement(void (MenuObject::*myFunction)(SDL_Renderer* rendererToPrintOn, int xPos, int yPos))
{
	ptrToPrintFunction = myFunction;
}

TreeElement::~TreeElement()
{
}

void TreeElement::printTreeElement(SDL_Renderer* rendererToPrintOn)
{
	for (vector<MenuObject*>::iterator it = listOfSons.begin(); it != listOfSons.end(); ++it)
		((*it)->*ptrToPrintFunction)(rendererToPrintOn, 0, 0);
}