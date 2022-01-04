#pragma once

#include "mesh.hpp"
#include "game/common.hpp"

namespace mesh
{
/**
 * @brief Mesh for the next piece displayed in the "NEXT" slot in the board.
 */
class next : public mesh
{
public:
    next(sampler &sampler, const square &init);

    void draw() override;

    /**
     * @brief Update the next piece to be drawn.
     * 
     * @param next The type of the next piece.
     * 
     * @note This method should be called every time the next piece changes.
     */
    void update(const square &next);

private:
    /**
     * @brief Vertices for the next piece.
     */
    quad_vertices<1> vertices_;

    /**
     * @brief The integer representing the next piece (start from 1).
     */
    std::size_t sq_;
};

}
