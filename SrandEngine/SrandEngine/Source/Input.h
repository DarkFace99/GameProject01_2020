#pragma once

/* C/C++ Headers */
#include <iostream>
#include <map>

/* Custom Headers */
#include "Engine.h"
#include "Camera.h"
#include "Animator.h"
#include "SpriteRenderer.h"
//cheat
#include "NPC.h"

namespace IOSystem 
{
	enum InputMode 
	{
		DEBUG,
		GAME
	};

    void key_callBack(GLFWwindow* window, int key, int scancode, int action, int mods)
    {

    }

	class Input
	{
    private:
        int currentInputMode = GAME;
        std::string currentPlayer = "";
        Camera* camera = nullptr;
        GameObject* player = nullptr;

        std::map<std::string, GameObject*> characterList;

        void keyUpdate(GLFWwindow* window)
        {
            bool C_DOWN = false;

            
            if (player->GetComponent<RigidBody>().GetVelocityY() > 0) 
            {
                player->GetComponent<Animator>().PlayState("BENNY_JUMP");
            }
            else if(player->GetComponent<RigidBody>().GetVelocityY() < 0)
            {
                player->GetComponent<Animator>().PlayState("BENNY_FALL");
            }
            else
            {
                player->GetComponent<Animator>().PlayState("BENNY_IDLE");
            }

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
                //std::cout << player->GetComponent<RigidBody>().GetVelocityX() << std::endl;
                //std::cout << player->GetComponent<BoxCollider2D>().GetIsGround() << std::endl;
                if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS && player->GetComponent<BoxCollider2D>().GetIsGround() && currentPlayer != "Macho")
                {
                    //std::cout << "W" << std::endl;
                    player->GetComponent<RigidBody>().SetVelocityY(8.0f);
                }
                if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
                {
                    //std::cout << "A" << std::endl;
                    player->GetComponent<Transform>().Translate(Vector2D_float(-2.5f, 0.0f));
                    if (player->GetComponent<BoxCollider2D>().GetIsGround()) {
                        player->GetComponent<Animator>().PlayState("BENNY_RUN");
                    }
                    player->GetComponent<SpriteRenderer>().SetFlip(true);
                }
                if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
                {
                    //std::cout << "D" << std::endl;
                    player->GetComponent<Transform>().Translate(Vector2D_float(2.5f, 0.0f));
                    if (player->GetComponent<BoxCollider2D>().GetIsGround()) {
                        player->GetComponent<Animator>().PlayState("BENNY_RUN");
                    }
                    player->GetComponent<SpriteRenderer>().SetFlip(false);
                }
                if ((glfwGetKey(window, GLFW_KEY_C) == GLFW_PRESS) && (!C_DOWN)) 
                {
                    C_DOWN = true;
                }
                if ((glfwGetKey(window, GLFW_KEY_C) == GLFW_RELEASE) && (C_DOWN)) 
                {
                    C_DOWN = false;
                    if (currentPlayer == "Benny")
                    {
                        SetControl("Macho");
                        Engine::get().player = characterList.at("Macho");
                    }
                    else if (currentPlayer == "Macho")
                    {
                        SetControl("Benny");
                        Engine::get().player = characterList.at("Benny");
                    }
                }

                // Shortcut keys

                if ((glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS)) // reset character pos
                {
                    SetControl("Macho");
                    Engine::get().player = characterList.at("Macho");
                    player->GetComponent<Transform>().SetPosition(Vector2D_float(60.0f, -285.0f));

                    SetControl("Benny");
                    Engine::get().player = characterList.at("Benny");
                    player->GetComponent<Transform>().SetPosition(Vector2D_float(-555.0f, -200.0f)); 

                    Engine::get().npc->GetComponent<NPC>().SetCollideFalse();
                }

                if ((glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS)) // skip macho's throw
                {
                    SetControl("Macho");
                    Engine::get().player = characterList.at("Macho");
                    player->GetComponent<Transform>().SetPosition(Vector2D_float(-82.0f, -114.0f));

                    SetControl("Benny");
                    Engine::get().player = characterList.at("Benny");
                    player->GetComponent<Transform>().SetPosition(Vector2D_float(302.0f, -114.0f));

                    Engine::get().npc->GetComponent<NPC>().SetCollideFalse();
                }

                if ((glfwGetKey(window, GLFW_KEY_3) == GLFW_PRESS)) // Benny third floor
                {
                    SetControl("Macho");
                    Engine::get().player = characterList.at("Macho");
                    player->GetComponent<Transform>().SetPosition(Vector2D_float(-77.0f, -114.0f));

                    SetControl("Benny");
                    Engine::get().player = characterList.at("Benny");
                    player->GetComponent<Transform>().SetPosition(Vector2D_float(282.0f, 88.0f));

                    Engine::get().npc->GetComponent<NPC>().SetCollideFalse();
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
        void SetControl(std::string name) 
        {
            this->player = characterList.at(name);
            currentPlayer = name;
            std::cout << "Current Control: " << name << std::endl;
        }
        void AddCharacterList(std::string name, GameObject* _gameObj) 
        {
            characterList.insert(std::pair<std::string, GameObject*>(name, _gameObj));
        }

        int GetInputMode() 
        {
            return currentInputMode;
        }
	};

}

