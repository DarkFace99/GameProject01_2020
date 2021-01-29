#include "Engine.h"

/* TEST */
#include "ecspch.h"

#include "Source/MouseEvent.h"
#include "Source/KeyEvent.h"

#include "Source/WindowsInput.h"
#include "Entity/NPC.h"
#include "Entity/Button.h"
#include "Entity/Door.h"
#include "Entity/Elevator.h"

#define DEBUG 1
#define MULTITHREAD 0
#define RATIO SCREEN_WIDTH / 480.0f

namespace Srand
{
#define BIND_EVENT_FUNCTION(x) std::bind(&Engine::x, this, std::placeholders::_1)

    // System-wide Initialization
    UserInterface user_interface;
    WindowsInput windowsInput;

    Engine* Engine::s_instance = nullptr;
    WindowProperties* WindowProperties::s_instance = nullptr;

    Engine::Engine() {
        running = false;
    }

    void Engine::Init() {

#pragma region InitializeEngine

        /* Initialize the library */
        std::cout << "Initializing GLFW..." << std::endl;
        if (!glfwInit())
        {
            std::cout << "Error! Cannot initializing GLFW" << std::endl;
        }

        WindowProperties::get();

        /*Initializing GLEW*/
        std::cout << "Initializing GLEW..." << std::endl;
        if (glewInit() != GLEW_OK)
        {
            std::cout << "Error! Cannot initializing GLEW" << std::endl;
        }

        std::cout << "Initializing UserInterface..." << std::endl;
        user_interface.InitUserInterface();

        glfwSetInputMode(WindowProperties::get(), GLFW_STICKY_KEYS, GL_TRUE);
        std::cout << "--------------------------------------------------------------------------------" << std::endl;
        std::cout << "                            |--System Initialized--|                            " << std::endl;
        std::cout << "--------------------------------------------------------------------------------" << std::endl;
        std::cout << "                          Version: " << glGetString(GL_VERSION) << std::endl;
        std::cout << "--------------------------------------------------------------------------------" << std::endl;

        glfwSetWindowSizeCallback(WindowProperties::get(), [](GLFWwindow* window, int width, int height)
        {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
            data.Width = width;
            data.Height = height;

            WindowResizeEvent event(width, height);
            data.EventCallback(event);
        });
        glfwSetWindowCloseCallback(WindowProperties::get(), [](GLFWwindow* window)
        {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

            WindowCloseEvent event;
            data.EventCallback(event);
        });
        glfwSetKeyCallback(WindowProperties::get(), [](GLFWwindow* window, int key, int scancode, int action, int mods)
        {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

            switch (action)
            {
            case GLFW_PRESS:
            {
                KeyPressedEvent event(key, 0);
                data.EventCallback(event);
                break;
            }
            case GLFW_RELEASE:
            {
                KeyReleasedEvent event(key);
                data.EventCallback(event);
                break;
            }
            case GLFW_REPEAT:
            {
                KeyPressedEvent event(key, 1);
                data.EventCallback(event);
                break;
            }
            }
        });
        glfwSetCharCallback(WindowProperties::get(), [](GLFWwindow* window, unsigned int keycode)
        {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

            KeyTypedEvent event(keycode);
            data.EventCallback(event);
        });
        glfwSetMouseButtonCallback(WindowProperties::get(), [](GLFWwindow* window, int button, int action, int mods)
        {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

            switch (action)
            {
            case GLFW_PRESS:
            {
                MouseButtonPressedEvent event(button);
                data.EventCallback(event);
                break;
            }
            case GLFW_RELEASE:
            {
                MouseButtonReleasedEvent event(button);
                data.EventCallback(event);
                break;
            }
            }
        });
        glfwSetScrollCallback(WindowProperties::get(), [](GLFWwindow* window, double offsetX, double offsetY)
        {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

            MouseScrolledEvent event((float)offsetX, (float)offsetY);
            data.EventCallback(event);
        });
        glfwSetCursorPosCallback(WindowProperties::get(), [](GLFWwindow* window, double xPos, double yPos)
        {
            WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

            MouseMovedEvent event((float)xPos, (float)yPos);
            data.EventCallback(event);
        });

#pragma endregion

        timeStep = &TimeStep::get();

        /* Initialize Shader */
        Shader::get()->InitializeShader();

        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glDisable(GL_CULL_FACE);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        // former asset loading pattern
        {
            //AssetManager::get().LoadMesh("BG_MESH");
            //AssetManager::get().LoadTexture("BG_TEX", "Assets/Background.png");

            //AssetManager::get().LoadMesh("TILESET_MESH", 8, 8);
            //AssetManager::get().LoadTexture("TILESET_TEX", "Assets/TILESET.png");

            //AssetManager::get().LoadMesh("BENNY_ANIM_MESH", 21);
            //AssetManager::get().LoadTexture("BENNY_ANIM_TEX", "Assets/Benny_Animations-Sheet.png");

            //AssetManager::get().LoadMesh("MACHO_ANIM_MESH", 20);
            //AssetManager::get().LoadTexture("MACHO_ANIM_TEX", "Assets/Macho_Animation-Sheet.png");

            //AssetManager::get().LoadMesh("NPC_ANIM_MESH", 2);
            //AssetManager::get().LoadTexture("NPC_ANIM_TEX", "Assets/NPC_Animation_Sheet.png");

            //// obstacle asset
            //AssetManager::get().LoadTexture("LEVEL_ASSET_TEX", "Assets/Level_Assets_00.png");

            //AssetManager::get().LoadMesh("DOOR_STAND_MESH", 10, 13);
            //AssetManager::get().LoadMesh("DOOR_MESH", 10, 13, 1, 4);
            //AssetManager::get().LoadMesh("ELEVATOR_MESH", 10, 13, 2, 2);
            //AssetManager::get().LoadMesh("ELEVATOR_STAND_MESH", 10, 13, 2, 1);
            //AssetManager::get().LoadMesh("BUTTON_MESH", 10, 13, 2, 1);
        }

#pragma region AssetsLoading

        double init_Time = (double)glfwGetTime();
        /* Mesh */
        AssetManager::get().LoadMesh("BG_MESH");
        AssetManager::get().LoadMesh("TILESET_MESH", 8, 8);
        AssetManager::get().LoadMesh("BENNY_ANIM_MESH", 21);
        AssetManager::get().LoadMesh("MACHO_ANIM_MESH", 20);
        AssetManager::get().LoadMesh("NPC_ANIM_MESH", 2);
        AssetManager::get().LoadMesh("DOOR_STAND_MESH", 10, 13);
        AssetManager::get().LoadMesh("DOOR_MESH", 10, 13, 1, 4);
        AssetManager::get().LoadMesh("ELEVATOR_MESH", 10, 13, 2, 2);
        AssetManager::get().LoadMesh("ELEVATOR_STAND_MESH", 10, 13, 2, 1);
        AssetManager::get().LoadMesh("BUTTON_MESH", 10, 13, 2, 1);

        /* Texture */
        AssetManager::get().LoadTexture("BG_TEX", "Assets/Background.png");
        AssetManager::get().LoadTexture("TILESET_TEX", "Assets/TILESET.png");
        AssetManager::get().LoadTexture("BENNY_ANIM_TEX", "Assets/Benny_Animations-Sheet.png");
        AssetManager::get().LoadTexture("MACHO_ANIM_TEX", "Assets/Macho_Animation-Sheet.png");
        AssetManager::get().LoadTexture("NPC_ANIM_TEX", "Assets/NPC_Animation_Sheet.png");
        AssetManager::get().LoadTexture("LEVEL_ASSET_TEX", "Assets/Level_Assets_00.png");

        double time_Interval = (double)glfwGetTime() - init_Time;
        std::cout << std::endl << "Time used: " << time_Interval << std::endl << std::endl;

#pragma endregion

        SceneManager::get().Init();

        running = true;
    }

    void Engine::Draw() {   
        user_interface.UpdateUserInterface();
        SceneManager::get().Draw();
        glfwSwapBuffers(WindowProperties::get());
    }

    void Engine::Update() {
        glClearColor(0.3f, 0.3f, 0.5f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glfwPollEvents();

        double init_Time = (double)glfwGetTime();

#if MULTITHREAD
        std::thread updateTime([&]()
        {
            timeStep->Update();
        });
        updateTime.join();
#else
        timeStep->Update();
#endif

        double time_Interval = (double)glfwGetTime() - init_Time;
        user_interface.SetTimeInterval(time_Interval);

        SceneManager::get().Update();

        glfwSetWindowSizeCallback(WindowProperties::get(), window_size_callback);
    }

    void Engine::FixedUpdate(TimeStep ts) 
    {

    }

    void Engine::OnEvent(Event& e) {
        EventDispatcher dispatcher(e);
        dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FUNCTION(Quit));
        
        //if (windowsInput.IsKeyPressed(SR_KEY_ESCAPE)) { Quit(); }
    }

    void Engine::Clean() {
        AssetManager::get().Clean();
        Shader::get()->DeleteShader();

        user_interface.WriteDataInterval("MTTimeInterval.txt");
        SceneManager::get().Clean();

        std::cout << "Closing window..." << std::endl << "System Shutdown" << std::endl;
        user_interface.TerminateUserInterface();
        glfwTerminate();
    }

    void Engine::Quit() {
        running = false;
    }

    /*bool Engine::OnWindowClose(WindowCloseEvent& e) 
    {
        running = false;
        return true;
    }*/

    void window_size_callback(GLFWwindow* window, int width, int height)
    {
        glfwGetWindowSize(window, &width, &height);
        WindowProperties::get().SetScreenSize(width, height);
    }
}