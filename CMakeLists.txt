# Hacked up version of http://prideout.net/blog/?p=22
# Thank you Philip Rideout for the excellent public domain code!

CMAKE_MINIMUM_REQUIRED( VERSION 2.6 )
PROJECT( GLSkeleton )

INCLUDE(cmake_modules/HardcodeShaders.cmake)

#
# Choose from the following frameworks here:
# GLUT, GLFW2, GLFW3, SDL, PEZ
#
SET( GL_FRAMEWORK "GLFW2" )

#
# Platform-dependent section: Windows, Linux, MacOS
#
IF( WIN32 )
    #
    # Set this hard-coded directory path to wherever the
    # glut and glew directories reside locally.
    #
    SET( GL_LIBS_HOME "C:/lib" )

    SET( GLUT_ROOT "${GL_LIBS_HOME}/glut-3.7.6-bin" )
    INCLUDE_DIRECTORIES( "${GLUT_ROOT}" )
    LINK_DIRECTORIES   ( "${GLUT_ROOT}" )

    SET( GLFW_ROOT "${GL_LIBS_HOME}/glfw-2.7.8.bin.WIN32" )
    INCLUDE_DIRECTORIES( "${GLFW_ROOT}/include" )
    LINK_DIRECTORIES   ( "${GLFW_ROOT}/lib-msvc100" )

    SET( GLFW3_ROOT "${GL_LIBS_HOME}/glfw-3.0.1.bin.WIN32" )
    INCLUDE_DIRECTORIES( "${GLFW3_ROOT}/include" )
    LINK_DIRECTORIES   ( "${GLFW3_ROOT}/lib-msvc100" )

    SET( SDL_ROOT "${GL_LIBS_HOME}/SDL-1.2.15" )
    INCLUDE_DIRECTORIES( "${SDL_ROOT}/include" )
    LINK_DIRECTORIES   ( "${SDL_ROOT}/lib/x86" )

    SET( GLEW_ROOT "${GL_LIBS_HOME}/glew" )
    INCLUDE_DIRECTORIES( "${GLEW_ROOT}/include" )
    LINK_DIRECTORIES   ( "${GLEW_ROOT}/lib" )
    #ADD_DEFINITIONS( -DGLEW_STATIC )

    #
    # Framework and platform-dependent lib section
    #
    IF( GL_FRAMEWORK STREQUAL "SDL" )
        SET( FRAMEWORK_LIBS SDL.lib )
    ELSEIF( GL_FRAMEWORK STREQUAL "GLFW2" )
        SET( FRAMEWORK_LIBS glfw.lib )
    ELSEIF( GL_FRAMEWORK STREQUAL "GLFW3" )
        SET( FRAMEWORK_LIBS glfw3.lib )
    ELSEIF( GL_FRAMEWORK STREQUAL "PEZ" )
        SET( CONSOLE_SYSTEM WIN32 )
    ENDIF()

    SET( PLATFORM_LIBS
        ${FRAMEWORK_LIBS}
        opengl32
        glew32.lib )

    IF( GL_FRAMEWORK STREQUAL "PEZ" )
        SET( SKELETON_FILE "pez_windows_skeleton.cpp" )
    ENDIF()
ELSEIF( APPLE )
    INCLUDE_DIRECTORIES ( /System/Library/Frameworks )
    FIND_LIBRARY(COCOA_LIBRARY Cocoa)
    FIND_LIBRARY(GLUT_LIBRARY GLUT )
    FIND_LIBRARY(OpenGL_LIBRARY OpenGL )
    MARK_AS_ADVANCED (COCOA_LIBRARY
                      GLUT_LIBRARY
                      OpenGL_LIBRARY)
    SET(PLATFORM_LIBS ${COCOA_LIBRARY} ${GLUT_LIBRARY} ${OpenGL_LIBRARY})
ELSEIF( UNIX )
    FIND_PACKAGE( OpenGL REQUIRED )
    FIND_PACKAGE( GLUT REQUIRED )
    FIND_PACKAGE( SDL )
    INCLUDE_DIRECTORIES( ${OPENGL_INCLUDE_DIRS}  ${GLUT_INCLUDE_DIRS} )
    INCLUDE_DIRECTORIES(${SDL_INCLUDE_DIR})

    #
    # Framework and platform-dependent lib section
    #
    IF( GL_FRAMEWORK STREQUAL "SDL" )
        SET( FRAMEWORK_LIBS SDL )
    ELSEIF( GL_FRAMEWORK STREQUAL "GLFW2" )
        SET( FRAMEWORK_LIBS glfw )
    ELSEIF( GL_FRAMEWORK STREQUAL "GLFW3" )
        SET( FRAMEWORK_LIBS glfw3 )
    ELSEIF( GL_FRAMEWORK STREQUAL "PEZ" )
        #SET( CONSOLE_SYSTEM WIN32 )
    ENDIF()

    SET( PLATFORM_LIBS ${FRAMEWORK_LIBS} glut GLEW X11 GL ${OPENGL_LIBRARIES} )

    IF( GL_FRAMEWORK STREQUAL "PEZ" )
        SET( SKELETON_FILE "pez_linux_skeleton.cpp" )
    ENDIF()
ENDIF()

#
# Platform-independent section
#
INCLUDE_DIRECTORIES(
    src
    src/utils
    src/utils/cudaSDK
    src/vectormath
    src/appskeleton
)

FILE( GLOB_RECURSE UTIL_SRC        src/utils/*.cpp  src/utils/*.h )
FILE( GLOB_RECURSE VECTORMATH_SRC  src/vectormath/*.cpp  src/vectormath/*.h )
FILE( GLOB_RECURSE APPSKELETON_SRC src/appskeleton/*.cpp  src/appskeleton/*.h )

ADD_LIBRARY( PROJ_LIBS
    ${UTIL_SRC}
    ${VECTORMATH_SRC}
    ${APPSKELETON_SRC}
)

#
# Choose a skeleton framework here. All will link to glut for the text.
#
IF( GL_FRAMEWORK STREQUAL "SDL" )
    SET( SKELETON_FILE "sdl_skeleton.cpp" )
ELSEIF( GL_FRAMEWORK STREQUAL "GLFW2" )
    SET( SKELETON_FILE "glfw2_skeleton.cpp" )
ELSEIF( GL_FRAMEWORK STREQUAL "GLFW3" )
    SET( SKELETON_FILE "glfw3_skeleton.cpp" )
ELSEIF( GL_FRAMEWORK STREQUAL "GLUT" )
    SET( SKELETON_FILE "glut_skeleton.cpp" )
#ELSEIF( GL_FRAMEWORK STREQUAL "PEZ" ) # handled in platform-dependent section
ENDIF()

IF( GL_FRAMEWORK STREQUAL "PEZ" )
    ADD_EXECUTABLE( ${PROJECT_NAME} WIN32 src/${SKELETON_FILE} )
ELSE()
    ADD_EXECUTABLE( ${PROJECT_NAME} src/${SKELETON_FILE} )
ENDIF()

TARGET_LINK_LIBRARIES( ${PROJECT_NAME}
    PROJ_LIBS
    ${PLATFORM_LIBS}
)

