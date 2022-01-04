#pragma once

#define GLEW_STATIC
#include <GL/glew.h>
#include "active.hpp"
#include "background.hpp"
#include "board.hpp"
#include "dim.hpp"
#include "frame.hpp"
#include "mesh.hpp"
#include "next.hpp"
#include "number.hpp"
#include "sampler.hpp"
#include "shader.hpp"


#if(RENDERING_ENGINE==1)
#define OPENGL_VERSION 4
#define OPENGL_SUBVERSION 5
#define EMULATED_WIDTH 320
#define EMULATED_HEIGHT 240
#define DEFAULT_SAMPLER_PATH "assets/texatlas.png"
#endif