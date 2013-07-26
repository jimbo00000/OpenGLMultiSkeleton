// Glfw Skeleton for OpenGL 2.0

#ifdef _WIN32
#  define WINDOWS_LEAN_AND_MEAN
#  define NOMINMAX
#  include <windows.h>
#endif

#include <sstream>

#include <GL/glew.h>
#include <GL/glfw.h>
#include <AntTweakBar.h>

#ifdef USE_CUDA
#else
#  include "vector_make_helpers.h"
#endif

#include "GL/ShaderFunctions.h"
#include "MatrixMath.h"
#include "utils/Logger.h"
#include "paramgl.h"

#include "AntAppSkeleton.h"

AntAppSkeleton g_app;

int running = 0;


void display()
{
    g_app.display();
    glfwSwapBuffers();
}

void GLFWCALL mouseDown(int button, int action)
{
    int x,y;
    glfwGetMousePos(&x, &y);
    g_app.mouseDown(button, action, x, y);
}

void GLFWCALL mouseMove(int x, int y)
{
    //int x,y;
    //glfwGetMousePos(&x, &y);
    g_app.mouseMove(x, y);
}

void GLFWCALL keyboard(int key, int action)
{
    g_app.keyboard(key, 0,0);
}

void resize(int w, int h)
{
    g_app.resize(w,h);
    TwWindowSize(w,h);
}

bool initGL(int argc, char **argv)
{
    return g_app.initGL(argc, argv);
}

bool initGlfw(int argc, char **argv)
{
    glfwInit();

    if (!glfwOpenWindow(
        g_app.w(), g_app.h(),
        8,8,8,8,
        0,8,
        GLFW_WINDOW //GLFW_FULLSCREEN
        ))
    {
        glfwTerminate();
        return 0;
    }

    glfwSetWindowTitle        ("GL Skeleton - GLFW 2");
    glfwSetMouseButtonCallback(mouseDown);
    glfwSetMousePosCallback   (mouseMove);
    glfwSetKeyCallback        (keyboard);
    glfwSetWindowSizeCallback (resize);


    GLenum err = glewInit();
    if (GLEW_OK != err)
    {
        // Problem: glewInit failed, something is seriously wrong.
        LOG_INFO("Error: %s\n", glewGetErrorString(err));
    }
    LOG_INFO("Status: Using GLEW %s\n", glewGetString(GLEW_VERSION));

    TwWindowSize(g_app.w(), g_app.h());

    return true;
}

////////////////////////////////////////////////////////////////////////////////
// Program main
////////////////////////////////////////////////////////////////////////////////
int main(int argc, char *argv[])
{
    if (!initGlfw(argc, argv))
        return 0;
    if (!initGL(argc, argv))
        return 0;

    LOG_INFO("Starting main loop.");

    running = GL_TRUE;
    //g_timer.reset();
    while (running)
    {
        //float dt = (float)g_timer.seconds();
        //timestep(dt);
        //g_timer.reset();
        display();
        running = running && glfwGetWindowParam(GLFW_OPENED);
    }

    glfwTerminate();
    return 0;
}
