// GlutAppSkeleton.cpp

#ifdef _WIN32
#  define WINDOWS_LEAN_AND_MEAN
#  define NOMINMAX
#  include <windows.h>
#endif
#include <stdlib.h>
#include <string.h>

#include <GL/glew.h>

#include "GlutAppSkeleton.h"

#include "GL/GLUtils.h"
#include "GL/ShaderFunctions.h"
#include "MatrixMath.h"
#include "utils/Logger.h"
#include "paramgl.h"


void GlutAppSkeleton::glut_PrintString(void *font, const char *str)
{
    int l = (int)strlen(str);
    for (int i=0; i<l; ++i)
    {
        glutBitmapCharacter(font, *str++);
    }
}




GlutAppSkeleton::GlutAppSkeleton()
: TriAppSkeleton()
{
    g_colorVal = 0.0f;
    curMouseAction = None;
    
    paramlist = NULL;
    paramlistA = NULL;

    InitParameters();
}

GlutAppSkeleton::~GlutAppSkeleton()
{
}

void GlutAppSkeleton::InitParameters()
{
    // create a new parameter list
    {
        paramlistA = new ParamListGL("Parameters");
        paramlistA->SetBarColorInner(0.8f, 0.2f, 0.2f);

        paramlistA->AddParam(new Param<float>("rotation.x", g_rotation.x,
                                       0.0f, 360.0f, .1f, &(g_rotation.x)));
        paramlistA->AddParam(new Param<float>("rotation.y", g_rotation.y,
                                       0.0f, 360.0f, .1f, &(g_rotation.y)));
        paramlistA->AddParam(new Param<float>("rotation.z", g_rotation.z,
                                       0.0f, 360.0f, .1f, &(g_rotation.z)));
    }
    paramlist = paramlistA;
}


///
/// Another layer of abstraction for printing text to screen.
/// Allows us to easily use uniforms for color when shaders are the norm.
///
/// @param font A glut \#define like GLUT_BITMAP_HELVETICA_12.
/// @param color A float3 rgb color value.
/// @param prog A GL shader program to set the color as uniform.
/// @param pos An int2 screen space pixel coordinate pair.
/// @param str A pointer to char(string) of ASCII text to print.
///
void GlutAppSkeleton::GlutDrawText(
    void*  font,
    const float3 color,
    const GLuint prog,
    const int2   pos,
    const char*  str) const
{
    if (prog == 0)
    {
        ///@todo Log an error
        return;
    }

    glUniform3f(getUniLoc(prog, "u_col"), color.x, color.y, color.z);
    glRasterPos2i(pos.x, pos.y);
    glut_PrintString(font, str);
}


void GlutAppSkeleton::drawOverlay() const
{
    glUseProgram(g_progOverlay);

    /// Set up a simple orthographic projection matrix for text
    float proj[16];
    glhOrtho(proj,
        0.0f, (float)g_windowWidth,
        0.0f, (float)g_windowHeight,
        -1.0f, 1.0f);
    glUniformMatrix4fv(getUniLoc(g_progOverlay, "prmtx"), 1, false, proj);

    std::ostringstream oss;
    oss.str("");
    oss.clear();
    oss << g_cameraLocation.x << " "
        << g_cameraLocation.y << " "
        << g_cameraLocation.z << "   "
        << g_rotation.x << " "
        << g_rotation.y;

    float3 white = {g_colorVal,1,1};
    int2 pos = make_int2(10,20);
    GlutDrawText(
        GLUT_BITMAP_HELVETICA_12,
        white,
        g_progOverlay,
        pos,
        oss.str().c_str());

    glUseProgram(0);
}


/// Draw param sliders with fixed pipeline
void GlutAppSkeleton::drawSlidersFixedPipeline() const
{
    glUseProgram(0);
    glBlendFunc(GL_ONE_MINUS_DST_COLOR, GL_ZERO); // invert color
    glEnable(GL_BLEND);
    if (paramlist)
        paramlist->Render(0, 0);
    glDisable(GL_BLEND);
}


void GlutAppSkeleton::display() const
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

        //glutWireSphere(1.0f, 16, 16);
        drawObject();
    }
    glUseProgram(0);

    drawOverlay();

    drawSlidersFixedPipeline();

    CHECK_GL_ERROR_MACRO();
}


void GlutAppSkeleton::mouseDown(int button, int state, int x, int y)
{
    {
        if (paramlist && paramlist->Mouse(x, y, button, state))
        {
            curMouseAction = AdjustParam;
            return;
        }
    }
    curMouseAction = None;

    TriAppSkeleton::mouseDown(button, state, x, y);
}


void GlutAppSkeleton::mouseMove(int x, int y)
{
    if (AdjustParam == curMouseAction)
    {
        if (paramlist && paramlist->Motion(x, y))
        {
        }
        return;
    }

    TriAppSkeleton::mouseMove(x,y);
}


void GlutAppSkeleton::keyboard(int key, int x, int y)
{
    switch(key)
    {
    default:
        break;

    case 27: // Escape
        exit(0);
        break;
    }
    TriAppSkeleton::keyboard(key, x, y);
}


void GlutAppSkeleton::resize(int w, int h)
{
    g_windowWidth = w;
    g_windowHeight = h;

    glViewport(0,0, (GLsizei)w, (GLsizei)h);
}


bool GlutAppSkeleton::initGL(int argc, char **argv)
{
    bool ret = TriAppSkeleton::initGL(argc, argv);

    glClearColor(0.0, 0.0, 0.0, 0.0);
    //glDisable(GL_LIGHTING);

    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    CHECK_GL_ERROR_MACRO();

    return ret;
}
