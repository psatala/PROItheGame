///Name: Tree.h
///Purpose: declaration and definition of tree template
///Author: Piotr Satala

#pragma once

#include "TreeElement.h"

template <class T>
class Tree
{
	
public:
	//pointer to current element
	TreeElement<T>* ptrToCurrentElement;



	//constructing

	///constructor
	///parameters are: pointer to first element of tree
	Tree(TreeElement<T>* firstElement = NULL):
		ptrToCurrentElement(firstElement) {}





	//destroying

	///destructor
	~Tree();

	///auxiliary function called in destructor responsible for freeing the memory of given element of tree
	///parameters are: pointer to element of tree
	void freeMemory(TreeElement<T>* ptrToSomeElement);





	//moving

	///function responsible for moving the current element to one of its sons or its father
	///parameters are: index of son to go to or -1, if the target is father
	void goTo(int indexOfSon);

	///function responsible for moving the current element to a new element of tree
	///prameters are: pointer to new element of tree
	void goTo(TreeElement<T>* newCurrentElement);





	//adding new element
	
	///function responsible for adding new element to the given element of tree
	///parameters are: pointer to element to which we will be adding, pointer to new element (to be added)
	void add(TreeElement<T>* addHere, TreeElement<T>* newElement);

	///function responsible for adding new element to current element
	///parameters are: pointer to new element (to be added)
	void add(TreeElement<T>* newElement);





	//returning
	
	///function responsible for getting the return value of current element
	///function returns the retun value of current element
	const int tryReturning();


};



template <class T>
Tree<T>::~Tree()
{
	TreeElement<T>* auxiliaryPtr = ptrToCurrentElement;
	goTo(-1);
	
	//make ptrToCurrentElement root
	while (ptrToCurrentElement != auxiliaryPtr)
	{
		auxiliaryPtr = ptrToCurrentElement;
		goTo(-1);
	}

	//free all memory by DFS search
	freeMemory(ptrToCurrentElement);

}


template <class T>
void Tree<T>::freeMemory(TreeElement<T>* ptrToSomeElement)
{
	//calling this function recurrently for all of the given element's sons
	for (unsigned int i = 0; i < ptrToSomeElement->listOfSons.size(); ++i)
		freeMemory(ptrToSomeElement->listOfSons[i]);

	//freeing the given element
	delete ptrToSomeElement;
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


