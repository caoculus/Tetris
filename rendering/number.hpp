#pragma once

#include <GL/glew.h>
#include "mesh.hpp"
#include "game/level.hpp"

namespace mesh
{
template <std::size_t DIGITS>
void update_number(quad_vertices<DIGITS> &vertices, const sampler &s, const int number, 
                   int x_max, int y_min, 
                   int spacing=1, int digit_width=7, int digit_height=10, float e_width=320.f, float e_height=240.f)
{
    uint32_t unit = 1, base = 10;

    const float Py = 1.f - (2*y_min/e_height);
    const float Ny = 1.f - (2*(y_min+digit_height)/e_height);
    float Px = (2*x_max/e_width) - 1.f;
    float Nx = (2*(x_max-digit_width)/e_width) - 1.f;

    const float step = 2*(digit_width + spacing) / e_width;

    for (std::size_t i = 0; i < DIGITS; ++i)
    {
        const bool leading_zero = number < unit and i;
        const auto &coords = s("number", leading_zero ? 10 : (number % base / unit));
        vertices[16*i+0] = Nx;
        vertices[16*i+1] = Ny;
        vertices[16*i+2] = coords.Nx;
        vertices[16*i+3] = coords.Ny;
        vertices[16*i+4] = Nx;
        vertices[16*i+5] = Py;
        vertices[16*i+6] = coords.Nx;
        vertices[16*i+7] = coords.Py;
        vertices[16*i+8] = Px;
        vertices[16*i+9] = Ny;
        vertices[16*i+10] = coords.Px;
        vertices[16*i+11] = coords.Ny;
        vertices[16*i+12] = Px;
        vertices[16*i+13] = Py;
        vertices[16*i+14] = coords.Px;
        vertices[16*i+15] = coords.Py;

        unit *= 10;
        base *= 10;
        Px -= step;
        Nx -= step;
    }
}

/**
 * @brief Class for the mesh of all numbers used in the game.
 * 
 * @details The numbers are rendered using a single mesh. Each digit is a 
 * quadrilateral using the different numbers as textures. The clock and level
 * are currently displayed in their respective places.
 */
class number : public mesh
{
public:
    number(sampler &s, const game::level_counter &level, const uint32_t &clk, const uint32_t &score, const uint8_t &grade);

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
    int intern_numer_{-5}, intern_denom_{-7}, intern_score_{-8}, intern_grade_{-3};

    /**
     * @brief The hundreds, tens, and ones digit for the level.
     */
    int n_hundreds_ {}, n_tens_ {}, n_ones_ {};

    /**
     * @brief Reference to the clock, used to display the clock.
     */
    const uint32_t &clk_;
    
    /**
     * @brief Reference to the score, used to display the score.
     */
    const uint32_t &score_;

    /**
     * @brief Reference to the grade, used to display the grade and the points
     * to the next grade.
     */
    const uint8_t &grade_;

    /**
     * @brief The vertices for the 6 quads to draw the clock.
     */
    quad_vertices<6> clk_vertices_;

    /**
     * @brief The vertices for the 3 quads to draw the numerator and denominator
     * of the level 
     */
    quad_vertices<3> numer_, denom_;

    quad_vertices<6> score_vertices_, next_grade_vertices_;

    quad_vertices<1> sprite_vertices_;
    
    /**
     * @brief The indices for the 12 quads (for now) to draw.
     */
    static constexpr quad_indices<25> INDICES {};

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
     * when the background changes).
     */
    void update_denom();

    void update_score();

    void update_grade();
};

}
