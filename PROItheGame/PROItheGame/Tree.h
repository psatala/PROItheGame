#pragma once

#include "TreeElement.h"

template <class T>
class Tree
{
	TreeElement<T>* ptrToCurrentElement;
public:
	
	//constructor
	Tree(TreeElement<T>* firstElement = NULL):
		ptrToCurrentElement(firstElement) {}


	//destructor
	~Tree();


	//moving
	void goTo(int indexOfSon);
	void goTo(TreeElement<T>* newCurrentElement);


	//adding new element
	void add(TreeElement<T>* addHere, TreeElement<T>* newElement);
	void add(TreeElement<T>* newElement);


	//returning
	const int tryReturning();


	//printing
	void printTree(SDL_Renderer* rendererToPrintOn);


	//checking input
	int checkInput(int xMouse, int yMouse);


	//updating
	void update(SDL_Renderer* rendererToPrintOn);

};





template <class T>
Tree<T>::~Tree()
{
}




//moving

template <class T>
void Tree<T>::goTo(int indexOfSon)
{
	//go to one of the sons
	if (indexOfSon >= 0 && indexOfSon < (int)ptrToCurrentElement->listOfSons.size())
		ptrToCurrentElement = ptrToCurrentElement->listOfSons[indexOfSon];
	//go back to father
	else if (-1 == indexOfSon)
		ptrToCurrentElement = ptrToCurrentElement->ptrToFather;
}



template <class T>
void Tree<T>::goTo(TreeElement<T>* newCurrentElement)
{
	ptrToCurrentElement = newCurrentElement;
}





//adding new element

template <class T>
void Tree<T>::add(TreeElement<T>* addHere, TreeElement<T>* newElement)
{
	if (newElement->ptrToFather == newElement) //check if newElement has not been added before
	{
		addHere->listOfSons.push_back(newElement); //giving father a pointer to son
		newElement->ptrToFather = addHere; //giving son a pointer to father
	}
}



template <class T>
void Tree<T>::add(TreeElement<T>* newElement)
{
	add(ptrToCurrentElement, newElement);
}





//returning

template <class T>
const int Tree<T>::tryReturning()
{
	return ptrToCurrentElement->returnHere();
}






//printing

template <class T>
void Tree<T>::printTree(SDL_Renderer* rendererToPrintOn)
{
	ptrToCurrentElement->printTreeElement(rendererToPrintOn);
}




//checking input

template <class T>
int Tree<T>::checkInput(int xMouse, int yMouse)
{
	for (unsigned int i = 0; i < ptrToCurrentElement->listOfSons.size(); ++i)
		if (ptrToCurrentElement->listOfSons[i]->checkInput(xMouse, yMouse))
			return i;
	return -1;
}


//updating

template <class T>
void Tree<T>::update(SDL_Renderer* rendererToPrintOn)
{
	printTree(rendererToPrintOn);
	SDL_RenderPresent(rendererToPrintOn);
}