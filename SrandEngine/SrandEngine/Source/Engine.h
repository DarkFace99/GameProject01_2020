#pragma once

// Include GLFW
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "WindowProperties.h"

/* Custom Header */
#include "AssetManager.h"
#include "Shader.h"
#include "EntityManager.h"
#include "TimeStep.h"

#include "Source/KeyCode.h"
#include "Source/MouseButtonCode.h"

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

namespace Srand
{
	class UserInterface
	{
	private:
		ImGuiIO io;
		bool vSync = false;
		bool show_demo_window = false;

	public:
		inline void InitUserInterface()
		{
			IMGUI_CHECKVERSION();

			ImGui::CreateContext();
			ImGui::StyleColorsDark();

			io = ImGui::GetIO();

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

			if (show_demo_window)
			{
				ImGui::ShowDemoWindow(&show_demo_window);
			}
			if (vSync) 
			{
				WindowProperties::get().SetVsync(true);
			}
			else 
			{
				WindowProperties::get().SetVsync(false);
			}

			ImGui::Begin("Debug Console");

			ImGui::Text("Time: %.3f sec", glfwGetTime());
			ImGui::Text("FPS: %.3f", ImGui::GetIO().Framerate);
			ImGui::Checkbox("Enable Vsync", &vSync);
			ImGui::Checkbox("Show Demo Window", &show_demo_window);

			ImGui::End();

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

	class Engine {
	private:
		static Engine* s_instance;
		bool running;

		TimeStep* timeStep = nullptr;

	public:
		Engine();
		virtual ~Engine() = default;
		
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

		void NextScene();
		void GoToScene(int);
	
	protected:
		int nextScene_Num = 0; // Engine.cpp line.138

		void LoadSave(bool& fullscreen, float& volM, float& volE, int& proc);
		void WriteSave();
	};


	void window_size_callback(GLFWwindow* window, int width, int height);
	void window_close_callback(GLFWwindow* window);
	void window_key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
}