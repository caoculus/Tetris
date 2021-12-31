#pragma once

#include "mesh.hpp"
#include "game/level.hpp"

class bkgd : public mesh
{
public:
    bkgd(sampler &__sampler, level_counter &level);

    void draw() const override;

private:
    static constexpr std::array<unsigned int, 6> indices_ = {
        0, 1, 2,
        1, 2, 3
    };

    std::array<float, 16> vertices_;

    level_counter level_;
};