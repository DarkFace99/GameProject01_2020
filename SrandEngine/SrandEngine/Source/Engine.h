#pragma once

// Include GLFW
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>

/* Custom Header */
#include "AssetManager.h"
#include "Shader.h"
#include "EntityManager.h"
#include "TimeStep.h"

#ifndef IMGUI

/* ImGui */
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#endif // !IMGUI

/* Initialize Window */
#define SCREEN_WIDTH    1280
#define SCREEN_HEIGTH   720
#define WINDOW_NAME		"BENNY: Everyone is Happy"
#define FULLSCREEN		false

class WindowProperties 
{
private:
	static WindowProperties* s_instance;

	//Initial Properties
	int screen_width = 1280;
	int screen_height = 720;
	bool isFullScreen = false;

	WindowProperties() {}

public:
	inline static WindowProperties& get() 
	{
		if (s_instance == nullptr) 
		{
			s_instance = new WindowProperties();
		}
		return *s_instance;
	}

	operator GLFWwindow* () const 
	{
		return glfwCreateWindow(GetWidth(), GetHeight(), WINDOW_NAME, (GetIsFullScreen()) ? glfwGetPrimaryMonitor() : NULL, NULL);
	}

	inline void SetScreenSize(int width, int height) { screen_width = width; screen_height = height; }
	inline void SetFullScreen(bool isFullScreen) { this->isFullScreen = isFullScreen; }

	inline int GetWidth() const { return screen_width; }
	inline int GetHeight() const { return screen_height; }
	inline bool GetIsFullScreen() const { return isFullScreen; }

};

namespace UI
{
	class UserInterface
	{
	private:
		float m_Time = 0.0f;
		ImGuiIO io;

	public:
		inline void InitUserInterface()
		{
			IMGUI_CHECKVERSION();

			ImGui::CreateContext();
			ImGui::StyleColorsDark();

			io = ImGui::GetIO();
			/*io.BackendFlags |= ImGuiBackendFlags_HasMouseCursors;
			io.BackendFlags |= ImGuiBackendFlags_HasSetMousePos;*/

			ImGui_ImplGlfw_InitForOpenGL(WindowProperties::get(), true);
			ImGui_ImplOpenGL3_Init("#version 330 core");
		}

		inline void UpdateUserInterface()
		{
			// Feed IMGUI the inputs, start new frame
			ImGui_ImplOpenGL3_NewFrame();
			ImGui_ImplGlfw_NewFrame();
			ImGui::NewFrame();

			io = ImGui::GetIO();

			static bool show = true;
			ImGui::ShowDemoWindow(&show);

			// Render IMGUI to screen
			ImGui::Render();
			ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
		}

		inline void TerminateUserInterface() 
		{
			ImGui_ImplOpenGL3_Shutdown();
			ImGui_ImplGlfw_Shutdown();
			ImGui::DestroyContext();
		}

	};
}

class Engine {
private:
	GLFWwindow* window;
	int width, height;

	static Engine* s_instance;
	bool running;

	EntityManager* manager = nullptr;
	
public:
	Engine();
	virtual ~Engine() = default;

	std::vector<GameObject*> objManager;
	GameObject* player;
	// cheat
	GameObject* npc;

	void Init();
	void Clean();
	void Quit();

	void Draw();
	void Update();
	void FixedUpdate(TimeStep ts);
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