// UnitTestProject.cpp : This file contains the 'main' function. Program execution begins and ends there.
//


#include <iostream>
#include <assert.h>
#include "../PROItheGame/BasicFunctions.h"
#undef main

using namespace std;

void test01()
{
	Obstacle firstObstacle;
	assert(firstObstacle.getCanItKill() == false);
}

int main()
{
	test01();
	return 0;
}
