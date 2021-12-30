#pragma once

#include <array>
#include <string>
#include "math.hpp"
#include <cstdint>

class sampler
{
public:
    sampler(const std::string &_global_texture_atlas_path);

    ~sampler();

    void bind(unsigned int slot = 0);

    void unbind();

    static constexpr std::array<vec2<float>, 10> BKGD_TOP_LEFT = {{
        {0.0f, 0.0f}
    }};

    static constexpr std::array<vec2<float>, 10> BKGD_BOT_RIGHT = {{
        {1.0f, 1.0f}
    }};

    static constexpr std::array<vec2<float>, 17> PIECE_TOP_LEFT = {{

    }};

    static constexpr std::array<vec2<float>, 17> PIECE_BOT_RIGHT = {{

    }};

    static constexpr vec2<float> FRAME_TOP_LEFT = {};
    static constexpr vec2<float> FRAME_BOT_RIGHT = {};

    static constexpr std::array<vec2<float>, 10> NUMBERS_TOP_LEFT = {{

    }};

    static constexpr std::array<vec2<float>, 10> NUMBERS_BOT_RIGHT = {{

    }};

private:
    unsigned int id_;
};