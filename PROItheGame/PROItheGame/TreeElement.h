#pragma once

#include <vector>


template <class T>
class TreeElement
{
	const int returnValue = -1;
	
public:

	T* ptrToObject;

	TreeElement* ptrToFather;

	std::vector<TreeElement*> listOfSons;

	
	
	//constructors

	TreeElement();
	


	TreeElement(T* objectToPointTo = NULL, int valueToReturn = -1) :
		returnValue(valueToReturn),
		ptrToFather(this),
		ptrToObject(objectToPointTo) {}




	
	//destructor
	~TreeElement();

	
	
	//returning from menu
	const int returnHere();

};




template <class T>
TreeElement<T>::TreeElement()
{
	ptrToFather = this;
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

