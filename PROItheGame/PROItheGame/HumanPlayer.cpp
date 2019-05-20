///Name: HumanPlayer.cpp
///Purpose: definition of methods from HumanPlayer class
///Author: Piotr Satala

#include "HumanPlayer.h"




	
void HumanPlayer::applyInput(std::vector <GameObject*> myVector)
{
	//getting keyboard state
	const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);

	//jump
	if (currentKeyStates[SDL_SCANCODE_W])
		jump();

	//no horizontal movement
	if (!currentKeyStates[SDL_SCANCODE_A] && !currentKeyStates[SDL_SCANCODE_D])
		stopX();
	//horizontal movement
	else if (currentKeyStates[SDL_SCANCODE_A] && !currentKeyStates[SDL_SCANCODE_D])
		moveLeft();
	else if (!currentKeyStates[SDL_SCANCODE_A] && currentKeyStates[SDL_SCANCODE_D])
		moveRight();

	//teleports
	if (currentKeyStates[SDL_SCANCODE_UP])
		teleport(Player::UP, myVector);
	if (currentKeyStates[SDL_SCANCODE_DOWN])
		teleport(Player::DOWN, myVector);
	if (currentKeyStates[SDL_SCANCODE_LEFT])
		teleport(Player::LEFT, myVector);
	if (currentKeyStates[SDL_SCANCODE_RIGHT])
		teleport(Player::RIGHT, myVector);
}
