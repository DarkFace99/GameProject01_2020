#include "Engine.h"

/* TEST */
#include "ecspch.h"

#include "Source/WindowsInput.h"
#include "Source/SceneManager.h"
#include "Game/Scenes/testing_scene.h"

namespace Srand
{
    // System-wide Initialization
    UserInterface user_interface;
    WindowsInput windowsInput;

    Engine* Engine::s_instance = nullptr;
    WindowProperties* WindowProperties::s_instance = nullptr;

    SceneManager& sceneManager = SceneManager::get();
    Scene* scene = nullptr;

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

#pragma endregion

        timeStep = &TimeStep::get();

        /* Initialize Shader */
        Shader::get()->InitializeShader();

        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glDisable(GL_CULL_FACE);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

#pragma region AssetsLoading

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

#pragma endregion

#pragma region SceneLoading

        scene = new TestingScene();
        sceneManager.PushScene(scene);

#pragma endregion

        //For Testing SceneManager Only
        sceneManager[0]->Init();
        
        running = true;
    }

    void Engine::Draw() {   
        //For Testing SceneManager Only
        sceneManager[0]->Draw();

        user_interface.UpdateUserInterface();

        glfwSwapBuffers(WindowProperties::get());
    }

    void Engine::Update() {
        glClearColor(0.3f, 0.3f, 0.5f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        timeStep->Update();

        //For Testing SceneManager Only
        sceneManager[0]->Update();

        glfwSetWindowSizeCallback(WindowProperties::get(), window_size_callback);
    }

    void Engine::FixedUpdate(TimeStep ts) 
    {
 
    }

    void Engine::Event() {
        // input
        glfwPollEvents();
        if (windowsInput.IsKeyPressed(SR_KEY_ESCAPE)) { Quit(); }
    }

    void Engine::Clean() {
        AssetManager::get().Clean();
        Shader::get()->DeleteShader();

        //user_interface.WriteDataInterval("MTTimeInterval.txt");

        //For Testing SceneManager Only
        sceneManager[0]->Clean();

        std::cout << "Closing window..." << std::endl << "System Shutdown" << std::endl;
        user_interface.TerminateUserInterface();
        glfwTerminate();
    }

    void Engine::Quit() {
        running = false;
    }

    void window_size_callback(GLFWwindow* window, int width, int height)
    {
        glfwGetWindowSize(window, &width, &height);
        WindowProperties::get().SetScreenSize(width, height);
    }
}