#pragma once

#include <iostream>

/* OpenGL */
#include <GL/glew.h>
#include <GLFW/glfw3.h>

class Shader {
public:
	Shader() = default;
	static unsigned int shader;
	static Shader* s_instance;

	static unsigned int CompileShader(unsigned int type, const std::string& source);
	static unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader);
	static void InitializeShader();
	static void DeleteShader();

	static Shader* get() {
		if (s_instance == nullptr) {
			s_instance = new Shader();
		}
		return s_instance;
	}
	
};


