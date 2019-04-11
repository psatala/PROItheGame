#include <SDL.h>
#undef main

#include <iostream>

#include "Player.h"

using namespace std;

int main()
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
		cout << "SDL could not load" << endl;
	else
		cout << "SDL works" << endl;
	return 0;
}

