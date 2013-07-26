// AntAppSkeleton.cpp

#include "AntAppSkeleton.h"

AntAppSkeleton::AntAppSkeleton()
: m_bar(NULL)
{
}

AntAppSkeleton::~AntAppSkeleton()
{
    ///@todo Delete this before glfw
    //delete m_bar;
}

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

bool AntAppSkeleton::initGL(int argc, char **argv)
{
    TwInit(TW_OPENGL, NULL);
    _InitializeBar();
    return TriAppSkeleton::initGL(argc, argv);
}

void AntAppSkeleton::display() const
{
    TriAppSkeleton::display();
    TwDraw(); ///@todo Should this go first? Will it write to a depth buffer?
}

void AntAppSkeleton::mouseDown(int button, int state, int x, int y)
{
    int ant = TwEventMouseButtonGLFW(button, state);
    if (ant != 0)
        return;
    TriAppSkeleton::mouseDown(button, state, x, y);
}

void AntAppSkeleton::mouseMove(int x, int y)
{
    TwEventMousePosGLFW(x, y);
    TriAppSkeleton::mouseMove(x, y);
}

void AntAppSkeleton::mouseWheel(int x, int y)
{
    TwEventMouseWheelGLFW(x);
    //TriAppSkeleton::mouseWheel(x, y);
}

void AntAppSkeleton::keyboard(int key, int x, int y)
{
    int ant = TwEventKeyGLFW(key, 0);
    if (ant != 0)
        return;
    TriAppSkeleton::keyboard(key, x, y);
}

void AntAppSkeleton::charkey(unsigned int key)
{
    int ant = TwEventCharGLFW(key, 0);
    if (ant != 0)
        return;
    TriAppSkeleton::keyboard(key, 0, 0);
}
