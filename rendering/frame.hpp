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
    static constexpr std::array<unsigned int, 6> indices_ = {
        0, 1, 2,
        1, 2, 3
    };

    std::array<float, 16> vertices_;
};

}
