#pragma once

#include <GL/glew.h>
#include "mesh.hpp"
#include "game/level.hpp"

namespace mesh
{

/**
 * @brief Class for the mesh of all numbers used in the game.
 * 
 * @details The numbers are rendered using a single mesh. Each digit is a 
 * quadralateral using the different numbers as textures. The clock and level
 * are currently displayed in their respective places.
 */
class number : public mesh
{
public:
    number(sampler &s, const game::level_counter &level, const uint32_t &clk);

    void draw() override;

private:
    const game::level_counter &level_;
    int intern_numer_{-5}, intern_denom_{-7};
    int n_hundreds_ {}, n_tens_ {}, n_ones_ {};
    const uint32_t &clk_;
    quad_vertices<6> clk_vertices_;
    quad_vertices<3> numer_, denom_;
    static constexpr quad_indices<12> INDICES {};

    void update_clk();
    void update_numer();
    void update_denom();
};

}
