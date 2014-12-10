cmake_minimum_required(VERSION 2.8.4)
project(Geometry)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
    Utility/package.hpp
    Utility/stb_image.h
    Utility/tAutosizeViewport.cpp
    Utility/tAutosizeViewport.hpp
    Utility/tInputEvent.hpp
    Utility/tMath.cpp
    Utility/tMath.hpp
    Utility/tMatrix.cpp
    Utility/tMatrix.hpp
    Utility/tOptional.hpp
    Utility/tProgram.cpp
    Utility/tProgram.hpp
    Utility/tRect.hpp
    Utility/tShader.cpp
    Utility/tShader.hpp
    Utility/tSingleton.hpp
    Utility/tSpriteBatch.cpp
    Utility/tSpriteBatch.hpp
    Utility/tSpriteFont.cpp
    Utility/tSpriteFont.hpp
    Utility/tSurface.cpp
    Utility/tSurface.hpp
    Utility/tTexture.cpp
    Utility/tTexture.hpp
    Utility/tVector.cpp
    Utility/tVector.hpp
    Utility/tViewport.cpp
    Utility/tViewport.hpp
    Art.cpp
    Art.hpp
    BlackHole.cpp
    BlackHole.hpp
    Bullet.cpp
    Bullet.hpp
    ColorUtil.cpp
    ColorUtil.hpp
    Enemy.cpp
    Enemy.hpp
    EnemySpawner.cpp
    EnemySpawner.hpp
    Entity.cpp
    Entity.hpp
    EntityManager.cpp
    EntityManager.hpp
    Extensions.cpp
    Extensions.hpp
    GameRoot.cpp
    GameRoot.hpp
    Grid.cpp
    Grid.hpp
    IncludeGL.hpp
    Input.cpp
    Input.hpp
    main.cpp
    MathUtil.cpp
    MathUtil.hpp
    package.h
    Particle.hpp
    ParticleManager.cpp
    ParticleManager.hpp
    ParticleState.cpp
    ParticleState.hpp
    PlayerShip.cpp
    PlayerShip.hpp
    PlayerStatus.cpp
    PlayerStatus.hpp
    SDLWrapper.cpp
    SDLWrapper.hpp
    Sound.cpp
    Sound.hpp
    TimeManager.cpp
    TimeManager.hpp
    VirtualGamepad.cpp
    VirtualGamepad.hpp)

# C++11
INCLUDE(CheckCXXCompilerFlag)
CHECK_CXX_COMPILER_FLAG("-std=c++11" COMPILER_SUPPORTS_CXX11)
CHECK_CXX_COMPILER_FLAG("-std=c++0x" COMPILER_SUPPORTS_CXX0X)
IF(COMPILER_SUPPORTS_CXX11)
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
ELSEIF(COMPILER_SUPPORTS_CXX0X)
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
ELSE()
        MESSAGE(STATUS "The compiler ${CMAKE_CXX_COMPILER} has no C++11 support. Please use a different C++ compiler.")
ENDIF()


#########################################################
# FIND GLEW
#########################################################
find_package(GLEW REQUIRED)
include_directories(${GLEW_INCLUDE_DIRS})
link_libraries(${GLEW_LIBRARIES})

#########################################################
# FIND OPENGL
#########################################################
find_package(OpenGL REQUIRED)
include_directories(${OpenGL_INCLUDE_DIRS})
link_directories(${OpenGL_LIBRARY_DIRS})
link_libraries (${OPENGL_gl_LIBRARY})
add_definitions(${OpenGL_DEFINITIONS})
if(NOT OPENGL_FOUND)
    message(ERROR " OPENGL not found!")
endif(NOT OPENGL_FOUND)

#########################################################
# FIND SDL
#########################################################
find_package(SDL REQUIRED)
include_directories(${SDL_INCLUDE_DIR})
link_libraries (
   ${SDL_LIBRARY}
   SDLmain # Sadly not included in SDL_LIBRARY variable
)

add_executable(Geometry ${SOURCE_FILES})