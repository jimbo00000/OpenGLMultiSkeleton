// AntAppSkeleton.h

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

#include "TriAppSkeleton.h"

#include <AntTweakBar.h>

class ParamListGL;

class AntAppSkeleton : public TriAppSkeleton
{
public:
    AntAppSkeleton();
    virtual ~AntAppSkeleton();

    virtual void display() const;
    virtual void mouseDown(int button, int state, int x, int y);
    virtual void mouseMove(int x, int y);
    virtual void mouseWheel(int x, int y);
    virtual void keyboard(int key, int x, int y);
    virtual void charkey(unsigned int key);
    virtual bool initGL(int argc, char **argv);

protected:
    void _InitializeBar();
    TwBar* m_bar;

    double speed;

private: // Disallow copy ctor and assignment operator
    AntAppSkeleton(const AntAppSkeleton&);
    AntAppSkeleton& operator=(const AntAppSkeleton&);
};
