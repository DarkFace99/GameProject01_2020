#pragma once

/* C/C++ Headers */
#include <iostream>

/* Custom Headers */
#include "Engine.h"
#include "Camera.h"

namespace IOSystem 
{
	enum InputMode 
	{
		DEBUG,
		GAME
	};

	void key_callBack(GLFWwindow* window, int key, int scancode, int action, int mods)
	{
		if (key == GLFW_KEY_TAB && action == GLFW_PRESS)
		{
			std::cout << key << std::endl;
		}
	}

	class Input
	{
    private:
        void keyUpdate(GLFWwindow* window)
        {
            switch (GetInputMode())
            {
            case DEBUG:
                if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
                {
                    std::cout << "W" << std::endl;
                    //camera.MoveCamera(glm::vec3(0.0f, 1.5f, 0.0f));
                }
                if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
                {
                    std::cout << "A" << std::endl;
                    //camera.MoveCamera(glm::vec3(-1.5f, 0.0f, 0.0f));
                }
                if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
                {
                    std::cout << "S" << std::endl;
                    //camera.MoveCamera(glm::vec3(0.0f, -1.5f, 0.0f));
                }
                if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
                {
                    std::cout << "D" << std::endl;
                    //camera.MoveCamera(glm::vec3(1.5f, 0.0f, 0.0f));
                }
                if (glfwGetKey(window, GLFW_KEY_I) == GLFW_PRESS)
                {
                    std::cout << "I" << std::endl;
                    //camera.CamZoomIn(0.05f);
                }
                if (glfwGetKey(window, GLFW_KEY_O) == GLFW_PRESS)
                {
                    std::cout << "O" << std::endl;
                    //camera.CamZoomOut(0.05f);
                }
                break;
            case GAME:
                break;
            default:
                break;
            }
        }

        int currentInputMode;

    public: 
        Input() 
        {
            SetInputMode(GAME);
        }

		void IOUpdate(GLFWwindow* window) 
		{
			glfwPollEvents();
			glfwSetKeyCallback(window, key_callBack);
            this->keyUpdate(window);
		}
        void SetInputMode(int mode) 
        {
            this->currentInputMode = mode;
        }
        int GetInputMode() 
        {
            return currentInputMode;
        }
	};
}
