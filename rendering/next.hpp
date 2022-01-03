#pragma once

#include "mesh.hpp"
#include "game/common.hpp"

namespace mesh
{
class next : public mesh
{
public:
    next(sampler &sampler, const square &init);

    void draw() override;

    void update(const square &next);

private:
    quad_vertices<1> vertices_;
    std::size_t sq_;
};

}
