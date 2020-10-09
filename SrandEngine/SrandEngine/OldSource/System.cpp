#include "System.h"

double currTime = 0.0, prevTime = 0.0;

int SystemInit(int width, int height, const std::string name)
{
    /* Initialize the library */
    std::cout << "Initializing GLFW..." << std::endl;
    if (!glfwInit())
    {
        std::cout << "Error! Cannot initializing GLFW" << std::endl;
        return -1;
    }

    /* Create a windowed mode window and its OpenGL context */
    std::cout << "Initializing Window..." << std::endl;
    window = glfwCreateWindow(width, height, "Engine", NULL /*glfwGetPrimaryMonitor()*/, NULL);
    if (!window)
    {
        glfwTerminate();
        std::cout << "Error! Cannot create window" << std::endl;
        return -1;
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
        return -1;
    }

    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
    std::cout << "--------------------------------------------------------------------------------" << std::endl;
    std::cout << "                            |--System Initialized--|                            " << std::endl;
    std::cout << "--------------------------------------------------------------------------------" << std::endl;
    std::cout << "                          Version: " << glGetString(GL_VERSION) << std::endl;
    std::cout << "--------------------------------------------------------------------------------" << std::endl;

}
void SystemShutdown()
{
    std::cout << "Closing window..." << std::endl << "System Shutdown" << std::endl;
    DeleteShader();
    glfwTerminate();
}

void FrameInit()
{
    prevTime = glfwGetTime();
}
double FrameStart()
{
    currTime = glfwGetTime();

    double result = currTime - prevTime;
    return result;
}
void FrameEnd()
{
    prevTime = currTime;
}