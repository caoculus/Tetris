#pragma once

#include "mesh.hpp"
#include "game/level.hpp"

namespace mesh {

class bkgd : public mesh
{
public:
    bkgd(sampler &sampler, const game::level_counter &level);

    void draw() override;

private:
    quad_vertices<1> vertices_;

    const game::level_counter &level_;

    std::size_t section_;
};

}
