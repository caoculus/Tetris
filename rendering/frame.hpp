#pragma once

#include "mesh.hpp"
#include <GLFW/glfw3.h>

namespace mesh {

class frame : public mesh
{
public:
    frame(sampler &sampler, const GLFWvidmode *mode);

    void draw() override;
    
private:
    std::array<float, 16> vertices_;
};

}
