#include "Tree.h"



Tree::Tree()
{
}


Tree::~Tree()
{
}

void Tree::apply(TreeElement* newCurrentElement)
{
	ptrToCurrentElement = newCurrentElement;
}