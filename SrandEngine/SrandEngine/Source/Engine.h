#pragma once

// Include GLFW
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>

/* Custom Header */
#include "AssetManager.h"
#include "Shader.h"

/* Initialize Window */
#define SCREEN_WIDTH    1280
#define SCREEN_HEIGTH   720
#define WINDOW_NAME		"BENNY: Everyone is Happy"
#define FULLSCREEN		false

class Engine {
private:
	GLFWwindow* window;
	static Engine* s_instance;
	bool running;
	
public:
	Engine();
	virtual ~Engine() = default;

	void Init();
	void Clean();
	void Quit();

	void Draw();
	void Update();
	void FixedUpdate();
	void Event();

	inline static Engine& get() {
		if (s_instance == nullptr) {
			s_instance = new Engine();
		}
		return *s_instance;
	}

	inline bool IsRunning() {
		return running;
	}
};

void key_callBack(GLFWwindow* window, int key, int scancode, int action, int mods);
void keyUpdate(GLFWwindow* window);