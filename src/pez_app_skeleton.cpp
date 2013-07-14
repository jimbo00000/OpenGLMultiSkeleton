// pez_app_skeleton.cpp

#include "TriAppSkeleton.h"

AppSkeleton g_app;


///
/// User-defined skeleton callbacks below.
///
const char* PezInitialize(int width, int height)
{
    g_app.initGL(0, NULL);
    return "Pez Intro";
}

void PezUpdate(unsigned int elapsedMilliseconds)
{
}

void PezRender()
{
    g_app.display();
}

void PezHandleMouse(int x, int y, int action)
{
    //if (action == PEZ_DOWN)
    //    pressing = 1;
    //else if (action == PEZ_UP)
    //    pressing = 0;
}
