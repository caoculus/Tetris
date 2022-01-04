#pragma once

#include "mesh.hpp"
#include "game/level.hpp"

namespace mesh {

/**
 * @brief The background for the game.
 */
class bkgd : public mesh
{
public:
    bkgd(sampler &sampler, const game::level_counter &level);

    void draw() override;

private:
    /**
     * @brief The vertices for the background.
     */
    quad_vertices<1> vertices_{};

    /**
     * @brief The background changes every 100 levels.
     */
    const game::level_counter &level_;

    /**
     * @brief The section the background is currently on. There are 10.
     */
    std::size_t section_;
};

}
