#include "WindowProperties.h"

namespace Srand
{
	WindowProperties* WindowProperties::s_instance = nullptr;

	void WindowProperties::Update()
	{
		glfwGetWindowPos(window, &wndPos[0], &wndPos[1]);
		glfwGetWindowSize(window, &wndSize[0], &wndSize[1]);

		const GLFWvidmode* mode = glfwGetVideoMode(monitor);
		if (enableFullScreen) 
		{
			glfwSetWindowMonitor(window, monitor, 0, 0, mode->width, mode->height, GLFW_DONT_CARE);
		}
		else 
		{
			glfwSetWindowMonitor(window, nullptr, wndPos[0], wndPos[1], wndSize[0], wndSize[1], GLFW_DONT_CARE);
		}
	}
}
