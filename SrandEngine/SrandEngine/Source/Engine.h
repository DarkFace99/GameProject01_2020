#pragma once

// Include GLFW
#include <GLFW/glfw3.h>

/* Initialize Window */
#define SCREEN_WIDTH    1280
#define SCREEN_HEIGTH  720

class Engine {
private:
	GLFWwindow* window;
	bool isRunning;
	static Engine* s_instance;

public:
	void Quit();
	void Init();
	void Clean();

	void Draw();
	void Update();
	void FixedUpdate();

	inline static Engine& get() {
		if (s_instance == nullptr) {
			s_instance = new Engine();
		}
		return *s_instance;
	}
};