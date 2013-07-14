// GlutAppSkeleton.h

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

class ParamListGL;

class GlutAppSkeleton : public TriAppSkeleton
{
public:
    GlutAppSkeleton();
    virtual ~GlutAppSkeleton();

    virtual void display() const;
    virtual void mouseDown(int button, int state, int x, int y);
    virtual void mouseMove(int x, int y);
    virtual void keyboard(int key, int x, int y);
    virtual void resize(int w, int h);
    virtual bool initGL(int argc, char **argv);

protected:
    static void glut_PrintString(void *font, const char *str);

    void InitParameters();
    void GlutDrawText(      void*  font,
                      const float3 color,
                      const GLuint prog,
                      const int2   pos,
                      const char*  str) const;
    void drawOverlay() const;
    void drawSlidersFixedPipeline() const;

    float g_colorVal;
    ParamListGL* paramlist;
    ParamListGL* paramlistA;
    
    // This will prevent the view from rotating when the user adjusts a param.
    enum mouseAction {
        None,
        Rotate,
        AdjustParam
    };
    mouseAction curMouseAction;

private: // Disallow copy ctor and assignment operator
    GlutAppSkeleton(const GlutAppSkeleton&);
    GlutAppSkeleton& operator=(const GlutAppSkeleton&);
};
