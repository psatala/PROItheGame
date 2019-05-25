///Name: Tree.h
///Purpose: declaration and definition of tree template
///Author: Piotr Satala

#pragma once

#include "TreeElement.h"

template <class T>
class Tree
{
	
	
	///auxiliary function called in destructor responsible for freeing the memory of given element of tree
	///parameters are: pointer to element of tree
	void freeMemory(TreeElement<T>* ptrToSomeElement);


public:
	//pointer to current element
	TreeElement<T>* ptrToCurrentElement;



	//constructing

	///constructor
	Tree(T* firstElement = new T);

	///copy constructor
	///constructing copies is not allowed
	Tree(const Tree<T>& other) = delete;


	//destroying

	///destructor
	~Tree();




	//moving

	///function responsible for moving the current element to one of its sons or its father
	///parameters are: index of son to go to or -1, if the target is father
	void goTo(int indexOfSon);

	///function responsible for moving the current element to a new element of tree
	///prameters are: pointer to new element of tree
	void goTo(TreeElement<T>* newCurrentElement);





	//adding new element
	
	///function responsible for adding new element to the given element of tree
	///parameters are: pointer to element to which we will be adding, pointer to new object (to be added)
	void add(TreeElement <T>* addHere, T* newElement);

	///function responsible for adding new element to current element
	///parameters are: pointer to new object (to be added)
	void add(T* newElement);




	//operators

	///copy assignment operator
	///making copies is not allowed
	Tree<T>& operator=(const Tree<T>& other) = delete;


};



template <class T>
Tree<T>::Tree(T* firstElement)
{
	TreeElement<T>* root = new TreeElement<T>(firstElement);
	ptrToCurrentElement = root;
}




template <class T>
Tree<T>::~Tree()
{
	if (ptrToCurrentElement)
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
}




template <class T>
void Tree<T>::freeMemory(TreeElement<T>* ptrToSomeElement)
{
	//calling this function recurrently for all of the given element's sons
	for (unsigned int i = 0; i < ptrToSomeElement->listOfSons.size(); ++i)
		freeMemory(ptrToSomeElement->listOfSons[i]);

	//deallocating the given element
	delete ptrToSomeElement;
	ptrToSomeElement = 0;
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
void Tree<T>::add(TreeElement<T>* addHere, T* newElement)
{
	TreeElement<T>* temporary = new TreeElement<T>(newElement);
	addHere->listOfSons.push_back(temporary); //giving father a pointer to son
	temporary->ptrToFather = addHere; //giving son a pointer to father
}


template <class T>
void Tree<T>::add(T* newElement)
{
	if (ptrToCurrentElement->ptrToObject)
		add(ptrToCurrentElement, newElement);
	else
		ptrToCurrentElement->ptrToObject = newElement;
}


