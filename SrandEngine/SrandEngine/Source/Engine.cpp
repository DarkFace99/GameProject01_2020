#include "Engine.h"

/* TEST */
#include "ecspch.h"

#include "Source/WindowsInput.h"
#include "Source/SceneManager.h"

#include "Game/Scenes/MainMenu.h"
#include "Game/Scenes/testing_scene.h"
#include "Game/Scenes/Level2.h"
#include "Game/Scenes/Level3.h"

#include "Source/Audio.h"

#define SFX_VOLUME 0.3f
#define BGM_VOLUME 0.2f

namespace Srand
{
    // System-wide Initialization
    //UserInterface user_interface;
    WindowsInput windowsInput;

    Engine* Engine::s_instance = nullptr;
    WindowProperties* WindowProperties::s_instance = nullptr;

    SceneManager& sceneManager = SceneManager::get();
    Scene* currentScene = nullptr;

    //GUI_Manager& guiManager = GUI_Manager::get();
    GUI_Array gui_arr;

    GameObject* tempgui = nullptr;

    Camera tempCam;

    AudioController& audioController = AudioController::get();

    GLFWimage icons[1];

    Engine::Engine() {
        running = false;
    }

    void Engine::Init() {

#pragma region InitializeEngine

        /* Initialize the library */
        SR_SYSTEM_INFO("Initializing GLFW...");
        if (!glfwInit())
        {
            SR_SYSTEM_ERROR("Error! Cannot initializing GLFW");
        }

        WindowProperties::get();

        /*Initializing GLEW*/
        SR_SYSTEM_INFO("Initializing GLEW...");
        if (glewInit() != GLEW_OK)
        {
            SR_SYSTEM_ERROR("Error! Cannot initializing GLEW");
        }

        SR_SYSTEM_INFO("Initializing UserInterface...");
        //user_interface.InitUserInterface();

        glfwSetInputMode(WindowProperties::get(), GLFW_STICKY_KEYS, GL_TRUE);
        std::cout << "--------------------------------------------------------------------------------" << std::endl;
        std::cout << "                            |--System Initialized--|                            " << std::endl;
        std::cout << "--------------------------------------------------------------------------------" << std::endl;
        std::cout << "                          Version: " << glGetString(GL_VERSION) << std::endl;
        std::cout << "--------------------------------------------------------------------------------" << std::endl;

        icons[0].pixels = SOIL_load_image("Assets/icon.png", &icons[0].width, &icons[0].height, 0, SOIL_LOAD_RGBA);
        glfwSetWindowIcon(WindowProperties::get(), 1, icons);
        SOIL_free_image_data(icons[0].pixels);

        glfwSetWindowPos(WindowProperties::get(), 100, 100);

#pragma endregion

        /* Initialize Shader */
        Shader::get()->InitializeShader();

        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glDisable(GL_CULL_FACE);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

#pragma region AssetsLoading

        /* Mesh */
        AssetManager::get().LoadMesh("BG_MESH");
        AssetManager::get().LoadMesh("B_MESH");
        AssetManager::get().LoadMesh("TILESET_MESH", 8, 8);
        AssetManager::get().LoadMesh("BENNY_ANIM_MESH", 21);
        AssetManager::get().LoadMesh("MACHO_ANIM_MESH", 20);
        AssetManager::get().LoadMesh("CHERRY_ANIM_MESH", 19);
        AssetManager::get().LoadMesh("PEAR_ANIM_MESH", 19);
        AssetManager::get().LoadMesh("BARTER_ANIM_MESH");
        AssetManager::get().LoadMesh("NPC_ANIM_MESH", 2);
        AssetManager::get().LoadMesh("DOOR_STAND_MESH", 10, 13);
        AssetManager::get().LoadMesh("DOOR_MESH", 10, 13, 1, 4);
        AssetManager::get().LoadMesh("ELEVATOR_MESH", 10, 13, 2, 2);
        AssetManager::get().LoadMesh("ELEVATOR_STAND_MESH", 10, 13, 2, 1);
        AssetManager::get().LoadMesh("BUTTON_MESH", 10, 13, 2, 1);

        /* Texture */
        AssetManager::get().LoadTexture("BG_TEX", "Background.png");
        AssetManager::get().LoadTexture("B_TEX", "b.png");
        AssetManager::get().LoadTexture("TILESET_TEX", "TILESET.png");
        AssetManager::get().LoadTexture("BENNY_ANIM_TEX", "Benny_Animations-Sheet.png");
        AssetManager::get().LoadTexture("MACHO_ANIM_TEX", "Macho_Animation-Sheet.png");
        AssetManager::get().LoadTexture("CHERRY_ANIM_TEX", "Cherry_SpriteSheet.png");
        AssetManager::get().LoadTexture("PEAR_ANIM_TEX", "Pear_SpriteShee.png");
        AssetManager::get().LoadTexture("BARTER_ANIM_TEX", "Barther.png");
        AssetManager::get().LoadTexture("NPC_ANIM_TEX", "NPC_Animation_Sheet.png");
        AssetManager::get().LoadTexture("LEVEL_ASSET_TEX", "Level_Assets_00.png");

        /* Audio */
        audioController.AddAudioSource(new AudioSource("BGM", BGM_VOLUME, true, "The Happy Man.mp3"));
        audioController.AddAudioSource(new AudioSource("Activate", SFX_VOLUME, false, "Activate.mp3"));
        audioController.AddAudioSource(new AudioSource("Barter_swap", SFX_VOLUME, false, "Barter_swap.mp3"));
        audioController.AddAudioSource(new AudioSource("Char_fall", SFX_VOLUME, false, "Char_fall.mp3"));
        audioController.AddAudioSource(new AudioSource("Char_jump", SFX_VOLUME, false, "Char_jump.mp3"));
        audioController.AddAudioSource(new AudioSource("Cherry_inRange", SFX_VOLUME, false, "Cherry_inRange.mp3"));
        audioController.AddAudioSource(new AudioSource("Cherry_outRange", SFX_VOLUME, false, "Cherry_outRange.mp3"));
        audioController.AddAudioSource(new AudioSource("Deactivate", SFX_VOLUME, false, "Deactivate.mp3"));
        audioController.AddAudioSource(new AudioSource("Door_open-close", SFX_VOLUME, false, "Door_open-close.mp3"));
        audioController.AddAudioSource(new AudioSource("Elevator", SFX_VOLUME, false, "Elevator.mp3"));
        audioController.AddAudioSource(new AudioSource("Macho_pickup", SFX_VOLUME, false, "Macho_pickup.mp3"));
        audioController.AddAudioSource(new AudioSource("Macho_throw", SFX_VOLUME, false, "Macho_throw.mp3"));
        audioController.AddAudioSource(new AudioSource("NPC_rescue", SFX_VOLUME, false, "NPC_rescue.mp3"));

#pragma endregion

#pragma region SceneLoading
        sceneManager.PushScene(new MainMenu());
        sceneManager.PushScene(new TestingScene());
        sceneManager.PushScene(new Level2());
        sceneManager.PushScene(new Level3());

#pragma endregion

#pragma region GUI_LOADING

        //tempgui = new GameObject();
        ////EntityManager::get().AddEntity(tempgui);

        //tempgui->GetComponent<Transform>().scale = Vector2D_float(32.0f * RATIO, 16.0f * RATIO);

        //tempgui->AddComponent<SpriteRenderer>(SpriteRenderer::GUI_LAYER, "B_MESH", "B_TEX", 1.0f, &tempCam, false);
        //tempgui->AddComponent<GUI_Button>("TestButton1");

        //gui_arr.PushGUI(tempgui);

        //tempgui = new GameObject();
        ////EntityManager::get().AddEntity(tempgui);

        //tempgui->AddComponent<Transform>(0, 100);
        //tempgui->GetComponent<Transform>().scale = Vector2D_float(32.0f * RATIO, 16.0f * RATIO);

        //tempgui->AddComponent<SpriteRenderer>(SpriteRenderer::GUI_LAYER, "B_MESH", "B_TEX", 1.0f, &tempCam, false);
        //tempgui->AddComponent<GUI_Button>("TestButton2");

        //gui_arr.PushGUI(tempgui);

#pragma endregion

        //For Testing SceneManager Only
        currentScene = sceneManager[0];

        currentScene->Init();
        
        running = true;
    }

    void Engine::NextScene() {      
        currentScene->Clean();
        nextScene_Num++;
        nextScene_Num %= sceneManager.VectorSize();
        currentScene = sceneManager[nextScene_Num];
        currentScene->Init();
    }

    void Engine::Draw() {   
        //For Testing SceneManager Only
        currentScene->Draw();
        /*gui_arr.OnDraw();*/

        //user_interface.UpdateUserInterface();

        glfwSwapBuffers(WindowProperties::get());
    }

    void Engine::Update() {
        glClearColor(0.3f, 0.3f, 0.5f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        //For Testing SceneManager Only
        currentScene->Update();

        /*gui_arr.OnUpdate();*/

        glfwSetKeyCallback(WindowProperties::get(), window_key_callback);
        glfwSetWindowSizeCallback(WindowProperties::get(), window_size_callback);
        glfwSetWindowCloseCallback(WindowProperties::get(), window_close_callback);
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

        //For Testing SceneManager Only
        currentScene->Clean();

        audioController.Stop();

        //std::cout << "Closing window..." << std::endl << "System Shutdown" << std::endl;
        SR_SYSTEM_INFO("Closing window...");
        SR_SYSTEM_INFO("System Shutdown");
        //user_interface.TerminateUserInterface();
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
    void window_close_callback(GLFWwindow* window)
    {
        Engine::get().Quit();
    }
    void window_key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) 
    {
        if (key == SR_KEY_0 && action == GLFW_PRESS) {
            Engine::get().NextScene();
        }

        /*if (key == SR_KEY_1 && action == GLFW_PRESS) 
        {
            currentScene->Clean();
            currentScene = sceneManager[0];
            currentScene->Init();
        }
        else if (key == SR_KEY_2 && action == GLFW_PRESS)
        {
            currentScene->Clean();
            currentScene = sceneManager[1];
            currentScene->Init();
        }
        else if(key == SR_KEY_3 && action == GLFW_PRESS)
        {
            currentScene->Clean();
            currentScene = sceneManager[2];
            currentScene->Init();
        }*/
    }
}