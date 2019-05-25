///Name: Test.cpp
///Purpose: definition of methods from Test class
///Author: Piotr Satala

#include "Test.h"

using namespace std;


void Test::testAll()
{
	testObsatcleDefaultConstructor();
	testGravity();
	testMovementX();
	testJumping();
	testNotJumping();
	testTeleport();
	testCollisionDetection();
	testKillingPlayer();
	testFinishing();
	testTreeAdd();
	testTreeMove();
}


void Test::testObsatcleDefaultConstructor()
{
	//arrange
	Obstacle firstObstacle;

	//assert
	assert(!firstObstacle.getCanItKill());

	cout << __func__ << " successful\n";
}



void Test::testGravity()
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


void Test::testMovementX()
{
	//testing movement in x

	//arrange
	const double xVelocityConstant = 1000;
	const double timeDiff = 100; //time between frames
	int initialXPos = 0;
	string behaviour = "BOUNCE"; //move left until you hit sth, then right, then left etc.

	Enemy* myEnemy = new Enemy(initialXPos, 0, 0, 0, xVelocityConstant, 0, 0, 0, 0, behaviour);

	//act
	myEnemy->applyBehaviour(vector<GameObject*>());
	myEnemy->calculateNextPosition(timeDiff);

	//assert
	assert(myEnemy->getXCoordinate() == initialXPos - xVelocityConstant * timeDiff);

	cout << __func__ << " successful\n";

	delete myEnemy;

}

void Test::testJumping()
{
	//testing jumping

	//arrange
	int startingYPosition = 0;
	int playerWidth = 100;
	int playerHeight = 100;
	string behaviour = "JUMP";
	const double gForce = 0.4;
	const double yVelocityConstant = -1400; //value is negative -> this velocity vector points towards the top of the screen
	const double timeDiff = 15; //time between frames

	int obstacleX = -50;
	int obstacleY = 150;
	int obstacleWidth = 200;
	int obstacleHeight = 10000;

	Enemy* myEnemy = new Enemy(0, startingYPosition, playerWidth, playerHeight, 0, yVelocityConstant, gForce, 0, 0, behaviour);
	Obstacle* myObstacle = new Obstacle(obstacleX, obstacleY, obstacleWidth, obstacleHeight, 0, 0);

	//act
	myEnemy->calculateNextPosition(timeDiff); //wait for enemy to land on obstacle
	myEnemy->checkCollision(myObstacle); //update position through collision check
	myEnemy->applyBehaviour(vector<GameObject*>()); //jump
	myEnemy->calculateNextPosition(timeDiff); //wait for enemy to jump really high



	//assert
	assert(myEnemy->getYCoordinate() < startingYPosition);

	cout << __func__ << " successful\n";

	delete myEnemy;
	delete myObstacle;
}

void Test::testNotJumping()
{
	//testing not being able to jump due to lack of contact with another object

	//arrange
	int startingYPosition = 123;
	const double yVelocityConstant = -14; //value is negative -> this velocity vector points towards the top of the screen
	const double timeDiff = 100; //time between frames
	string behaviour = "JUMP";

	Enemy* myEnemy = new Enemy(0, startingYPosition, 0, 0, 0, yVelocityConstant, 0, 0, 0, behaviour);

	//act
	myEnemy->applyBehaviour(vector<GameObject*>());
	myEnemy->calculateNextPosition(timeDiff);

	//assert
	assert(myEnemy->getYCoordinate() == startingYPosition); //nothing should change, since the enemy does not have contact with an object to jump off of

	cout << __func__ << " successful\n";

	delete myEnemy;
}


void Test::testTeleport()
{
	//testing teleport

	//arrange
	int startingYPosition = 123; //starting position for the player
	int teleportDistance = 100; //distance covered by a single teleport
	int timeBetweenTeleports = 1000;

	string behaviour = "TELEPORT_UP";

	Enemy *myEnemy = new Enemy(0, startingYPosition, 0, 0, 0, 0, 0, teleportDistance, timeBetweenTeleports, behaviour);


	//act
	myEnemy->applyBehaviour(vector<GameObject*>());

	//assert
	assert(myEnemy->getYCoordinate() == startingYPosition - teleportDistance);

	cout << __func__ << " successful\n";

	delete myEnemy;
}





void Test::testCollisionDetection()
{
	//testing collision detection

	//arrange
	int playerWidth = 100;
	int playerHeight = 100;
	int obstacleX = -50;
	int obstacleY = 50;
	int obstacleWidth = 200;
	int obstacleHeight = 1000;

	//act
	HumanPlayer* myPlayer = new HumanPlayer(0, 0, playerWidth, playerHeight, 0, 0, 0, 0, 0);
	Obstacle* myObstacle = new Obstacle(obstacleX, obstacleY, obstacleWidth, obstacleHeight, 0, 0);

	//assert
	assert(myPlayer->checkCollisionSide(myObstacle, GameObject::DOWN));

	cout << __func__ << " successful\n";

	delete myPlayer;
	delete myObstacle;
}



void Test::testKillingPlayer()
{
	//testing killing player

	//arrange
	int playerWidth = 100;
	int playerHeight = 100;
	int obstacleX = -50;
	int obstacleY = 50;
	int obstacleWidth = 200;
	int obstacleHeight = 1000;
	bool canObstacleKill = true;

	//act
	HumanPlayer* myPlayer = new HumanPlayer(0, 0, playerWidth, playerHeight, 0, 0, 0, 0, 0);
	Obstacle* myObstacle = new Obstacle(obstacleX, obstacleY, obstacleWidth, obstacleHeight, canObstacleKill, 0);
	myPlayer->checkCollision(myObstacle); //checking collision with myObstacle

	//assert
	assert(!myPlayer->getIsAlive());

	cout << __func__ << " successful\n";

	delete myPlayer;
	delete myObstacle;
}


void Test::testFinishing()
{
	//testing finishing level

	//arrange
	int playerWidth = 100;
	int playerHeight = 100;
	int obstacleX = -50;
	int obstacleY = 50;
	int obstacleWidth = 200;
	int obstacleHeight = 1000;
	bool isItFinishLine = true;

	//act
	HumanPlayer* myPlayer = new HumanPlayer(0, 0, playerWidth, playerHeight, 0, 0, 0, 0, 0);
	Obstacle* myObstacle = new Obstacle(obstacleX, obstacleY, obstacleWidth, obstacleHeight, 0, isItFinishLine);
	myPlayer->checkCollision(myObstacle); //checking collision with myObstacle

	//assert
	assert(myPlayer->getHasFinished());

	cout << __func__ << " successful\n";

	delete myPlayer;
	delete myObstacle;
}


void Test::testTreeAdd()
{
	//testing additions to tree

	//arrange
	Tree<int> myTree;
	int* someIntPtr = new int(1);

	//act
	myTree.add(someIntPtr);

	//assert
	assert(*myTree.ptrToCurrentElement->listOfSons[0]->ptrToObject == 1);

	cout << __func__ << " successful\n";
}

void Test::testTreeMove()
{
	//testing movement in the tree

	//arrange
	Tree<int>* myTree = new Tree<int>;
	TreeElement<int>* root = myTree->ptrToCurrentElement;
	myTree->add(new int(1));

	//act
	myTree->goTo(0);

	//assert
	assert(myTree->ptrToCurrentElement->ptrToFather == root);

	cout << __func__ << " successful\n";

	delete myTree;
}

