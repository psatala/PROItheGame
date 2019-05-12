#pragma once

#include "TreeElement.h"

class Tree
{
	TreeElement* ptrToCurrentElement;
public:
	Tree();
	void apply(TreeElement* newCurrentElement);
	virtual ~Tree();
};

