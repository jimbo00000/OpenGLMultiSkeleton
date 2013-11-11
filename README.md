# OpenGLMultiSkeleton

## Description
Cross-platform OpenGL skeleton for multiple frameworks. Fork and select from GLFW3, GLFW2,
Glut, SDL and Cinder with a simple tweak to a CMake variable.

The build process requires CMake and Python 2.7. Python is used to generate
a C++ source header with hardcoded strings for shader source in text files under shaders/.

## Setup
### Windows
    Create the directory build/ in project's home(alongside CMakeLists.txt)
    Shift+right-click it in Explorer->"Open command window here"
    ...\build> cmake .. -G "Visual Studio 10"
    Double-click the only .sln file in build to open it in Visual Studio
    Right-click the GLSkeleton project in Solution Explorer, "Set as StartUp Project"
    F7 to build, F5 to build and run

### Linux
    $> mkdir build
    $> cd build
    $> cmake .. && make
    $> ./GLSkeleton
