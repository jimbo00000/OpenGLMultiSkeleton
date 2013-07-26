// TriAppSkeleton.cpp

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

#include "TriAppSkeleton.h"

TriAppSkeleton::TriAppSkeleton()
: AppSkeleton()
, which_button(-1)
{
    g_cameraLocation = make_float3(0.0f, -3.0f, 0.0f);
    g_lookVector     = make_float3(0.0f,  1.0f, 0.0f);
    g_upVector       = make_float3(0.0f,  0.0f, 1.0f);
    g_rotation       = make_float3(0.0f, 90.0f, 0.0f);
    g_distance     = 0.0f;
    g_viewAngle    = 45.0;

    which_button = -1;
    modifier_mode = 0;

    g_progBasic = 0;
    g_progOverlay = 0;
}

TriAppSkeleton::~TriAppSkeleton()
{
}

bool TriAppSkeleton::initGL(int argc, char **argv)
{
    bool ret = AppSkeleton::initGL(argc, argv); /// calls _InitShaders
    return ret;
}

/// Shaders must be created *after* the OpenGL context is created.
/// This virtual function will be called by AppSkeleton::initGL.
void TriAppSkeleton::_InitShaders()
{
    // InitShaders()
    LOG_INFO("Initializing shaders.");
    {
        g_progBasic   = makeShaderByName("basic");
        g_progOverlay = makeShaderByName("overlay");
    }
}


void TriAppSkeleton::drawObject() const
{
    GLfloat vVertices[] = { 0.0f,  0.5f, 0.0f, 
                           -0.5f, -0.5f, 0.0f,
                            0.5f, -0.5f, 0.0f };
    GLfloat vColors[]   = { 1.0f,  0.0f, 0.0f, 
                            0.0f,  1.0f, 0.0f,
                            0.0f,  0.0f, 1.0f };
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, vVertices);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, vColors);
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);

    CHECK_GL_ERROR_MACRO();
}



void TriAppSkeleton::display() const
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);

    glUseProgram(g_progBasic);
    {
        /// Set up our 3D transformation matrices
        float modelviewMatrix[16];
        float projectionMatrix[16];

        float3 origin = g_cameraLocation + g_lookVector;
        glhLookAtf2(modelviewMatrix,
                    g_cameraLocation,
                    origin,
                    g_upVector);
        glhTranslate(modelviewMatrix, 0.0f, g_distance, 0.0f);
        glhRotate(modelviewMatrix,  g_rotation.x, 0.0f, 0.0f, 1.0f);
        glhRotate(modelviewMatrix,  g_rotation.y, 1.0f, 0.0f, 0.0f);

        glhPerspectivef2(projectionMatrix, g_viewAngle, (float)g_windowWidth/(float)g_windowHeight, 0.004, 500.0);

        glUniformMatrix4fv(getUniLoc(g_progBasic, "mvmtx"), 1, false, modelviewMatrix);
        glUniformMatrix4fv(getUniLoc(g_progBasic, "prmtx"), 1, false, projectionMatrix);

        drawObject();
    }
    glUseProgram(0);

    CHECK_GL_ERROR_MACRO();
}

void TriAppSkeleton::mouseDown(int button, int state, int x, int y)
{
    which_button = button;
    oldx = newx = x;
    oldy = newy = y;
    if (state == 0) // 0 == GLFW_RELEASE
    {
        which_button = -1;
    }
}

void TriAppSkeleton::mouseMove(int x, int y)
{
    int mmx, mmy;
    float thresh = 4;

    if (modifier_mode & GLUT_ACTIVE_SHIFT) { thresh /= 0.01f; }

    oldx = newx;
    oldy = newy;
    newx = x;
    newy = y;
    mmx = x-oldx;
    mmy = y-oldy;

    if (which_button == GLUT_LEFT_BUTTON) //GLFW_MOUSE_BUTTON_1
    {
        g_rotation.x += (float)mmx/thresh;
        g_rotation.y += (float)mmy/thresh;
    }
    else if (which_button == GLUT_RIGHT_BUTTON)
    {
        g_distance += (float)mmx/thresh;
    }
}

void TriAppSkeleton::keyboard(int key, int x, int y)
{
    AppSkeleton::keyboard(key, x, y);
}
