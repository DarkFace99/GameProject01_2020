#pragma once

/* Open GL */
#include <GL/glew.h>
#include <GLFW/glfw3.h>

/* Initialize Window */
extern GLFWwindow* window;

/* Standard C/C++ */
#include <iostream>
#include <string>

#include "Shader.h"

/* System Check*/
int SystemInit(int width, int height, const std::string name);
void SystemShutdown();

/* Framerate Check*/
void FrameInit();
double FrameStart();
void FrameEnd();
