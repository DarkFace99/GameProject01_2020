#pragma once

#include <iostream>

/* OpenGL */
#include <GLFW/glfw3.h>


static unsigned int CompileShader(unsigned int type, const std::string& source);
static unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader);
void InitializeShader();
void DeleteShader();
