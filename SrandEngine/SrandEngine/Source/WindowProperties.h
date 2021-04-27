#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <srpch.h>

namespace Srand
{
	class WindowProperties
	{
	private:
		static WindowProperties* s_instance;
		GLFWwindow* window;
		GLFWmonitor* monitor;

		//Initial Properties
		int screen_width = 1280;
		int screen_height = 720;
		const char* window_name = "BENNY: Everyone is Happy";
		bool enableFullScreen = false;
		bool enableVsync = true;

		int wndPos[2];
		int wndSize[2];

		WindowProperties()
		{
			/* Create a windowed mode window and its OpenGL context */
			SR_SYSTEM_INFO("Initializing Window...");
			monitor = glfwGetPrimaryMonitor();
			window = glfwCreateWindow(GetWidth(), GetHeight(), window_name, (GetFullScreenStatus()) ? monitor : NULL, NULL);
			if (!window)
			{
				glfwTerminate();
				SR_SYSTEM_ERROR("Error! Cannot create window");
			}

			glfwSetWindowPos(window, 400, 540);

			/* Make the window's context current */
			glfwMakeContextCurrent(window);

			/*Vsync on = 1, off = 0*/
			glfwSwapInterval(enableVsync);
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

		void Update();

		inline void SetScreenSize(int width, int height) { screen_width = width; screen_height = height; }
		inline void SetFullScreen(bool isFullScreen) { this->enableFullScreen = isFullScreen; }
		inline void SetVsync(bool enableVsync) { this->enableVsync = enableVsync; }

		inline int GetWidth() const { return screen_width; }
		inline int GetHeight() const { return screen_height; }
		inline bool GetFullScreenStatus() const { return enableFullScreen; }
		inline bool GetVsyncStatus() const { return enableVsync; }

	};
}
