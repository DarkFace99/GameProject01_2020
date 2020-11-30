#pragma once

/* C/C++ Headers */
#include <iostream>

/* Custom Headers */
#include "Engine.h"
#include "Camera.h"
#include "Animator.h"
#include "SpriteRenderer.h"

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
        
        int currentInputMode;
        Camera* camera = nullptr;
        GameObject* player = nullptr;

        void keyUpdate(GLFWwindow* window)
        {
            player->GetComponent<Animator>().PlayState("BENNY_IDLE");

            if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS && glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS) 
            {
                SetInputMode(DEBUG);
            }
            if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS && glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS)
            {
                SetInputMode(GAME);
            }

            switch (GetInputMode())
            {
            case DEBUG:
                if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
                {
                    //std::cout << "W" << std::endl;
                    camera->MoveCamera(glm::vec3(0.0f, 1.5f, 0.0f));
                }
                if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
                {
                    //std::cout << "A" << std::endl;
                    camera->MoveCamera(glm::vec3(-1.5f, 0.0f, 0.0f));
                }
                if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
                {
                    //std::cout << "S" << std::endl;
                    camera->MoveCamera(glm::vec3(0.0f, -1.5f, 0.0f));
                }
                if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
                {
                    //std::cout << "D" << std::endl;
                    camera->MoveCamera(glm::vec3(1.5f, 0.0f, 0.0f));
                }
                if (glfwGetKey(window, GLFW_KEY_I) == GLFW_PRESS)
                {
                    //std::cout << "I" << std::endl;
                    camera->CamZoomIn(0.05f);
                }
                if (glfwGetKey(window, GLFW_KEY_O) == GLFW_PRESS)
                {
                    //std::cout << "O" << std::endl;
                    camera->CamZoomOut(0.05f);
                }
                break;
            case GAME:
                if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
                {
                    //std::cout << "W" << std::endl;
                    player->GetComponent<Transform>().Translate(Vector2D_float(0.0f, 2.0f));
                    player->GetComponent<Animator>().PlayState("BENNY_JUMP");
                }
                if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
                {
                    //std::cout << "A" << std::endl;
                    player->GetComponent<Transform>().Translate(Vector2D_float(-.10f, 0.0f));
                    player->GetComponent<Animator>().PlayState("BENNY_RUN");
                    player->GetComponent<SpriteRenderer>().SetFlip(true);
                }
                if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
                {
                    //std::cout << "S" << std::endl;
                    player->GetComponent<Transform>().Translate(Vector2D_float(0.0f, -2.0f));
                    player->GetComponent<Animator>().PlayState("BENNY_FALL");
                }
                if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
                {
                    //std::cout << "D" << std::endl;
                    player->GetComponent<Transform>().Translate(Vector2D_float(.10f, 0.0f));
                    player->GetComponent<Animator>().PlayState("BENNY_RUN");
                    player->GetComponent<SpriteRenderer>().SetFlip(false);
                }
                break;
            default:
                break;
            }
        }


    public: 
        Input(Camera* camera) 
        {
            SetInputMode(GAME);
            Input::camera = camera;
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
        void SetControl(GameObject* gameObj) 
        {
            this->player = gameObj;
        }
        int GetInputMode() 
        {
            return currentInputMode;
        }
	};
}
