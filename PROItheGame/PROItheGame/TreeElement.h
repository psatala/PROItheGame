#pragma once

#include <vector>


template <class T>
class TreeElement
{
	const int returnValue = -1;

	//pointer to printing function
	void (<T>::*ptrToPrintFunction)(SDL_Renderer* rendererToPrintOn, int elementIndex, int elementCount);

	//pointer to check if clicked function
	bool (<T>::*ptrToInputCheckingFunction)(int xMouse, int yMouse);

public:

	TreeElement<T>* ptrToObject;

	TreeElement* ptrToFather;

	std::vector<TreeElement*> listOfSons;

	
	
	//constructors

	TreeElement();
	


	TreeElement(void (<T>::*myPrintingFunction)(SDL_Renderer* rendererToPrintOn, int elIndex, int elCount),
				bool (<T>::*myInputCheckingFunction)(int xM, int yM),
				<T>* objectToPointTo, int valueToReturn = -1) :

		ptrToPrintFunction(myPrintingFunction),
		ptrToInputCheckingFunction(myInputCheckingFunction),
		returnValue(valueToReturn),
		ptrToFather(this),
		ptrToObject(objectToPointTo) {}




	
	//destructor
	~TreeElement();

	
	
	//returning from menu
	const int returnHere();

	
	
	//printing
	void printTreeElement(SDL_Renderer* rendererToPrintOn);


	//checking input
	bool checkInput(int xMouse, int yMouse);

};


template <class T>
TreeElement<T>::TreeElement()
{
	ptrToFather = this;
}



template <class T>
TreeElement<T>::~TreeElement()
{
}



template <class T>
const int TreeElement<T>::returnHere()
{
	if (!listOfSons.empty())
		return -1; //cannot return here
	else
		return returnValue;
}



template <class T>
void TreeElement<T>::printTreeElement(SDL_Renderer* rendererToPrintOn)
{
	for (unsigned int i = 0; i < listOfSons.size(); ++i)
		(listOfSons[i]->ptrToObject->*ptrToPrintFunction)(rendererToPrintOn, i, listOfSons.size());
}



template <class T>
bool TreeElement<T>::checkInput(int xMouse, int yMouse)
{
	return (this->ptrToObject->*ptrToInputCheckingFunction)(xMouse, yMouse);
}