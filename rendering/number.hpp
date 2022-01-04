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
    /**
     * @brief The level counter, which are numbers that are displayed in the
     * level section.
     */
    const game::level_counter &level_;

    /**
     * @brief The internal numbers, kept so that the level counter only updates
     * when it has to and not on every frame. 
     */
    int intern_numer_{-5}, intern_denom_{-7};

    /**
     * @brief The hundreds, tens, and ones digit for the level.
     */
    int n_hundreds_ {}, n_tens_ {}, n_ones_ {};

    /**
     * @brief Reference to the clock, used to display the clock.
     */
    const uint32_t &clk_;

    /**
     * @brief The vertices for the 6 quads to draw the clock.
     */
    quad_vertices<6> clk_vertices_;

    /**
     * @brief The vertices for the 3 quads to draw the numerator and denominator
     * of the level 
     */
    quad_vertices<3> numer_, denom_;

    /**
     * @brief The indices for the 12 quads (for now) to draw.
     */
    static constexpr quad_indices<12> INDICES {};

    /**
     * @brief Update the clock that is rendered on the screen.
     * @note This function is called every frame.
     */
    void update_clk();

    /**
     * @brief Update the level that is rendered on the screen.
     * @note This function should only be called when the level changes.
     */
    void update_numer();

    /**
     * @brief Update the denominator (which is tied with the section) that is
     * rendered on the screen.
     * @note This function should only be called when the section changes (i.e.
     * when the backgroud changes).
     */
    void update_denom();
};

}
