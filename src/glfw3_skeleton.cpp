// glfw3_skeleton.cpp

#ifdef _WIN32
#  define WINDOWS_LEAN_AND_MEAN
#  define NOMINMAX
#  include <windows.h>
#endif

#include <sstream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>


#ifdef USE_CUDA
#else
#  include "vector_make_helpers.h"
#endif

#include "GL/ShaderFunctions.h"
#include "MatrixMath.h"
#include "utils/Logger.h"
#include "paramgl.h"

#include "GlutAppSkeleton.h"

TriAppSkeleton g_app;

int running = 0;
GLFWwindow* g_pWindow;

void display()
{
    g_app.display();
    glfwSwapBuffers(g_pWindow);
}

void mouseDown(GLFWwindow* pWin, int button, int action, int mods)
{
    double x,y;
    glfwGetCursorPos(g_pWindow, &x, &y);
    g_app.mouseDown(button, action, x, y);
}

void mouseMove(int x, int y)
{
    //int x,y;
    //glfwGetMousePos(&x, &y);
    g_app.mouseMove(x, y);
}

void keyboard(int key, int action)
{
    g_app.keyboard(key, 0,0);
}

void resize(int w, int h)
{
    g_app.resize(w,h);
}

bool initGL(int argc, char **argv)
{
    return g_app.initGL(argc, argv);
}

bool initGlfw(int argc, char **argv)
{
    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    g_pWindow = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!g_pWindow)
    {
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(g_pWindow);

    glfwSetMouseButtonCallback(g_pWindow, mouseDown);

    return 1;
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
    while (running && !glfwWindowShouldClose(g_pWindow))
    {
        //float dt = (float)g_timer.seconds();
        //timestep(dt);
        //g_timer.reset();
        display();
        //running = running && glfwGetWindowParam(GLFW_OPENED);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
