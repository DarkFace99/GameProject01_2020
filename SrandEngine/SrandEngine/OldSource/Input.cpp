#include "Input.h"

void SystemPollEvent(GLFWwindow* window, int& inputMode)
{
	glfwPollEvents();

	if(glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS && glfwGetKey(window, GLFW_KEY_G) == GLFW_PRESS)
	{
		inputMode = GAME_MODE;
	}
	else if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS && glfwGetKey(window, GLFW_KEY_C) == GLFW_PRESS)
	{
		inputMode = CAMERA_MODE;
	}
	else if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS && glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{
		inputMode = TESTING_MODE;
	}

	if (inputMode == GAME_MODE) 
	{
		if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) 
		{
			HandleKeys("Game_a");
		}
	}
	else if (inputMode == CAMERA_MODE)
	{
		if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		{
			HandleKeys("Camera_w");
		}
		else if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		{
			HandleKeys("Camera_a");
		}
		else if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		{
			HandleKeys("Camera_s");
		}
		else if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		{
			HandleKeys("Camera_d");
		}
		else if (glfwGetKey(window, GLFW_KEY_I) == GLFW_PRESS)
		{
			HandleKeys("Camera_i");
		}
		else if (glfwGetKey(window, GLFW_KEY_O) == GLFW_PRESS)
		{
			HandleKeys("Camera_o");
		}
	}
	else if (inputMode == TESTING_MODE)
	{
		if (glfwGetKey(window, GLFW_KEY_TAB) == GLFW_PRESS) 
		{
			HandleKeys("Tab");
		}
	}
}

void HandleKeys(std::string key)
{
	if (key == "Game_a")
	{
		std::cout << key << std::endl;
	}
	else if (key == "Camera_w")
	{
		std::cout << key << std::endl;
	}
	else if (key == "Camera_a")
	{
		std::cout << key << std::endl;
	}
	else if (key == "Camera_s")
	{
		std::cout << key << std::endl;
	}
	else if (key == "Camera_d")
	{
		std::cout << key << std::endl;
	}
	else if (key == "Camera_i")
	{
		std::cout << key << std::endl;
	}
	else if (key == "Camera_o")
	{
		std::cout << key << std::endl;
	}
	else if (key == "Tab")
	{
		std::cout << key << std::endl;
	}
}