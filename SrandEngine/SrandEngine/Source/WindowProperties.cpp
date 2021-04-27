#include "WindowProperties.h"

namespace Srand
{
	WindowProperties* WindowProperties::s_instance = nullptr;

	void WindowProperties::Update()
	{
		const GLFWvidmode* mode = glfwGetVideoMode(monitor);
		if (enableFullScreen) 
		{
			glfwSetWindowMonitor(window, monitor, 0, 0, mode->width, mode->height, GLFW_DONT_CARE);
		}
		else 
		{
			glfwSetWindowMonitor(window, nullptr, 0, 0, screen_width, screen_height, GLFW_DONT_CARE);
		}
	}
}
