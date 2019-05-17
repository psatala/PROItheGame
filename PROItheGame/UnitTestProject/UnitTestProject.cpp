#include <iostream>
#include <assert.h>
#include "../PROItheGame/BasicFunctions.h"
#undef main



using namespace std;



void testObsatcleDefaultConstructor()
{
	//arrange
	Obstacle firstObstacle;

	//assert
	assert(!firstObstacle.getCanItKill());

	cout << __func__ << " successful\n";
}



void testGravity()
{
	//testing gravity

	//arrange
	double gForce = 9.81; //our gForce
	const double timeDiff = 100; //time between frames
	int initialYPos = 0;
	HumanPlayer *myPlayer = new HumanPlayer(0, initialYPos, 0, 0, 0, 0, gForce, 0, 0);
	
	//act
	myPlayer->calculateNextPosition(timeDiff);

	//assert
	assert(myPlayer->getYCoordinate() > initialYPos);

	cout << __func__ << " successful\n";

	delete myPlayer;
}



void testTeleportUP()
{
	//testing teleport

	//arrange
	int startingYPosition = 123; //starting position for the player
	int teleportDistance = 100; //distance covered by a single teleport
	int timeBetweenTeleports = 1000;
	
	string behaviour = "TELEPORT_UP";
	
	Enemy *myEnemy = new Enemy(0, startingYPosition, 0, 0, 0, 0, 0, teleportDistance, timeBetweenTeleports, behaviour);


	//act
	myEnemy->applyBehaviour();
	
	//assert
	assert(myEnemy->getYCoordinate() == startingYPosition - teleportDistance);

	cout << __func__ << " successful\n";

	delete myEnemy;
}



void testTeleportDOWN()
{
	//testing teleport

	//arrange
	int startingYPosition = 123; //starting position for the player
	int teleportDistance = 100; //distance covered by a single teleport
	int timeBetweenTeleports = 1000;

	string behaviour = "TELEPORT_DOWN";

	Enemy *myEnemy = new Enemy(0, startingYPosition, 0, 0, 0, 0, 0, teleportDistance, timeBetweenTeleports, behaviour);


	//act
	myEnemy->applyBehaviour();

	//assert
	assert(myEnemy->getYCoordinate() == startingYPosition + teleportDistance);

	cout << __func__ << " successful\n";

	delete myEnemy;
}



void testTeleportLEFT()
{
	//testing teleport

	//arrange
	int startingXPosition = 123; //starting position for the player
	int teleportDistance = 100; //distance covered by a single teleport
	int timeBetweenTeleports = 1000;

	string behaviour = "TELEPORT_LEFT";

	Enemy *myEnemy = new Enemy(startingXPosition, 0, 0, 0, 0, 0, 0, teleportDistance, timeBetweenTeleports, behaviour);


	//act
	myEnemy->applyBehaviour();

	//assert
	assert(myEnemy->getXCoordinate() == startingXPosition - teleportDistance);

	cout << __func__ << " successful\n";

	delete myEnemy;
}



void testTeleportRIGHT()
{
	//testing teleport

	//arrange
	int startingXPosition = 123; //starting position for the player
	int teleportDistance = 100; //distance covered by a single teleport
	int timeBetweenTeleports = 1000;

	string behaviour = "TELEPORT_RIGHT";

	Enemy *myEnemy = new Enemy(startingXPosition, 0, 0, 0, 0, 0, 0, teleportDistance, timeBetweenTeleports, behaviour);


	//act
	myEnemy->applyBehaviour();

	//assert
	assert(myEnemy->getXCoordinate() == startingXPosition + teleportDistance);

	cout << __func__ << " successful\n";

	delete myEnemy;
}


int main()
{
	//main function calling all test functions
	testObsatcleDefaultConstructor();
	testGravity();
	testTeleportUP();
	testTeleportDOWN();
	testTeleportLEFT();
	testTeleportRIGHT();
	return 0;
}
