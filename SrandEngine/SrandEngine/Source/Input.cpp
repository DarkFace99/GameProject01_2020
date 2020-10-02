#include "Input.h"

void SystemPollEvent(GLFWwindow* window)
{
	glfwPollEvents();

	if(glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS && glfwGetKey(window, GLFW_KEY_G) == GLFW_PRESS)
	{
		HandleKeys('g');
	}
	else if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS && glfwGetKey(window, GLFW_KEY_C) == GLFW_PRESS)
	{
		HandleKeys('c');
	}
	else if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS && glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{
		HandleKeys('s');
	}
}

void HandleKeys(char key)
{
	switch (key)
	{
	case 'g':
		std::cout << "Ctrl + G" << std::endl;
		break;
	case 'c':
		std::cout << "Ctrl + C" << std::endl;
		break;
	case 's':
		std::cout << "Ctrl + S" << std::endl;
		break;
	default:
		break;
	}
}