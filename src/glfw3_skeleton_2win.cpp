// glfw3_skeleton.cpp

#ifdef _WIN32
#  define WINDOWS_LEAN_AND_MEAN
#  define NOMINMAX
#  include <windows.h>
#endif

#include <sstream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>


#ifdef USE_CUDA
#else
#  include "vector_make_helpers.h"
#endif

#include "GL/ShaderFunctions.h"
#include "MatrixMath.h"
#include "utils/Logger.h"
#include "paramgl.h"

#include "AntAppSkeleton.h"

AntAppSkeleton g_app;

int running = 0;
GLFWwindow* g_pWindow = NULL;
GLFWwindow* g_pWindow2 = NULL;

void display()
{
    /// display control window
    {
        glfwMakeContextCurrent(g_pWindow);
        g_app.display();
        glfwSwapBuffers(g_pWindow);
    }

    /// display secondary window
    if (g_pWindow2 != NULL)
    {
        glfwMakeContextCurrent(g_pWindow2);
        glUseProgram(0);
        glClearColor(1,0,0,1);
        glClear(GL_COLOR_BUFFER_BIT);
        glfwSwapBuffers(g_pWindow2);
    }
}

void mouseDown(GLFWwindow* pWin, int button, int action, int mods)
{
    double x,y;
    glfwGetCursorPos(g_pWindow, &x, &y);
    g_app.mouseDown(button, action, x, y);
}

void mouseMove(GLFWwindow* window, double x, double y)
{
    //int x,y;
    //glfwGetMousePos(&x, &y);
    g_app.mouseMove(x, y);
}

void mouseWheel(GLFWwindow* window, double x, double y)
{
    g_app.mouseWheel(x, y);
}

void keyboard(GLFWwindow* window, int key, int action, int, int)
{
    g_app.keyboard(key, 0,0);
}

void charkey(GLFWwindow* window, unsigned int key)
{
    g_app.charkey(key);
}

void resize(GLFWwindow* window, int w, int h)
{
    g_app.resize(w,h);
    TwWindowSize(w,h);
}

bool initGL(int argc, char **argv)
{
    return g_app.initGL(argc, argv);
}

static void error_callback(int error, const char* description)
{
    fprintf(stderr, "Error: %s\n", description);
}

bool initGlfw(int argc, char **argv)
{
    glfwSetErrorCallback(error_callback);

    if (!glfwInit())
        return -1;

    //glfwWindowHint(GLFW_VISIBLE, GL_FALSE);

    /// Init Control window containing AntTweakBar
    {
        const int w = 640;
        const int h = 480;
        g_pWindow = glfwCreateWindow(w, h, "GLSkeleton - GLFW 3", NULL, NULL);
        if (!g_pWindow)
        {
            glfwTerminate();
            return -1;
        }
        glfwMakeContextCurrent(g_pWindow);

        glfwSetWindowSizeCallback (g_pWindow, resize);
        glfwSetMouseButtonCallback(g_pWindow, mouseDown);
        glfwSetCursorPosCallback  (g_pWindow, mouseMove);
        glfwSetScrollCallback     (g_pWindow, mouseWheel);
        glfwSetKeyCallback        (g_pWindow, keyboard);
        glfwSetCharCallback       (g_pWindow, charkey);

        ///@note Bad size errors will be thrown if this is not called at init
        TwWindowSize(w, h);
    }

    /// Init secondary window
    {
        g_pWindow2 = glfwCreateWindow(200, 200, "Second window", NULL, NULL);
        if (!g_pWindow2)
        {
            glfwTerminate();
            exit(EXIT_FAILURE);
        }

        glfwMakeContextCurrent(g_pWindow2);

        //glfwSetWindowPos(g_pWindow2, 100 + (i & 1) * 300, 100 + (i >> 1) * 300);
        glfwShowWindow(g_pWindow2);
    }

    glfwMakeContextCurrent(g_pWindow);

    return 1;
}


/// Dump a list of monitor info to Log and stdout.
/// http://www.glfw.org/docs/3.0/monitor.html
void PrintMonitorInfo()
{
    int count;
    GLFWmonitor** monitors = glfwGetMonitors(&count);
    printf("Found %d monitors:\n", count);
    LOG_INFO("Found %d monitors:", count);
    for (int i=0; i<count; ++i)
    {
        GLFWmonitor* pMonitor = monitors[i];
        if (pMonitor == NULL)
            continue;
        printf("  Monitor %d:\n", i);
        LOG_INFO("  Monitor %d:", i);

        /// Monitor name
        const char* pName = glfwGetMonitorName(pMonitor);
        printf("    Name: %s\n", pName);
        LOG_INFO("    Name: %s", pName);

        /// Monitor Physical Size
        int widthMM, heightMM;
        glfwGetMonitorPhysicalSize(pMonitor, &widthMM, &heightMM);
        //const double dpi = mode->width / (widthMM / 25.4);
        printf("    physical size: %d x %d mm\n");
        LOG_INFO("    physical size: %d x %d mm");

        /// Modes
        const GLFWvidmode* mode = glfwGetVideoMode(pMonitor);
        printf("    Current mode:  %dx%d @ %dHz (RGB %d %d %d bits)\n",
                mode->width,
                mode->height,
                mode->refreshRate,
                mode->redBits,
                mode->greenBits, 
                mode->blueBits);
        LOG_INFO("    Current mode:  %dx%d @ %dHz (RGB %d %d %d bits)",
                mode->width,
                mode->height,
                mode->refreshRate,
                mode->redBits,
                mode->greenBits, 
                mode->blueBits);

#if 0
        int modeCount;
        const GLFWvidmode* modes = glfwGetVideoModes(pMonitor, &modeCount);
        printf("    %d Modes:\n", modeCount);
        LOG_INFO("    %d Modes:", modeCount);
        for (int j=0; j<modeCount; ++j)
        {
            const GLFWvidmode& m = modes[j];
            printf("      %dx%d @ %dHz (RGB %d %d %d bits)\n",
                m.width, m.height, m.refreshRate, m.redBits, m.greenBits, m.blueBits);
            LOG_INFO("      %dx%d @ %dHz (RGB %d %d %d bits)",
                m.width, m.height, m.refreshRate, m.redBits, m.greenBits, m.blueBits);
        }
#endif
    }
}

////////////////////////////////////////////////////////////////////////////////
// Program main
////////////////////////////////////////////////////////////////////////////////
int main(int argc, char *argv[])
{
    if (!initGlfw(argc, argv))
        return 0;
    if (!initGL(argc, argv))
        return 0;

    PrintMonitorInfo();

    LOG_INFO("Starting main loop.");

    running = GL_TRUE;
    //g_timer.reset();
    while (
        running &&
        !glfwWindowShouldClose(g_pWindow) &&
        !glfwWindowShouldClose(g_pWindow2)
        )
    {
        //float dt = (float)g_timer.seconds();
        //timestep(dt);
        //g_timer.reset();
        display();
        //running = running && glfwGetWindowParam(GLFW_OPENED);
        glfwPollEvents();
    }
    
    TwTerminate();
    glfwTerminate();
    return 0;
}
