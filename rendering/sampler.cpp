#include "sampler.hpp"

#define cimg_display 0
#define cimg_use_png 1

#include <GL/glew.h>
#include <CImg.h>
#include <vector>

sampler::sampler(const std::string &_texture_atlas_path)
{
    std::size_t last_dot = _texture_atlas_path.find_last_of('.');
    if (_texture_atlas_path.substr(last_dot) != ".png")
        throw std::runtime_error("sampler::sampler: texture atlas must be a .png file");
    
    std::string atlas_layout_path = _texture_atlas_path.substr(0, last_dot) + ".layout";
    load_atlas(atlas_layout_path);
    load_texture(_texture_atlas_path);
}

void sampler::load_atlas(const std::string &_atlas_layout_path)
{
    std::ifstream atlas_layout(_atlas_layout_path);
    if (!atlas_layout.is_open())
        throw std::runtime_error("sampler::sampler: failed to open atlas layout file");
    
    std::string line;
    std::getline(atlas_layout, line);
    std::stringstream ss(line);
    ss >> width_ >> height_;
    if (ss.fail())
        throw std::runtime_error("failed to read width and height");

    while (std::getline(atlas_layout, line))
    {
        if (line.empty())
            continue;

        std::string name;
        std::size_t num, i;
        std::stringstream(line) >> name >> num;
        if (ss.fail())
            throw std::runtime_error("sampler::sampler: failed to parse atlas layout file");
        
        std::vector<tex_rect> elems;
        elems.reserve(num);

        for (i = 0; i < num and std::getline(atlas_layout, line); i++)
        {
            int x1, y1, x2, y2;
            std::stringstream(line) >> x1 >> y1 >> x2 >> y2;
            if (ss.fail())
                throw std::runtime_error("sampler::sampler: failed to parse atlas layout file");

            elems.push_back(tex_rect{
                static_cast<float>(x1 + width_*(x1<0)) / width_,
                static_cast<float>(y1 + height_*(y1<0)) / height_,
                static_cast<float>(x2 + width_*(x2<0)) / width_,
                static_cast<float>(y2 + height_*(y2<0)) / height_
            });
        }

        locs_[name] = std::move(elems);
    }

}

void sampler::load_texture(const std::string &_texture_atlas_path)
{
    cimg_library::CImg<uint8_t> _tex(_texture_atlas_path.c_str());
    
    if (_tex.spectrum() != 4)
        throw std::runtime_error("Texture atlas must be RGBA");
    if (_tex.width() != width_)
        throw std::runtime_error("Texture atlas width is incorrect");
    if (_tex.height() != height_)
        throw std::runtime_error("Texture atlas height is incorrect");
    
    std::vector<uint8_t> tex (width_ * height_ * 4, 0);

#pragma omp parallel for 
    for (int x = 0; x < width_; x++)
        for (int y = 0; y < height_; y++)
            for (int c = 0; c < 4; c++)
                tex[(y * width_ + x) * 4 + c] = _tex(x, y, 0, c);
    
    glGenTextures(1, &id_);
    glBindTexture(GL_TEXTURE_2D, id_);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width_, height_, 0, GL_RGBA, GL_UNSIGNED_BYTE, tex.data());
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

sampler::tex_rect sampler::operator() (const std::string &thing, std::size_t index) const
{
    return locs_.at(thing)[index];
}
