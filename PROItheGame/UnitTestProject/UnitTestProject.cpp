///Name: UnitTestProject.cpp
///Purpose: file containing main function for this project
///Author: Piotr Satala

#include "Test.h"

#undef main  //undefining main because of conflict with SDL


using namespace std;



int main()
{
	Test myInstanceOfTestClass;
	myInstanceOfTestClass.testAll();
	return 0;
}




