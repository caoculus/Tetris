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
           const uint8_t &frame_num);

    void draw() override;

private:
    quad_vertices<4> p_vertices_{}, s_vertices_{};
    const game::piece &active_piece_;
    const game::level_counter &level_;
    const state_t &state_;
    const uint8_t &frame_num_;

    static constexpr quad_indices<8> INDICES {};

    void update();
};

}
