///Name: TreeElement.h
///Purpose: declaration and definition of element of tree template
///Author: Piotr Satala

#pragma once

#include <vector>


template <class T>
class TreeElement
{
	const int returnValue = -1; //return value of element
	
public:

	T* ptrToObject; //pointer to object contained by element of tree

	TreeElement* ptrToFather; //pointer to father of element

	std::vector<TreeElement*> listOfSons; //vector of pointers to all sons of given element

	
	
	//constructing

	///default constructor
	TreeElement();

	///parametrised constructor
	///paramters are: pointer to an object element will be containing, return value of the element
	TreeElement(T* objectToPointTo = NULL, int valueToReturn = -1) :
		returnValue(valueToReturn),
		ptrToFather(this),
		ptrToObject(objectToPointTo) {}




	
	//destroying

	///destructor
	~TreeElement();

	
	
	//returning from menu

	///function responsible for getting the return value of element
	///function returns the return value of the element
	const int returnHere();

};




template <class T>
TreeElement<T>::TreeElement()
{
	ptrToFather = this; //set element's father to be the element
}



template <class T>
TreeElement<T>::~TreeElement()
{
	//free memory
	delete ptrToObject;

	//clear vector
	while (!listOfSons.empty())
		listOfSons.pop_back();
}



template <class T>
const int TreeElement<T>::returnHere()
{
	if (!listOfSons.empty())
		return -1; //cannot return here
	else
		return returnValue;
}

