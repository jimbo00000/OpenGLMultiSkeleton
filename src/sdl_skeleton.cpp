// SDL skeleton

#ifdef _WIN32
#  define WINDOWS_LEAN_AND_MEAN
#  define NOMINMAX
#  include <windows.h>
#endif

#include <sstream>

#include <GL/glew.h>
#include <SDL.h>
#undef main

#ifdef USE_CUDA
#else
#  include "vector_make_helpers.h"
#endif

#include "GL/ShaderFunctions.h"
#include "MatrixMath.h"
#include "utils/Logger.h"
#include "paramgl.h"

#include "GlutAppSkeleton.h"

const int SCREEN_WIDTH  = 640;
const int SCREEN_HEIGHT = 480;
const int SCREEN_BPP    = 32;

TriAppSkeleton g_app;
int running = 0;


void display()
{
    g_app.display();
    SDL_GL_SwapBuffers();
}


bool init()
{
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
        return false;

    if (SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_OPENGL) == NULL)
        return false;

    SDL_WM_SetCaption( "GL Skeleton - SDL", NULL );

    return true;
}

bool initGL(int argc, char **argv)
{
    return g_app.initGL(argc, argv);
}

int main(int argc, char *argv[])
{
    if( init() == false )
        return 1;

    if (!initGL(argc, argv))
        return 0;

    SDL_Event event;
    int quit = 0;
    while (quit == 0)
    {
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_KEYDOWN)
            {
                if (event.key.keysym.sym == SDLK_ESCAPE)
                    quit = 1;
            }
            else if (event.type == SDL_QUIT)
            {
                quit = 1;
            }
        }

        display();
    }

    SDL_Quit();
    return 0;
}
