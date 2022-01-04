cmake_minimum_required(VERSION 3.22)
project(Tetris)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++2a -fopenmp")
set(OpenGlLinkers -lpthread -lm -lopengl32 -lglfw3 -lglew32 -lpng -lssp)
set(CMAKE_BUILD_TYPE Debug)

include_directories(/usr/x86_64-w64-mingw32/include/)
include_directories(.)

add_executable(Tetris game/main.cxx game/common.cpp game/game.cpp game/level.cpp
        game/piece.cpp game/randomizer.cpp
        rendering/sampler.cpp rendering/shader.cpp rendering/mesh.cpp
        rendering/background.cpp rendering/frame.cpp rendering/board.cpp 
        rendering/active.cpp rendering/next.cpp rendering/number.cpp rendering/dim.cpp)

target_link_libraries(${PROJECT_NAME} ${OpenGlLinkers})
