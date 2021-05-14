#include "WindowProperties.h"

namespace Srand
{
	WindowProperties* WindowProperties::s_instance = nullptr;

	void WindowProperties::SetFullScreen(bool isFullScreen)
	{
		if (GetFullScreenStatus() == isFullScreen)
			return;

		this->enableFullScreen = isFullScreen;

		if (isFullScreen) 
		{
			glfwGetWindowPos(window, &wndPos[0], &wndPos[1]);
			glfwGetWindowSize(window, &wndSize[0], &wndSize[1]);

			const GLFWvidmode* mode = glfwGetVideoMode(monitor);
			glfwSetWindowMonitor(window, monitor, 0, 0, mode->width, mode->height, 0);

			SR_TRACE("Fullscreen");
			SR_TRACE("w: {0}	h:{1}", wndPos[0], wndPos[1]);
			SR_TRACE("sw: {0}	sh:{1}", wndSize[0], wndSize[1]);
		}
		else 
		{
			glfwSetWindowMonitor(window, nullptr, wndPos[0], wndPos[1], wndSize[0], wndSize[1], 0);
			SR_TRACE("Windowed");
			SR_TRACE("w: {0}	h:{1}", wndPos[0], wndPos[1]);
			SR_TRACE("sw: {0}	sh:{1}", wndSize[0], wndSize[1]);
		}
	}
}
