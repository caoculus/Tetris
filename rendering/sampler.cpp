#include "sampler.hpp"

#define cimg_display 0
#define cimg_use_png 1

#include <GL/glew.h>
#include <CImg.h>
#include <vector>

sampler::sampler(const std::string &_global_texture_atlas_path)
{
    cimg_library::CImg<uint8_t> _tex(_global_texture_atlas_path.c_str());
    
    if (_tex.spectrum() != 4)
        throw std::runtime_error("Texture atlas must be RGBA");
    if (_tex.width() != TEX_WIDTH)
        throw std::runtime_error("Texture atlas width is incorrect");
    if (_tex.height() != TEX_HEIGHT)
        throw std::runtime_error("Texture atlas height is incorrect");
    
    constexpr std::size_t TEX_SIZE = TEX_WIDTH * TEX_HEIGHT * 4;
    std::vector<uint8_t> tex (TEX_SIZE, 0);

#pragma omp parallel for 
    for (int x = 0; x < TEX_WIDTH; x++)
        for (int y = 0; y < TEX_HEIGHT; y++)
            for (int c = 0; c < 4; c++)
                tex[(y * TEX_WIDTH + x) * 4 + c] = _tex(x, y, 0, c);
    
    glGenTextures(1, &id_);
    glBindTexture(GL_TEXTURE_2D, id_);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, _tex.width(), _tex.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, tex.data());
    glBindTexture(GL_TEXTURE_2D, 0);
}

sampler::~sampler()
{
    glDeleteTextures(1, &id_);
}

void sampler::bind(unsigned int slot)
{
    glActiveTexture(GL_TEXTURE0 + slot);
    glBindTexture(GL_TEXTURE_2D, id_);
}

void sampler::unbind()
{
    glBindTexture(GL_TEXTURE_2D, 0);
}
