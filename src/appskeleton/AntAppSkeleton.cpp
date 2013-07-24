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
    double time = 0, dt;// Current time and enlapsed time
    double turn = 0;    // Model turn counter
    double speed = 0.3; // Model rotation speed
    int wire = 0;       // Draw model in wireframe?
    float bgColor[] = { 0.1f, 0.2f, 0.4f };         // Background color 
    unsigned char cubeColor[] = { 255, 0, 0, 128 }; // Model color (32bits RGBA)

    // Create a tweak bar
    m_bar = TwNewBar("TweakBar");
    TwDefine(" GLOBAL help='This example shows how to integrate AntTweakBar with GLFW and OpenGL.' "); // Message added to the help bar.

    // Add 'speed' to 'bar': it is a modifable (RW) variable of type TW_TYPE_DOUBLE. Its key shortcuts are [s] and [S].
    TwAddVarRW(m_bar, "speed", TW_TYPE_DOUBLE, &speed, 
               " label='Rot speed' min=0 max=2 step=0.01 keyIncr=s keyDecr=S help='Rotation speed (turns/second)' ");

    // Add 'wire' to 'bar': it is a modifable variable of type TW_TYPE_BOOL32 (32 bits boolean). Its key shortcut is [w].
    TwAddVarRW(m_bar, "wire", TW_TYPE_BOOL32, &wire, 
               " label='Wireframe mode' key=w help='Toggle wireframe display mode.' ");

    // Add 'time' to 'bar': it is a read-only (RO) variable of type TW_TYPE_DOUBLE, with 1 precision digit
    TwAddVarRO(m_bar, "time", TW_TYPE_DOUBLE, &time, " label='Time' precision=1 help='Time (in seconds).' ");         

    // Add 'bgColor' to 'bar': it is a modifable variable of type TW_TYPE_COLOR3F (3 floats color)
    TwAddVarRW(m_bar, "bgColor", TW_TYPE_COLOR3F, &bgColor, " label='Background color' ");

    // Add 'cubeColor' to 'bar': it is a modifable variable of type TW_TYPE_COLOR32 (32 bits color) with alpha
    TwAddVarRW(m_bar, "cubeColor", TW_TYPE_COLOR32, &cubeColor, 
               " label='Cube color' alpha help='Color and transparency of the cube.' ");
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
    TwEventMouseButtonGLFW(button, state);
}

void AntAppSkeleton::mouseMove(int x, int y)
{
    TwEventMousePosGLFW(x, y);
}

void AntAppSkeleton::mouseWheel(int x, int y)
{
    TwEventMouseWheelGLFW(x);
}

void AntAppSkeleton::keyboard(int key, int x, int y)
{
    TwEventKeyGLFW(key, 0);
}

void AntAppSkeleton::charkey(unsigned int key)
{
    TwEventCharGLFW(key, 0);
}