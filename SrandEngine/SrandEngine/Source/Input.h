#pragma once

#include <SDL.h>

#include<iostream>

//extern SDL_Event sdlEvent;

enum INPUT_MODE
{
	GAME_MODE = 0,
	CAMERA_MODE,
	TESTING_MODE
};

void HandleKeys(char key) 
{
	switch (key)
	{
		case 'a':
			std::cout << "a" << std::endl;
			break;
		default:
			break;
	}
}