#pragma once

#include <SDL.h>
#include <iostream>

#include "Player.h"


bool init(SDL_Window** window, SDL_Renderer** renderer, const int SCREEN_HEIGHT, const int SCREEN_WIDTH);


void play(SDL_Window* window, SDL_Renderer* renderer, const int SCREEN_HEIGHT, const int SCREEN_WIDTH, const int PLAYER_HEIGHT, const int PLAYER_WIDTH, const double TIME_BETWEEN_FRAMES);

void applyInput(Player* myPlayer, const Uint8* currentKeyStates, const int teleportDistance, const unsigned int timeBetweenTeleports);

void clear(SDL_Renderer* rendererToPrintOn);

void close();