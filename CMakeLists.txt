# Hacked up version of http://prideout.net/blog/?p=22
# Thank you Philip Rideout for the excellent public domain code!

CMAKE_MINIMUM_REQUIRED( VERSION 2.6 )
PROJECT( GLSkeleton )

INCLUDE(cmake_modules/HardcodeShaders.cmake)

#
# Choose from the following frameworks here:
# GLUT, GLFW2, GLFW3, SDL, SDL2, PEZ, CINDER
#
SET( GL_FRAMEWORK "GLFW3" CACHE STRING "Which OpenGL windowing framework to use" )

SET( USE_ANTTWEAKBAR TRUE CACHE BOOL "Use AntTweakBar" )

#
# Platform-dependent section: Windows, Linux, MacOS
#
IF( WIN32 )
    #
    # Set this hard-coded directory path to wherever the
    # glut and glew directories reside locally.
    #
    SET( GL_LIBS_HOME "C:/lib" CACHE PATH "Location of support libraries" )

    SET( GLUT_ROOT "${GL_LIBS_HOME}/glut-3.7.6-bin" CACHE STRING "GLUT root" )
    SET( GLFW_ROOT "${GL_LIBS_HOME}/glfw-2.7.8.bin.WIN32" CACHE STRING "GLFW2 root" )
    SET( GLFW3_ROOT "${GL_LIBS_HOME}/glfw-3.0.4.bin.WIN32" CACHE STRING "GLFW3 root" )
    SET( SDL_ROOT "${GL_LIBS_HOME}/SDL-1.2.15" CACHE STRING "SDL root" )
    SET( SDL2_ROOT "${GL_LIBS_HOME}/SDL2-2.0.3" CACHE STRING "SDL2 root" )
    SET( GLEW_ROOT "${GL_LIBS_HOME}/glew" CACHE STRING "GLEW root" )
    SET( CINDER_ROOT "${GL_LIBS_HOME}/cinder_0.8.5_vc2010" CACHE STRING "Cinder root" )

    # TODO: remove paramGL dependency on Glut
    INCLUDE_DIRECTORIES( "${GLUT_ROOT}" )
    LINK_DIRECTORIES   ( "${GLUT_ROOT}" )

    INCLUDE_DIRECTORIES( "${GLEW_ROOT}/include" )
    LINK_DIRECTORIES   ( "${GLEW_ROOT}/lib" )
    #ADD_DEFINITIONS( -DGLEW_STATIC )


    #
    # Framework and platform-dependent lib section
    #
    IF( GL_FRAMEWORK STREQUAL "SDL" )
        INCLUDE_DIRECTORIES( "${SDL_ROOT}/include" )
        LINK_DIRECTORIES   ( "${SDL_ROOT}/lib/x86" )
        SET( FRAMEWORK_LIBS SDL.lib )
    ELSEIF( GL_FRAMEWORK STREQUAL "SDL2" )
        INCLUDE_DIRECTORIES( "${SDL2_ROOT}/include" )
        LINK_DIRECTORIES   ( "${SDL2_ROOT}/lib/x86" )
        SET( FRAMEWORK_LIBS SDL2.lib )
    ELSEIF( GL_FRAMEWORK STREQUAL "GLFW2" )
        INCLUDE_DIRECTORIES( "${GLFW_ROOT}/include" )
        LINK_DIRECTORIES   ( "${GLFW_ROOT}/lib-msvc100" )
        SET( FRAMEWORK_LIBS glfw.lib )
    ELSEIF( GL_FRAMEWORK STREQUAL "GLFW3" )
        INCLUDE_DIRECTORIES( "${GLFW3_ROOT}/include" )
        LINK_DIRECTORIES   ( "${GLFW3_ROOT}/lib-msvc110" )
        SET( FRAMEWORK_LIBS glfw3.lib )
    ELSEIF( GL_FRAMEWORK STREQUAL "CINDER" )
        INCLUDE_DIRECTORIES( "${CINDER_ROOT}/include" "${CINDER_ROOT}/boost" )
        LINK_DIRECTORIES   ( "${CINDER_ROOT}/lib" "${CINDER_ROOT}/lib/msw" )
        SET( FRAMEWORK_LIBS optimized cinder.lib debug cinder_d.lib )
        #
        # Force static runtime linking and ignore libcmt.lib in MSVC for cinder
        #
        IF( MSVC )
            foreach(flag_var
                CMAKE_CXX_FLAGS CMAKE_CXX_FLAGS_DEBUG CMAKE_CXX_FLAGS_RELEASE
                CMAKE_CXX_FLAGS_MINSIZEREL CMAKE_CXX_FLAGS_RELWITHDEBINFO)
                if(${flag_var} MATCHES "/MD")
                    string(REGEX REPLACE "/MD" "/MT" ${flag_var} "${${flag_var}}")
                endif(${flag_var} MATCHES "/MD")
            endforeach(flag_var)
            
            SET(CMAKE_EXE_LINKER_FLAGS_DEBUG /NODEFAULTLIB:\"libcmt.lib\")
        ENDIF()

        ADD_DEFINITIONS( "-D_UNICODE" "-DUNICODE" ) #"-DGLEW_STATIC" )
    ELSEIF( GL_FRAMEWORK STREQUAL "PEZ" )
        SET( CONSOLE_SYSTEM WIN32 )
    ENDIF()


    IF( USE_ANTTWEAKBAR )
        SET( ANTTWEAKBAR_ROOT "${GL_LIBS_HOME}/AntTweakBar_116/AntTweakBar" CACHE STRING "AntTweakBar root" )
        INCLUDE_DIRECTORIES( "${ANTTWEAKBAR_ROOT}/include" )
        LINK_DIRECTORIES   ( "${ANTTWEAKBAR_ROOT}/lib" )
        SET( ANT_LIBS AntTweakBar.lib )
        ADD_DEFINITIONS( -DUSE_ANTTWEAKBAR )
    ENDIF( USE_ANTTWEAKBAR )

    SET( PLATFORM_LIBS
        ${FRAMEWORK_LIBS}
        opengl32
        glew32.lib
        ${ANT_LIBS}
        )

    IF( GL_FRAMEWORK STREQUAL "PEZ" )
        SET( SKELETON_FILE "pez_windows_skeleton.cpp" )
    ENDIF()
ELSEIF( APPLE )
    INCLUDE_DIRECTORIES ( /System/Library/Frameworks )
    FIND_LIBRARY(COCOA_LIBRARY Cocoa)
    FIND_LIBRARY(IOKIT_LIBRARY IOKit)
    FIND_LIBRARY(GLUT_LIBRARY GLUT )
    FIND_LIBRARY(OpenGL_LIBRARY OpenGL )
    MARK_AS_ADVANCED (COCOA_LIBRARY
                      GLUT_LIBRARY
                      IOKIT_LIBRARY
                      OpenGL_LIBRARY)
    
    INCLUDE_DIRECTORIES( "/opt/local/include" )
    LINK_DIRECTORIES   ( "/opt/local/lib" )

    IF( GL_FRAMEWORK STREQUAL "SDL" )
        SET( FRAMEWORK_LIBS SDL )
    ELSEIF( GL_FRAMEWORK STREQUAL "SDL2" )
        SET( FRAMEWORK_LIBS SDL2 )
    ELSEIF( GL_FRAMEWORK STREQUAL "GLFW" )
        SET( FRAMEWORK_LIBS glfw )
    ELSEIF( GL_FRAMEWORK STREQUAL "GLFW3" )
        SET( FRAMEWORK_LIBS glfw3 )
    ELSEIF( GL_FRAMEWORK STREQUAL "PEZ" )
        #SET( CONSOLE_SYSTEM WIN32 )
    ENDIF()

    # Update this to your GLFW installation location
    SET( GLFW_ROOT "~/Development/glfw-2.7.7/")
    INCLUDE_DIRECTORIES( "${GLFW_ROOT}/include" )
    LINK_DIRECTORIES   ( "${GLFW_ROOT}/lib" )

    SET( GLFW3_ROOT "~/Development/glfw-3.0.1/")
    INCLUDE_DIRECTORIES( "${GLFW3_ROOT}/include" )
    LINK_DIRECTORIES   ( "${GLFW3_ROOT}/lib" )

    SET(PLATFORM_LIBS ${FRAMEWORK_LIBS} ${COCOA_LIBRARY} ${IOKIT_LIBRARY} ${GLUT_LIBRARY} ${OpenGL_LIBRARY} -lGLEW)

    IF( GL_FRAMEWORK STREQUAL "PEZ" )
        SET( SKELETON_FILE "pez.cocoa.mm" "src/pez_app_skeleton.cpp")
    ENDIF()

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
    ELSEIF( GL_FRAMEWORK STREQUAL "SDL2" )
        SET( FRAMEWORK_LIBS SDL2 )
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
ELSEIF( GL_FRAMEWORK STREQUAL "SDL2" )
    SET( SKELETON_FILE "sdl2_skeleton.cpp" )
ELSEIF( GL_FRAMEWORK STREQUAL "GLFW2" )
    SET( SKELETON_FILE "glfw2_skeleton.cpp" )
ELSEIF( GL_FRAMEWORK STREQUAL "GLFW3" )
    SET( SKELETON_FILE "glfw3_skeleton.cpp" )
    #SET( SKELETON_FILE "glfw3_skeleton_2win.cpp" )
ELSEIF( GL_FRAMEWORK STREQUAL "CINDER" )
    SET( SKELETON_FILE "cinder_skeleton.cpp" )
ELSEIF( GL_FRAMEWORK STREQUAL "GLUT" )
    SET( SKELETON_FILE "glut_skeleton.cpp" )
#ELSEIF( GL_FRAMEWORK STREQUAL "PEZ" ) # handled in platform-dependent section
ENDIF()


IF( GL_FRAMEWORK STREQUAL "PEZ" OR GL_FRAMEWORK STREQUAL "CINDER" )
    ADD_EXECUTABLE( ${PROJECT_NAME} WIN32 src/${SKELETON_FILE} )
ELSE()
    ADD_EXECUTABLE( ${PROJECT_NAME} src/${SKELETON_FILE} )
ENDIF()

TARGET_LINK_LIBRARIES( ${PROJECT_NAME}
    PROJ_LIBS
    ${PLATFORM_LIBS}
)
