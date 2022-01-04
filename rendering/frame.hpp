#pragma once

#include "mesh.hpp"

namespace mesh {

/**
 * @brief The frame of the TGM game that includes the pipe for the level and
 * colons for the timer.
 */
class frame : public mesh
{
public:
    explicit frame(sampler &sampler);

    void draw() override;
};

}
