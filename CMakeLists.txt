cmake_minimum_required(VERSION 3.22)
project(Tetris)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++2a -fopenmp")
set(OpenGlLinkers -lglfw -lpthread -lm -lz -lGL -lX11 -lXfixes -ldl -lGLEW)
set(CMAKE_BUILD_TYPE Debug)

find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)

include_directories(${OPENGL_INCLUDE_DIR} ${GLFW_INCLUDE_DIRS})

include_directories(.)

add_executable(Tetris tests/game_level.cxx game/common.cpp game/game.cpp game/level.cpp game/piece.cpp game/randomizer.cpp)

target_link_libraries(${PROJECT_NAME} ${OPENGL_gl_LIBRARY} ${OpenGlLinkers})
