#pragma once

#include <array>
#include <string>
#include "math.hpp"
#include <cstdint>

class sampler
{
private:
    struct tex_rect
    {
        float Nx, Py, Px, Ny;
    };

    unsigned int id_;
public:
    sampler(const std::string &_global_texture_atlas_path);

    ~sampler();

    void bind(unsigned int slot = 0);

    void unbind();

    static constexpr std::size_t TEX_WIDTH = 1920, TEX_HEIGHT = 6780;

private:
    static constexpr float PIECES_TOP = 5880.0f/TEX_HEIGHT;
    static constexpr float PIECE_WIDTH = 25.0f/TEX_WIDTH;
    static constexpr float PIECES_BOT = 5905.0f/TEX_HEIGHT;
public:
    static constexpr std::array<tex_rect, 10> BKGD = {{
        {0.0f, 0.0f, 1.0f, 1080.0f/TEX_HEIGHT},
        {0.0f, 1080.0f/TEX_HEIGHT, 1.0f, 2 * 1080.0f/TEX_HEIGHT},
        {0.0f, 2 * 1080.0f/TEX_HEIGHT, 1.0f, 3 * 1080.0f/TEX_HEIGHT},
        {0.0f, 3 * 1080.0f/TEX_HEIGHT, 953.0f/TEX_WIDTH, (3*1080 + 450.0f)/TEX_HEIGHT},
        {0.0f, 3700.0f/TEX_HEIGHT, 1030.0f/TEX_WIDTH, 4280.0f/TEX_HEIGHT},
        {0.0f, 4280.0f/TEX_HEIGHT, 887.0f/TEX_WIDTH, (4280.0f+512.0f)/TEX_HEIGHT},
        {0.0f, 4800.0f/TEX_HEIGHT, 960.0f/TEX_WIDTH, 5340.0f/TEX_HEIGHT},
        {0.0f, 5340.0f/TEX_HEIGHT, 960.0f/TEX_WIDTH, 5880.0f/TEX_HEIGHT},
        {1.0f - 672.0f/TEX_WIDTH, 3240.0f/TEX_HEIGHT, 1.0f, 3740.0f/TEX_HEIGHT},
        {0.0f, 5880.0f/TEX_HEIGHT, 1660.0f/TEX_WIDTH, 1.0f}
    }};

    static constexpr std::array<tex_rect, 8> PIECE = {{
        {PIECES_TOP, 1.0f-8*PIECE_WIDTH, PIECES_BOT, 1.0f-7*PIECE_WIDTH},
        {PIECES_TOP, 1.0f-7*PIECE_WIDTH, PIECES_BOT, 1.0f-6*PIECE_WIDTH},
        {PIECES_TOP, 1.0f-6*PIECE_WIDTH, PIECES_BOT, 1.0f-5*PIECE_WIDTH},
        {PIECES_TOP, 1.0f-3*PIECE_WIDTH, PIECES_BOT, 1.0f-2*PIECE_WIDTH},
        {PIECES_TOP, 1.0f-PIECE_WIDTH, PIECES_BOT, 1.0f},
        {PIECES_TOP, 1.0f-5*PIECE_WIDTH, PIECES_BOT, 1.0f-4*PIECE_WIDTH},
        {PIECES_TOP, 1.0f-2*PIECE_WIDTH, PIECES_BOT, 1.0f-PIECE_WIDTH},
        {PIECES_TOP, 1.0f-4*PIECE_WIDTH, PIECES_BOT, 1.0f-3*PIECE_WIDTH}
    }};

    static constexpr tex_rect FRAME {};

    static constexpr std::array<tex_rect, 10> NUMBER = {{

    }};

};