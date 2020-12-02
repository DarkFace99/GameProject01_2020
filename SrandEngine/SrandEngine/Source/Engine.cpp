#include "Engine.h"

/* TEST */
#include "SpriteRenderer.h"
#include "TileSelector.h"
#include "RigidBody.h"
#include "Animator.h"
#include "Camera.h"
#include "Collision.h"
#include "Input.h"
#include "Button.h"
#include "Door.h"
#include "Elevator.h"

#define RATIO 1280.0f / 480.0f

GameObject* gameObject;

GameObject* button;
GameObject* door;

GameObject* benny;
GameObject* macho;

Camera camera(glm::vec3(0, 0, 0), glm::vec3(0, 0, -1), glm::vec3(0, 1, 0), 1.0f, 0.0f);

IOSystem::Input ioSystem(&camera);

std::vector<glm::vec4> tile_info;

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

    AssetManager::get().LoadMesh("TILESET_MESH", 8, 8);
    AssetManager::get().LoadTexture("TILESET_TEX", "Assets/TILESET.png");
    std::cout << std::endl;

    AssetManager::get().LoadMesh("BENNY_ANIM_MESH", 21);
    AssetManager::get().LoadTexture("BENNY_ANIM_TEX", "Assets/Benny_Animations-Sheet.png");

    /* Tile Set */
    {
        /* First Row */
        for (int i = 0; i < 30; i++)
        {
            if (i > 5 && i < 29) { tile_info.push_back(glm::vec4(8 + (i * 16), 8, 2, 6)); }
            else { tile_info.push_back(glm::vec4(8 + (i * 16), 8, 2, 5)); }

        }
        /* Second Row */
        for (int i = 0; i < 7; i++)
        {
            if (i > 5) { tile_info.push_back(glm::vec4(8 + (29 * 16), 24, 1, 5)); }
            else if (i == 5) { tile_info.push_back(glm::vec4(8 + (i * 16), 24, 3, 5)); }
            else { tile_info.push_back(glm::vec4(8 + (i * 16), 24, 2, 5)); }
        }
        /* Third Row */
        for (int i = 0; i < 7; i++)
        {
            if (i > 5) { tile_info.push_back(glm::vec4(8 + (29 * 16), 40, 1, 5)); }
            else if (i == 5) { tile_info.push_back(glm::vec4(8 + (i * 16), 40, 3, 6)); }
            else { tile_info.push_back(glm::vec4(8 + (i * 16), 40, 2, 6)); }
        }
        /* Forth Row */
        tile_info.push_back(glm::vec4(8 + (29 * 16), 56, 1, 5));
        /* Fifth Row */
        for (int i = 8; i < 14; i++)
        {
            if (i == 8) { tile_info.push_back(glm::vec4(8 + (i * 16), 72, 1, 2)); }
            else { tile_info.push_back(glm::vec4(8 + (i * 16), 72, 2, 2)); }
        }
        for (int i = 18; i < 30; i++)
        {
            if (i == 29) { tile_info.push_back(glm::vec4(8 + (i * 16), 72, 2, 6)); }
            else { tile_info.push_back(glm::vec4(8 + (i * 16), 72, 2, 2)); }
        }
        /* Tenth Row */
        for (int i = 15; i < 24; i++)
        {
            if (i == 23) { tile_info.push_back(glm::vec4(8 + (i * 16), 148, 3, 2)); }
            else if (i == 15) { tile_info.push_back(glm::vec4(8 + (i * 16), 148, 1, 4)); }
            else if (i == 16) { tile_info.push_back(glm::vec4(8 + (i * 16), 148, 2, 4)); }
            else { tile_info.push_back(glm::vec4(8 + (i * 16), 148, 2, 2)); }
        }
        /* Eleventh Row */
        for (int i = 9; i < 17; i++)
        {
            if (i == 9) { tile_info.push_back(glm::vec4(8 + (i * 16), 164, 1, 4)); }
            else if (i == 15) { tile_info.push_back(glm::vec4(8 + (i * 16), 164, 2, 6)); }
            else if (i == 16) { tile_info.push_back(glm::vec4(8 + (i * 16), 164, 3, 6)); }
            else { tile_info.push_back(glm::vec4(8 + (i * 16), 164, 2, 2)); }
        }
        /* Remaining Row */
        for (int i = 1; i < 6; i++)
        {
            if (i < 5) { tile_info.push_back(glm::vec4(152, 164 + (i * 16), 6, 5)); }
            else { tile_info.push_back(glm::vec4(152, 164 + (i * 16), 6, 6)); }
        }
    }

    for (int i = 0; i < tile_info.size(); i++) 
    {
        gameObject = new GameObject();
        manager->AddEntity(gameObject);

        gameObject->GetComponent<Transform>().position = Vector2D_float((-240.0f + tile_info[i].x) * RATIO, (-135.0f + tile_info[i].y) * RATIO);
        gameObject->GetComponent<Transform>().scale = Vector2D_float(16.0f * RATIO, 16.0f * RATIO);

        gameObject->AddComponent<SpriteRenderer>(SpriteRenderer::TILE_LAYER, "TILESET_MESH", "TILESET_TEX", 1.0f, &camera, false);
        gameObject->AddComponent<TileSelector>(8, 8);
        
        gameObject->GetComponent<TileSelector>().SetTile(tile_info[i].z, tile_info[i].w);
        gameObject->AddComponent<BoxCollider2D>(BoxCollider2D::TILE_COLLISION, gameObject->GetComponent<Transform>().scale.x, gameObject->GetComponent<Transform>().scale.y);

        objManager.push_back(gameObject);
    }
    
    gameObject = new GameObject();
    manager->AddEntity(gameObject);
    gameObject->GetComponent<Transform>().position = Vector2D_float(0.0f, 300.0f);
    gameObject->GetComponent<Transform>().scale = Vector2D_float(24.0f * RATIO, 24.0f * RATIO);
    gameObject->AddComponent<SpriteRenderer>("BENNY_ANIM_MESH", "BENNY_ANIM_TEX", 1.0f, &camera, false);
    gameObject->AddComponent<RigidBody>(0.01f);
    // anim_set
    gameObject->AddComponent<Animator>(21, 100);
    gameObject->GetComponent<Animator>().SetState("BENNY_IDLE", 0, 6);
    gameObject->GetComponent<Animator>().SetState("BENNY_RUN", 8, 16);
    gameObject->GetComponent<Animator>().SetState("BENNY_JUMP", 18, 18);
    gameObject->GetComponent<Animator>().SetState("BENNY_FALL", 19, 19);
    gameObject->AddComponent<BoxCollider2D>(BoxCollider2D::CHARACTER_COLLISION, gameObject->GetComponent<Transform>().scale.x, gameObject->GetComponent<Transform>().scale.y,
        false /* overlap */, true /* movable */, "BENNY_ANIM_MESH", &camera);

    player = gameObject; // check collision
    benny = player;

    objManager.push_back(gameObject);

    ioSystem.AddCharacterList("Benny", benny);
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
        if (objManager[i]->GetComponent<BoxCollider2D>().GetTag() == BoxCollider2D::TILE_COLLISION)
            continue;

        for (int j = 0; j < objManager.size(); j++) 
        {
            if (Collision::AABB(objManager[i]->GetComponent<BoxCollider2D>(), objManager[j]->GetComponent<BoxCollider2D>())
                && objManager[i]->GetComponent<BoxCollider2D>().GetTag() == BoxCollider2D::CHARACTER_COLLISION) 
            {
                if (Collision::IsOnGround(*objManager[i], *objManager[j])) {
                    objManager[i]->GetComponent<RigidBody>().SetVelocityY(0.0f);
                }
            }
        }
    }

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
