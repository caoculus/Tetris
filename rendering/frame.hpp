#pragma once

#include "mesh.hpp"

namespace mesh {

class frame : public mesh
{
public:
    explicit frame(sampler &sampler);

    void draw() override;
    
private:
    quad_vertices<1> vertices_;
};

}
