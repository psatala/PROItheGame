#include "Tree.h"




Tree::~Tree()
{
}






//moving

void Tree::goTo(int indexOfSon)
{
	//go to one of the sons
	if (indexOfSon >= 0 && indexOfSon < (int)ptrToCurrentElement->listOfSons.size())
		ptrToCurrentElement = ptrToCurrentElement->listOfSons[indexOfSon];
	//go back to father
	else if (-1 == indexOfSon)
		ptrToCurrentElement = ptrToCurrentElement->ptrToFather;
}



void Tree::goTo(TreeElement* newCurrentElement)
{
	ptrToCurrentElement = newCurrentElement;
}





//adding new element

void Tree::add(TreeElement* addHere, TreeElement* newElement)
{
	if (newElement->ptrToFather == newElement) //check if newElement has not been added before
	{
		addHere->listOfSons.push_back(newElement); //giving father a pointer to son
		newElement->ptrToFather = addHere; //giving son a pointer to father
	}
}



void Tree::add(TreeElement* newElement)
{
	add(ptrToCurrentElement, newElement);
}





//returning

const int Tree::tryReturning()
{
	return ptrToCurrentElement->returnHere();
}






//printing

void Tree::printTree(SDL_Renderer* rendererToPrintOn)
{
	ptrToCurrentElement->printTreeElement(rendererToPrintOn);
}


//checking input

int Tree::checkInput(int xMouse, int yMouse)
{
	for (unsigned int i = 0; i < ptrToCurrentElement->listOfSons.size(); ++i)
		if (ptrToCurrentElement->listOfSons[i]->checkInput(xMouse, yMouse))
			return i;
	return -1;
}


//updating

void Tree::update(SDL_Renderer* rendererToPrintOn)
{
	printTree(rendererToPrintOn);
	SDL_RenderPresent(rendererToPrintOn);
}