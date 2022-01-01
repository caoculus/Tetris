#pragma once
#include "mesh.hpp"
#include "sampler.hpp"
#include "game/piece.hpp"

namespace mesh {

class active : public mesh
{
public:
    active(sampler &sampler, const game::piece &active_piece);

    void draw() override;

private:
    std::array<float, 64> p_vertices_, s_vertices_;
    std::array<unsigned int, 24> p_indices_, s_indices_;
    const game::piece &active_piece_;

    void update();
};

}
