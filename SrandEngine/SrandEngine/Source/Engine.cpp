#include "Engine.h"

/* TEST */
#include "SpriteRenderer.h"
#include "RigidBody.h"
#include "Animator.h"
#include "Camera.h"
#include "Collision.h"
#include "Input.h"
#include "Button.h"
#include "Door.h"
#include "Elevator.h"

GameObject* gameObject;

GameObject* button;
GameObject* door;

GameObject* benny;
GameObject* macho;

Camera camera(glm::vec3(0, 0, 0), glm::vec3(0, 0, -1), glm::vec3(0, 1, 0), 1.0f, 0.0f);

IOSystem::Input ioSystem(&camera);

Engine* Engine::s_instance = nullptr;

Engine::Engine() {
	window = nullptr;
	running = false;
}

void Engine::Init() {
    
    /* Initialize the library */
    std::cout << "Initializing GLFW..." << std::endl;
    if (!glfwInit())
    {
        std::cout << "Error! Cannot initializing GLFW" << std::endl;
    }

    /* Create a windowed mode window and its OpenGL context */
    std::cout << "Initializing Window..." << std::endl;
    window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGTH, WINDOW_NAME, (FULLSCREEN) ? glfwGetPrimaryMonitor() : NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        std::cout << "Error! Cannot create window" << std::endl;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    /*Vsync on = 1, off = 0*/
    glfwSwapInterval(1);

    /*Initializing GLEW*/
    std::cout << "Initializing GLEW..." << std::endl;
    if (glewInit() != GLEW_OK)
    {
        std::cout << "Error! Cannot initializing GLEW" << std::endl;
    }

    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
    std::cout << "--------------------------------------------------------------------------------" << std::endl;
    std::cout << "                            |--System Initialized--|                            " << std::endl;
    std::cout << "--------------------------------------------------------------------------------" << std::endl;
    std::cout << "                          Version: " << glGetString(GL_VERSION) << std::endl;
    std::cout << "--------------------------------------------------------------------------------" << std::endl;

    manager = new EntityManager();

    /* Initialize Shader */
    Shader::get()->InitializeShader();

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glDisable(GL_CULL_FACE);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


    /* Test */

    AssetManager::get().LoadMesh("TEST_MESH", 1);
    AssetManager::get().LoadMesh("TEST_MESH", 1);
    AssetManager::get().LoadMesh("TEST2_MESH", 1);
    AssetManager::get().LoadMesh("TILEMESH", 1);
    AssetManager::get().LoadMesh("BUTTONMESH", 1);
    AssetManager::get().LoadTexture("TEST_TEX", "Assets/Benny.png");
    AssetManager::get().LoadTexture("TEST_TEX", "Assets/!!Benny??.png");
    AssetManager::get().LoadTexture("TEST_TEX", "Assets/Cherry.png");
    AssetManager::get().LoadTexture("TEST2_TEX", "Assets/Cherry.png");
    AssetManager::get().LoadTexture("TILETEX", "Assets/blank.png");
    AssetManager::get().LoadTexture("BUTTONTEX", "Assets/b.png");
    std::cout << std::endl;

    /* Anim_Test */
    AssetManager::get().LoadMesh("BENNY_ANIM_MESH", 21);
    AssetManager::get().LoadTexture("BENNY_ANIM_TEX", "Assets/Benny_Animations-Sheet.png");
    AssetManager::get().LoadMesh("MACHO_ANIM_MESH", 20);
    AssetManager::get().LoadTexture("MACHO_ANIM_TEX", "Assets/Macho_Animation-Sheet.png");

    // Tile=================================================================================================================================
    float posX = -128.0f;
    for (int i = 0; i < 10; i++)
    {
        gameObject = new GameObject();
        manager->AddEntity(gameObject);
        /* std::cout << "initial position: " << gameObject->GetComponent<Transform>().position << std::endl;
         std::cout << std::endl;*/

        posX += 64;

        gameObject->GetComponent<Transform>().position = Vector2D_float(posX, -296.0f);
        gameObject->GetComponent<Transform>().scale = Vector2D_float(64.0f, 64.0f);
        std::cout << "Set transform:" << std::endl;
        std::cout << "position: " << gameObject->GetComponent<Transform>().position << std::endl;
        std::cout << "scale: " << gameObject->GetComponent<Transform>().scale << std::endl;
        std::cout << std::endl;

        gameObject->AddComponent<SpriteRenderer>("TILEMESH", "TILETEX", 1.0f, &camera, true);
        std::cout << std::endl;

        gameObject->AddComponent<BoxCollider2D>(gameObject->GetComponent<Transform>().scale.x, gameObject->GetComponent<Transform>().scale.y);

        objManager.push_back(gameObject);
    }

    // Button===============================================================================================================================
    gameObject = new GameObject();
    manager->AddEntity(gameObject);
    gameObject->GetComponent<Transform>().position = Vector2D_float(128.0f, -232.0f);
    gameObject->GetComponent<Transform>().scale = Vector2D_float(64.0f, 64.0f);

    gameObject->AddComponent<SpriteRenderer>("BUTTONMESH", "BUTTONTEX", 1.0f, &camera, true);
    std::cout << std::endl;

    gameObject->AddComponent<Button>();

    gameObject->AddComponent<BoxCollider2D>(gameObject->GetComponent<Transform>().scale.x, gameObject->GetComponent<Transform>().scale.y/2.0f,
            true, false, "BUTTONMESH", &camera);
    gameObject->GetComponent<BoxCollider2D>().SetOffset(0, -20);

    button = gameObject;

    // Test Obstacle========================================================================================================================
    std::cout << "Obj 2:" << std::endl;
    gameObject = new GameObject();
    manager->AddEntity(gameObject);
    gameObject->GetComponent<Transform>().position = Vector2D_float(256.0f, -200.0f);
    gameObject->GetComponent<Transform>().scale = Vector2D_float(96.0f, 96.0f);
    gameObject->AddComponent<SpriteRenderer>("TEST2_MESH", "TEST2_TEX", 0.1f, &camera, false);
    std::cout << std::endl;

    gameObject->AddComponent<BoxCollider2D>(gameObject->GetComponent<Transform>().scale.x, gameObject->GetComponent<Transform>().scale.y / 2.0f,
            false, false, "TEST2_MESH", &camera);
    gameObject->GetComponent<BoxCollider2D>().SetOffset(0, -gameObject->GetComponent<Transform>().scale.y * (float)1/2);

    gameObject->AddComponent<Elevator>(3);
    gameObject->GetComponent<Elevator>().AddConnectedButtons(button);

    door = gameObject;
    objManager.push_back(gameObject);

    // Benny================================================================================================================================
    gameObject = new GameObject();
    manager->AddEntity(gameObject);
    gameObject->GetComponent<Transform>().position = Vector2D_float(0.0f, 0.0f);
    gameObject->GetComponent<Transform>().scale = Vector2D_float(96.0f, 96.0f);
    gameObject->AddComponent<SpriteRenderer>("BENNY_ANIM_MESH", "BENNY_ANIM_TEX", 1.0f, &camera, false);
    gameObject->AddComponent<RigidBody>(0.01f);
    // anim_set
    gameObject->AddComponent<Animator>(21, 100);
    gameObject->GetComponent<Animator>().SetState("BENNY_IDLE", 0, 6);
    gameObject->GetComponent<Animator>().SetState("BENNY_RUN", 8, 16);
    gameObject->GetComponent<Animator>().SetState("BENNY_JUMP", 18, 18);
    gameObject->GetComponent<Animator>().SetState("BENNY_FALL", 19, 19);
    gameObject->AddComponent<BoxCollider2D>(gameObject->GetComponent<Transform>().scale.x, gameObject->GetComponent<Transform>().scale.y,
        false /* overlap */, true /* movable */, "BENNY_ANIM_MESH", &camera);

    player = gameObject; // check collision
    benny = player;
    ioSystem.AddCharacterList("Benny", benny);

    // Macho================================================================================================================================
    gameObject = new GameObject();
    manager->AddEntity(gameObject);
    gameObject->GetComponent<Transform>().position = Vector2D_float(0.0f, 0.0f);
    gameObject->GetComponent<Transform>().scale = Vector2D_float(96.0f, 96.0f);
    gameObject->AddComponent<SpriteRenderer>("MACHO_ANIM_MESH", "MACHO_ANIM_TEX", 1.0f, &camera, false);
    gameObject->AddComponent<RigidBody>(0.01f);
    // anim_set
    gameObject->AddComponent<Animator>(20, 100);
    gameObject->GetComponent<Animator>().SetState("MACHO_IDLE", 0, 5);
    gameObject->GetComponent<Animator>().SetState("MACHO_RUN", 13, 19);

    gameObject->AddComponent<BoxCollider2D>(gameObject->GetComponent<Transform>().scale.x, gameObject->GetComponent<Transform>().scale.y,
        false /* overlap */, true /* movable */, "MACHO_ANIM_MESH", &camera);
    
    macho = gameObject;
    ioSystem.AddCharacterList("Macho", macho);

    ioSystem.SetControl("Benny");

    running = true;
}

void Engine::Draw(){
    manager->Draw();
    glfwSwapBuffers(window);
}

void Engine::Update() {
    glClearColor(0.3f, 0.3f, 0.5f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    manager->Update();

    for (int i = 0; i < objManager.size(); i++)
    {
        Collision::AABB(benny->GetComponent<BoxCollider2D>(), objManager[i]->GetComponent<BoxCollider2D>());
        Collision::AABB(macho->GetComponent<BoxCollider2D>(), objManager[i]->GetComponent<BoxCollider2D>());
    }

    if (Collision::IsOnGround(*benny)) {
        benny->GetComponent<RigidBody>().SetVelocityY(0.0f);
    }

    if (Collision::IsOnGround(*macho)) {
        macho->GetComponent<RigidBody>().SetVelocityY(0.0f);
    }
    
    //std::cout << "PlayerPos: " << player->GetComponent<Transform>().position << std::endl;
}

void Engine::FixedUpdate(TimeStep ts) {
    //std::cout << "FPS: " << 1.0f/TimeStep::get().GetSeconds() << std::endl;
}

void Engine::Event() {
    // input
    ioSystem.IOUpdate(window);
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) { Quit(); }
}

void Engine::Clean() {
    AssetManager::get().Clean();
    Shader::get()->DeleteShader();
    delete manager;

    std::cout << "Closing window..." << std::endl << "System Shutdown" << std::endl;
    glfwTerminate();
}

void Engine::Quit() {
    running = false;
}
