#pragma once

// Include GLFW
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <srpch.h>

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
	class WindowProperties
	{
	private:
		static WindowProperties* s_instance;
		GLFWwindow* window;

		//Initial Properties
		int screen_width = 1280;
		int screen_height = 720;
		bool enableFullScreen = false;
		bool enableVsync = true;

		WindowProperties()
		{
			/* Create a windowed mode window and its OpenGL context */
			SR_SYSTEM_INFO("Initializing Window...");
			window = glfwCreateWindow(GetWidth(), GetHeight(), WINDOW_NAME, (GetFullScreenStatus()) ? glfwGetPrimaryMonitor() : NULL, NULL);
			if (!window)
			{
				glfwTerminate();
				SR_SYSTEM_ERROR("Error! Cannot create window");
			}

			/* Make the window's context current */
			glfwMakeContextCurrent(window);

			/*Vsync on = 1, off = 0*/
			glfwSwapInterval(GetVsyncStatus());
		}

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
			return window;
		}

		inline void SetScreenSize(int width, int height) { screen_width = width; screen_height = height; }
		inline void SetFullScreen(bool isFullScreen) { this->enableFullScreen = isFullScreen; }
		inline void SetVsync(bool enableVsync) { this->enableVsync = enableVsync; }

		inline int GetWidth() const { return screen_width; }
		inline int GetHeight() const { return screen_height; }
		inline bool GetFullScreenStatus() const { return enableFullScreen; }
		inline bool GetVsyncStatus() const { return enableVsync; }

	};

	class UserInterface
	{
	private:
		ImGuiIO io;
		bool vSync = true;
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

			ImGui::Begin("Debug Console");

			ImGui::Text("Time: %.3f sec", glfwGetTime());
			ImGui::Text("FPS: %.3f", ImGui::GetIO().Framerate);
			ImGui::Checkbox("Enable Vsync", &vSync);
			ImGui::Checkbox("Show Demo Window", &show_demo_window);
			WindowProperties::get().SetVsync(vSync);

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
	};


	void window_size_callback(GLFWwindow* window, int width, int height);
	void window_close_callback(GLFWwindow* window);

}