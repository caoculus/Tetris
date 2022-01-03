#pragma once

#include <GL/glew.h>
#include "mesh.hpp"
#include "game/level.hpp"

namespace mesh
{

class number : public mesh
{
public:
    number(sampler &s, const game::level_counter &level);

    void draw() override;

private:
    const game::level_counter &level_;
    int intern_numer_{-5}, intern_denom_{-7};
    int n_hundreds {}, n_tens {}, n_ones {};
    quad_vertices<3> numer_, denom_;
    static constexpr quad_indices<6> N_INDICES {};
};

}
