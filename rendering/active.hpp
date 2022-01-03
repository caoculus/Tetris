#pragma once

#include "mesh.hpp"
#include "sampler.hpp"
#include "game/piece.hpp"
#include "game/level.hpp"

namespace mesh {

class active : public mesh
{
public:
    active(sampler &sampler, const game::piece &active_piece, const game::level_counter &level, const int &state);

    void draw() override;

private:
    quad_vertices<4> p_vertices_{}, s_vertices_{};
    const game::piece &active_piece_;
    const game::level_counter &level_;
    const int &state_;

    static constexpr quad_indices<8> INDICES {
        0,   1,  2,
        1,   2,  3,
        4,   5,  6,
        5,   6,  7,
        8,   9, 10,
        9,  10, 11,
        12, 13, 14,
        13, 14, 15,
        16, 17, 18,
        17, 18, 19,
        20, 21, 22,
        21, 22, 23,
        24, 25, 26,
        25, 26, 27,
        28, 29, 30,
        29, 30, 31
    };

    void update();
};

}
