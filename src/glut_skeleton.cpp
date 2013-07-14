// Glut Skeleton for OpenGL 2.0

#include <sstream>

#include <GL/glew.h>
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#ifdef USE_CUDA
#else
#  include "vector_make_helpers.h"
#endif

#include "GL/ShaderFunctions.h"
#include "MatrixMath.h"
#include "utils/Logger.h"
#include "paramgl.h"

#include "GlutAppSkeleton.h"

GlutAppSkeleton g_app;


void display()
{
    g_app.display();
    glutSwapBuffers();
}

void mouseDown(int button, int state, int x, int y)
{
    g_app.mouseDown(button, state, x, y);
    glutPostRedisplay();
}

void mouseMove(int x, int y)
{
    g_app.mouseMove(x,y);
    glutPostRedisplay();
}

void keyboard(unsigned char key, int x, int y)
{
    g_app.keyboard(key, x, y);
    glutPostRedisplay();
}

void resize(int w, int h)
{
    g_app.resize(w,h);
    glutPostRedisplay();
}

bool initGL(int argc, char **argv)
{
    return g_app.initGL(argc, argv);
}

bool initGlut(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
    glutInitWindowSize(g_app.w(), g_app.h());
    glutCreateWindow("glut - OpenGL 2.0");
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutMouseFunc(mouseDown);
    glutMotionFunc(mouseMove);
    glutReshapeFunc(resize);
    //glutSpecialFunc(special);
    return true;
}

////////////////////////////////////////////////////////////////////////////////
// Program main
////////////////////////////////////////////////////////////////////////////////
int main(int argc, char *argv[])
{
    if (!initGlut(argc, argv))
        return 0;
    if (!initGL(argc, argv))
        return 0;

    LOG_INFO("Starting glut main loop.");
    glutMainLoop();
    return 0;
}
