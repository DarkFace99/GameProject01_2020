#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <iostream>

// Include GLEW
#include <GL/glew.h>

// Include GLFW
#include <GLFW/glfw3.h>
extern GLFWwindow* window;

// Include GLM
#include <glm.hpp>

#include "Input.h"
#include "Renderable.h"
#include "GameObject.h"
#include "Camera.h"

// ---------------------------------------------------------------------------

void GameStateLevel1Load(void);
void GameStateLevel1Init(void);
void GameStateLevel1Update(double dt, long frame, int& state);
void GameStateLevel1Draw(void);
void GameStateLevel1Free(void);
void GameStateLevel1Unload(void);

// ---------------------------------------------------------------------------