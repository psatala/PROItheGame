///Name: Test.h
///Purpose: declaration of Test class and all its methods
///Author: Piotr Satala

#pragma once

#include <iostream>
#include <assert.h>

#include "../PROItheGame/Game.h"

class Test
{
	
	///function tests Obstacle's default constructor
	void testObsatcleDefaultConstructor();

	///function tests gravity
	void testGravity();

	///function tests movement in x direction
	void testMovementX();

	///function tests jumping
	void testJumping();

	///function tests not jumping due to lack of contact with another object
	void testNotJumping();

	///function tests teleporting
	void testTeleport();

	///function tests collision detection
	void testCollisionDetection();

	///function tests killing player by contact with "deadly" obstacle
	void testKillingPlayer();

	///function tests completing the level
	void testFinishing();

	///function tests adding element to tree template
	void testTreeAdd();

	///function tests movement in the tree
	void testTreeMove();

public:

	///constructor
	Test() {}

	///destructor
	~Test() {}

	///function calls all test methods
	void testAll();
	   	  
};

