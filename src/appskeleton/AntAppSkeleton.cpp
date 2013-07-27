// AntAppSkeleton.cpp

#include "AntAppSkeleton.h"

AntAppSkeleton::AntAppSkeleton()
#ifdef USE_ANTTWEAKBAR
: m_bar(NULL)
#endif
{
}

AntAppSkeleton::~AntAppSkeleton()
{
    ///@todo Delete this before glfw
    //delete m_bar;
}

#ifdef USE_ANTTWEAKBAR
void AntAppSkeleton::_InitializeBar()
{
    // Create a tweak bar
    m_bar = TwNewBar("TweakBar");
    TwDefine(" GLOBAL help='This example shows how to integrate AntTweakBar with GLFW and OpenGL.' "); // Message added to the help bar.

    TwAddVarRW(m_bar, "rotation x", TW_TYPE_FLOAT, &g_rotation.x, 
               " label='Rot x' min=0 max=360 step=1.0 keyIncr=a keyDecr=A help='Rotation x' ");
    TwAddVarRW(m_bar, "rotation y", TW_TYPE_FLOAT, &g_rotation.y, 
               " label='Rot y' min=0 max=360 step=1.0 keyIncr=s keyDecr=S help='Rotation y' ");
    TwAddVarRW(m_bar, "rotation z", TW_TYPE_FLOAT, &g_rotation.z, 
               " label='Rot z' min=0 max=360 step=1.0 keyIncr=d keyDecr=D help='Rotation z' ");
}
#endif

bool AntAppSkeleton::initGL(int argc, char **argv)
{
#ifdef USE_ANTTWEAKBAR
    TwInit(TW_OPENGL, NULL);
    _InitializeBar();
#endif
    return TriAppSkeleton::initGL(argc, argv);
}

void AntAppSkeleton::display() const
{
    TriAppSkeleton::display();
#ifdef USE_ANTTWEAKBAR
    TwDraw(); ///@todo Should this go first? Will it write to a depth buffer?
#endif
}

void AntAppSkeleton::mouseDown(int button, int state, int x, int y)
{
#ifdef USE_ANTTWEAKBAR
    int ant = TwEventMouseButtonGLFW(button, state);
    if (ant != 0)
        return;
#endif
    TriAppSkeleton::mouseDown(button, state, x, y);
}

void AntAppSkeleton::mouseMove(int x, int y)
{
#ifdef USE_ANTTWEAKBAR
    TwEventMousePosGLFW(x, y);
#endif
    TriAppSkeleton::mouseMove(x, y);
}

void AntAppSkeleton::mouseWheel(int x, int y)
{
#ifdef USE_ANTTWEAKBAR
    TwEventMouseWheelGLFW(x);
#endif
    //TriAppSkeleton::mouseWheel(x, y);
}

void AntAppSkeleton::keyboard(int key, int x, int y)
{
#ifdef USE_ANTTWEAKBAR
    int ant = TwEventKeyGLFW(key, 0);
    if (ant != 0)
        return;
#endif
    TriAppSkeleton::keyboard(key, x, y);
}

void AntAppSkeleton::charkey(unsigned int key)
{
#ifdef USE_ANTTWEAKBAR
    int ant = TwEventCharGLFW(key, 0);
    if (ant != 0)
        return;
#endif
    TriAppSkeleton::keyboard(key, 0, 0);
}
