#pragma once

#include <GLFW/glfw3.h>

#include<iostream>

extern GLFWwindow* window;

enum INPUT_MODE
{
	GAME_MODE = 0,
	CAMERA_MODE,
	TESTING_MODE
};

/*Use this in Game Update Function*/
void SystemPollEvent(GLFWwindow* window, int& inputMode);
void HandleKeys(std::string key);