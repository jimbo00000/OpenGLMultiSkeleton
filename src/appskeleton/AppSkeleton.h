// AppSkeleton.h

#pragma once

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

class AppSkeleton
{
public:
    AppSkeleton();
    virtual ~AppSkeleton();

    virtual void display() const;
    virtual void mouseDown(int button, int state, int x, int y);
    virtual void mouseMove(int x, int y);
    virtual void keyboard(int key, int x, int y);
    virtual void resize(int w, int h);
    virtual bool initGL(int argc, char **argv);
    
    virtual const int w() const { return g_windowWidth; }
    virtual const int h() const { return g_windowHeight; }

protected:
    virtual void _InitShaders() {}

    int g_windowWidth;
    int g_windowHeight;

private: // Disallow copy ctor and assignment operator
    AppSkeleton(const AppSkeleton&);
    AppSkeleton& operator=(const AppSkeleton&);
};
