#include "Engine.h"

/* TEST */
#include "SpriteRenderer.h"
#include "RigidBody.h"
#include "Animator.h"
#include "Camera.h"
#include "Collision.h"
GameObject* gameObject;
GameObject* testEntity;
GameObject* player;

Camera camera(glm::vec3(0, 0, 0), glm::vec3(0, 0, -1), glm::vec3(0, 1, 0), 1.0f, 0.0f);

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
    gameObject = new GameObject();
    manager->AddEntity(gameObject);
    std::cout << "initial position: " << gameObject->GetComponent<Transform>().position << std::endl;
    std::cout << std::endl;

    AssetManager::get().LoadMesh("TEST_MESH", 1);
    AssetManager::get().LoadMesh("TEST_MESH", 1);
    AssetManager::get().LoadMesh("TEST2_MESH", 1);
    AssetManager::get().LoadTexture("TEST_TEX", "Assets/Benny.png");
    AssetManager::get().LoadTexture("TEST_TEX", "Assets/!!Benny??.png");
    AssetManager::get().LoadTexture("TEST_TEX", "Assets/Cherry.png");
    AssetManager::get().LoadTexture("TEST2_TEX", "Assets/Cherry.png");
    std::cout << std::endl;

    /* Anim_Test */
    AssetManager::get().LoadMesh("ANIM_TEST_MESH", 21);
    AssetManager::get().LoadTexture("ANIM_TEST_TEX", "Assets/Benny_Animations-Sheet.png");

    gameObject->GetComponent<Transform>().position = Vector2D_float(-150.0f, 200.0f);
    gameObject->GetComponent<Transform>().scale = Vector2D_float(96.0f, 96.0f);
    std::cout << "Set transform:" <<std::endl;
    std::cout << "position: " << gameObject->GetComponent<Transform>().position << std::endl;
    std::cout << "scale: " << gameObject->GetComponent<Transform>().scale << std::endl;
    std::cout << std::endl;

    gameObject->AddComponent<SpriteRenderer>("TEST_MESH", "TEST_TEX", 1.0f, camera, true);
    std::cout << std::endl;

    gameObject->AddComponent<RigidBody>(0.2f); // rigidBody
    gameObject->AddComponent<BoxCollider2D>(gameObject->GetComponent<Transform>().scale.x, gameObject->GetComponent<Transform>().scale.y);
    testEntity = gameObject;


    // gameObj2
    std::cout << "Obj 2:" << std::endl;
    gameObject = new GameObject();
    manager->AddEntity(gameObject);
    gameObject->GetComponent<Transform>().position = Vector2D_float(0.0f, 0.0f);
    gameObject->GetComponent<Transform>().scale = Vector2D_float(96.0f, 96.0f);
    gameObject->AddComponent<SpriteRenderer>("TEST2_MESH", "TEST2_TEX", 0.5f, camera, false);

    // gameObj3 Anim_Test
    gameObject = new GameObject();
    manager->AddEntity(gameObject);
    gameObject->GetComponent<Transform>().position = Vector2D_float(-150.0f, 0.0f);
    gameObject->GetComponent<Transform>().scale = Vector2D_float(96.0f, 96.0f);
    gameObject->AddComponent<SpriteRenderer>("ANIM_TEST_MESH", "ANIM_TEST_TEX", 1.0f, camera, false);
    // anim_set
    gameObject->AddComponent<Animator>(21, 100);
    gameObject->GetComponent<Animator>().SetState("BENNY_IDLE", 0, 6);
    gameObject->GetComponent<Animator>().SetState("BENNY_RUN", 8, 16);
    gameObject->GetComponent<Animator>().SetState("BENNY_JUMP", 18, 18);
    gameObject->GetComponent<Animator>().SetState("BENNY_FALL", 19, 19);
    gameObject->AddComponent<BoxCollider2D>(gameObject->GetComponent<Transform>().scale.x, gameObject->GetComponent<Transform>().scale.y);

    player = gameObject; // check collision

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
    std::cout << "Collision:" << Collision::AABB(player->GetComponent<BoxCollider2D>(), testEntity->GetComponent<BoxCollider2D>()) << std::endl;
}

void Engine::FixedUpdate(TimeStep ts) {
    //std::cout << "FPS: " << 1.0f/ts.GetSeconds() << "\t GetMilliseconds: " << ts.GetMilliseconds() << std::endl;

}

void Engine::Event() {
    // input
    glfwPollEvents();
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) { Quit(); }
    keyUpdate(window);
    glfwSetKeyCallback(window, key_callBack);
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

/*---------------------------------*/
/*		     Input Test		       */
/*---------------------------------*/

// Once
void key_callBack(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_TAB && action == GLFW_PRESS)
    {
        std::cout << key << std::endl;   
    }
}

// Continuous
void keyUpdate(GLFWwindow* window)
{
    gameObject->GetComponent<Animator>().PlayState("BENNY_IDLE");
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) 
    {
        std::cout << "W" << std::endl;
        gameObject->GetComponent<Animator>().PlayState("BENNY_JUMP");
    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
    {
        std::cout << "A" << std::endl;
        gameObject->GetComponent<Animator>().PlayState("BENNY_RUN");
        gameObject->GetComponent<SpriteRenderer>().SetFlip(true);
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
    {
        std::cout << "S" << std::endl;
        gameObject->GetComponent<Animator>().PlayState("BENNY_FALL");
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
    {
        std::cout << "D" << std::endl;
        gameObject->GetComponent<Animator>().PlayState("BENNY_RUN");
        gameObject->GetComponent<SpriteRenderer>().SetFlip(false);
    }

}
