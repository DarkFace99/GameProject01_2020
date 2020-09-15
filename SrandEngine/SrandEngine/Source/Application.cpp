#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm.hpp>

/*Include Custom header files*/
#include "System.h"

/*Initialize Window*/
GLFWwindow* window;

#define SCREEN_WIDTH    1920
#define SCREEN_HEIGTH   1080

double frameTime = 0.0;

int main(void)
{
    /*All System Initialize*/
    SystemInit(SCREEN_WIDTH, SCREEN_HEIGTH, "Hello World");
    FrameInit();
    InitializeShader();

    /* Loop until the user closes the window or user press escape key*/
    while (!glfwWindowShouldClose(window) && glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS)
    {
        frameTime = FrameStart();

        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    /*Shutdown all system*/
    SystemShutdown();
    return 0;
}