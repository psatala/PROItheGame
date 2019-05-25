///Name: TreeElement.h
///Purpose: declaration and definition of element of tree template
///Author: Piotr Satala

#pragma once

#include <vector>


template <class T>
class TreeElement
{
	
public:

	T* ptrToObject; //pointer to object contained by element of tree

	TreeElement* ptrToFather; //pointer to father of element

	std::vector<TreeElement*> listOfSons; //vector of pointers to all sons of given element

	
	
	//constructing

	///constructor
	///paramters are: pointer to an object element will be containing
	TreeElement(T* objectToPointTo = NULL) :
		ptrToFather(this),
		ptrToObject(objectToPointTo) {}

	///copy constructor
	///constructing copies is not allowed
	TreeElement(const TreeElement<T>& other) = delete;


	
	//destroying

	///destructor
	~TreeElement();


	//operators

	///copy assignment operator
	///making copies is not allowed
	TreeElement<T>& operator=(const TreeElement<T>& other) = delete;

};




template <class T>
TreeElement<T>::~TreeElement()
{
	//free memory
	delete ptrToObject;
	ptrToObject = 0;

	//clear vector
	while (!listOfSons.empty())
		listOfSons.pop_back();
}




