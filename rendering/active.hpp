#pragma once

#include "mesh.hpp"
#include "sampler.hpp"
#include "game/piece.hpp"
#include "game/level.hpp"

namespace mesh
{

class active : public mesh
{
public:
    active(sampler &sampler, const game::piece &active_piece,
           const game::level_counter &level, const state_t &state,
           const int &frame_num);

    void draw() override;

private:
    std::array<float, 64> p_vertices_{}, s_vertices_{};
    std::array<unsigned int, 24> p_indices_{}, s_indices_{};
    const game::piece &active_piece_;
    const game::level_counter &level_;
    const state_t &state_;
    const int &frame_num_;

    static constexpr std::array<unsigned int, 48> INDICES{
        0, 1, 2,
        1, 2, 3,
        4, 5, 6,
        5, 6, 7,
        8, 9, 10,
        9, 10, 11,
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
