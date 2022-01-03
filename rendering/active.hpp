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

    static constexpr quad_indices<8> INDICES {};

    void update();
};

}
