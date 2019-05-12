#include "TreeElement.h"

using namespace std;

TreeElement::TreeElement()
{
	ptrToFather = this;
}

TreeElement::~TreeElement()
{
}


const int TreeElement::returnHere()
{
	if (!listOfSons.empty())
		return -1; //cannot return here
	else
		return returnValue;
}

void TreeElement::printTreeElement(SDL_Renderer* rendererToPrintOn)
{
	for (unsigned int i = 0; i < listOfSons.size(); ++i)
		(listOfSons[i]->ptrToObject->*ptrToPrintFunction)(rendererToPrintOn, i, listOfSons.size());
}