#pragma once

#include "mesh.hpp"
#include "sampler.hpp"
#include "game/piece.hpp"
#include "game/level.hpp"

namespace mesh
{

/**
 * @brief The mesh to draw the active piece.
 */
class active : public mesh
{
public:
    active(sampler &sampler, const game::piece &active_piece,
           const game::level_counter &level, const state_t &state,
           const uint8_t &frame_num);

    void draw() override;
private:

    /**
     * @brief Vertices for the active piece and the shadow.
     */
    quad_vertices<4> p_vertices_{}, s_vertices_{};

    /**
     * @brief Reference to the active piece and the shadow.
     */
    const game::piece &active_piece_;

    /**
     * @brief Reference to the level counter.
     * @details If the level counter is greater or equal to 100, the shadow is
     * no longer rendered.
     */
    const game::level_counter &level_;

    /**
     * @brief State of the game.
     * @details If the state is not the active state, the active piece is not
     * rendered.
     */
    const state_t &state_;

    /**
     * @brief Frame number of the current state used to determine the brightness
     * of the active piece.
     */
    const uint8_t &frame_num_;

    /**
     * @brief Indices for 8 quads.
     */
    static constexpr quad_indices<8> INDICES {};

    /**
     * @brief Update the vertex buffer to reflect where the active piece is in
     * the current state.
     */
    void update();
};

}
