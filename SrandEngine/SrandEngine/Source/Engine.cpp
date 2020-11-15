#include "Engine.h"

/* TEST */
#include "EntityManager.h"
#include "SpriteRenderer.h"
#include "Camera.h"
EntityManager* manager;
GameObject* gameObject;
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


    /* Initialize Shader */
    Shader::get()->InitializeShader();

    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glDisable(GL_CULL_FACE);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


    /* Test */
    manager = new EntityManager();
    gameObject = new GameObject();
    
    manager->AddEntity(gameObject);
    std::cout << "initial position: " << gameObject->GetComponent<Transform>().position << std::endl;
    std::cout << std::endl;

    AssetManager::get().LoadMesh("TEST_MESH", 1);
    AssetManager::get().LoadTexture("TEST_TEX", "Benny.png");
    std::cout << std::endl;
    
    gameObject->AddComponent<Transform>(100, 100, 100, 100);
    gameObject->AddComponent<SpriteRenderer>("TEST_MESH", "TEST_TEX", 1.0f, camera);

    std::cout << "position: " << gameObject->GetComponent<Transform>().position << std::endl;
    std::cout << "scale: " << gameObject->GetComponent<Transform>().scale << std::endl;

    running = true;
}

void Engine::Draw(){
    manager->Draw();
}

void Engine::Update() {
    glClearColor(0.3f, 0.3f, 0.5f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    manager->Update();

    glfwSwapBuffers(window);
}

void Engine::FixedUpdate() {

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
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) 
    {
        std::cout << "W" << std::endl;
    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
    {
        std::cout << "A" << std::endl;
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
    {
        std::cout << "S" << std::endl;
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
    {
        std::cout << "D" << std::endl;
    }
}
