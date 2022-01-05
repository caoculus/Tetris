cmake_minimum_required(VERSION 3.22)
project(Tetris)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++2a -fopenmp -static")
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_FIND_LIBRARY_SUFFIXES .a)

include_directories(/usr/x86_64-w64-mingw32/include/)
include_directories(.)

find_library(LIBOPENGL NAMES libopengl32.a PATHS /usr/x86_64-w64-mingw32/lib/)
find_library(LIBGLFW NAMES libglfw3.a PATHS /usr/x86_64-w64-mingw32/lib/)
find_library(LIBGLEW NAMES libglew32.dll.a PATHS /usr/x86_64-w64-mingw32/lib/)
find_library(LIBPNG NAMES libpng.a PATHS /usr/x86_64-w64-mingw32/lib/)
find_library(LIBSSP NAMES libssp.a PATHS /usr/x86_64-w64-mingw32/lib/)
find_library(LIBZ NAMES libz.a PATHS /usr/x86_64-w64-mingw32/lib/)

add_executable(Tetris game/main.cxx game/common.cpp game/game.cpp game/level.cpp
        game/piece.cpp game/randomizer.cpp
        rendering/sampler.cpp rendering/shader.cpp rendering/mesh.cpp
        rendering/background.cpp rendering/frame.cpp rendering/board.cpp 
        rendering/active.cpp rendering/next.cpp rendering/number.cpp rendering/dim.cpp)

#target_link_libraries(${PROJECT_NAME} ${OpenGlLinkers})
target_link_libraries(${PROJECT_NAME} ${LIBOPENGL} ${LIBGLFW} ${LIBGLEW} ${LIBPNG} ${LIBSSP} ${LIBZ})
