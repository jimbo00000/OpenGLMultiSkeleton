// TriAppSkeleton.h

#pragma once

#ifdef __APPLE__
#include "opengl/gl.h"
#endif

#ifdef _WIN32
#  define WINDOWS_LEAN_AND_MEAN
#  define NOMINMAX
#  include <windows.h>
#endif
#include <stdlib.h>
//#include <GL/GL.h>

#ifdef USE_CUDA
#else
#  include "vector_make_helpers.h"
#endif

#include "AppSkeleton.h"

class TriAppSkeleton : public AppSkeleton
{
public:
    TriAppSkeleton();
    virtual ~TriAppSkeleton();

    virtual void display() const;
    virtual void mouseDown(int button, int state, int x, int y);
    virtual void mouseMove(int x, int y);
    virtual void keyboard(int key, int x, int y);
    //virtual void resize(int w, int h);
    virtual bool initGL(int argc, char **argv);


protected:
    virtual void _InitShaders();
    virtual void drawObject() const;

    float3  g_cameraLocation;
    float3  g_lookVector;
    float3  g_upVector;
    float3  g_rotation;
    GLfloat g_distance;

    double g_viewAngle;

    // mouse motion internal state
    int oldx, oldy, newx, newy;
    int which_button;
    int modifier_mode;

    GLuint g_progBasic;
    GLuint g_progOverlay;


private: // Disallow copy ctor and assignment operator
    TriAppSkeleton(const TriAppSkeleton&);
    TriAppSkeleton& operator=(const TriAppSkeleton&);
};
