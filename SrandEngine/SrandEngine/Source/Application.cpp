#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm.hpp>

/*Include Custom header files*/
#include "System.h"
#include "TestRender.h"

/*Initialize Window*/
GLFWwindow* window;

/*---------------------------------Temporary---------------------------------*/
// variables to keep track the current, previous and next game state
unsigned int	gGameStateInit;
unsigned int	gGameStateCurr;
unsigned int	gGameStatePrev;
unsigned int	gGameStateNext;

// pointer to functions for game state levelX functions
void(*GameStateLoad)() = 0;
void(*GameStateInit)() = 0;
void(*GameStateUpdate)(double, long, int&) = 0;
void(*GameStateDraw)() = 0;
void(*GameStateFree)() = 0;
void(*GameStateUnload)() = 0;
/*---------------------------------Temporary---------------------------------*/

//Frame Rate
double  frameTime = 0.0;
long    framenumber = 0.0;

int main(void)
{
    /*All System Initialize*/
    SystemInit(SCREEN_WIDTH, SCREEN_HEIGTH, "Hello World");
    RendererInit();

    GameStateLoad = GameStateLevel1Load;
    GameStateInit = GameStateLevel1Init;
    GameStateUpdate = GameStateLevel1Update;
    GameStateDraw = GameStateLevel1Draw;
    GameStateFree = GameStateLevel1Free;
    GameStateUnload = GameStateLevel1Unload;
    GameStateLoad();

    FrameInit();
    GameStateInit();
    framenumber = 0;

    /* Loop until the user closes the window or user press escape key*/
    while (!glfwWindowShouldClose(window) && glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS)
    {
        frameTime = FrameStart();
        framenumber++;

        /* Poll for and process events */
        glfwPollEvents();

        int state = 0;
        GameStateUpdate(frameTime, framenumber, state);
        GameStateDraw();

    }

    GameStateFree();
    GameStateUnload();

    /*Shutdown all system*/
    SystemShutdown();
    return 0;
}