// AppSkeleton.cpp

#ifdef _WIN32
#  define WINDOWS_LEAN_AND_MEAN
#  define NOMINMAX
#  include <windows.h>
#endif

#include <GL/glew.h>

#include "AppSkeleton.h"

#include "GL/GLUtils.h"
#include "GL/ShaderFunctions.h"
#include "MatrixMath.h"
#include "utils/Logger.h"
#include "paramgl.h"


AppSkeleton::AppSkeleton()
: g_windowWidth(600)
, g_windowHeight(400)
{
}

AppSkeleton::~AppSkeleton()
{
}

void AppSkeleton::display() const
{
    glClearColor(1,0,0,1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    CHECK_GL_ERROR_MACRO();
}

void AppSkeleton::mouseDown(int button, int state, int x, int y)
{
}

void AppSkeleton::mouseMove(int x, int y)
{
}

void AppSkeleton::keyboard(int key, int x, int y)
{
    switch (key)
    {
    case 257: // Escape in GLFW
    case 27: //Esc
        exit(0);
        break;

    default:
        LOG_INFO("key: %d %c\n", key , key );
        printf("key: %d %c\n", key , key);
        break;
    }
}

void AppSkeleton::resize(int w, int h)
{
}

/// Glew should be the first thing we initialize. After that, all initialization of GL state.
bool AppSkeleton::initGL(int argc, char **argv)
{
#if 1
    GLenum err = glewInit();
    if (GLEW_OK != err)
    {
        // Problem: glewInit failed, something is seriously wrong.
        LOG_INFO("Error: %s\n", glewGetErrorString(err));
    }
    LOG_INFO("Status: Using GLEW %s\n", glewGetString(GLEW_VERSION));
#endif

#if   defined(WIN32)
    //wglSwapIntervalEXT(0);
#elif defined(LINUX)
    glxSwapIntervalSGI(0);
#endif

    _InitShaders();

    return true;
}
