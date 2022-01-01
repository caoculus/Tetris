#pragma once

#include "mesh.hpp"

namespace mesh {

class frame : public mesh
{
public:
    explicit frame(sampler &sampler);

    void draw() override;
    
private:
    std::array<float, 16> vertices_;
};

}
