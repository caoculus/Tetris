#pragma once

#include "sampler.hpp"
#include "game/common.hpp"
#include "mesh.hpp"
#include <vector>

namespace mesh
{
    
/**
 * @brief The mesh for the pieces on the board.
 * 
 * @note Only the pieces are drawn. The blank squares are neither buffered nor
 * drawn.
 */
class board : public mesh
{
public:
    board(sampler &sampler, const board_t &board);

    void draw() override;

    /**
     * @brief Update the drawn board in the vertex and index buffer objects to
     * the current board held in board_;
     * 
     * @warning This function rebuffers a large amount of data, hence, it should
     * only be called when the board has actually changed.
     */
    void update();

private:
    /**
     * @brief The vertices for each piece on the board.
     */
    std::vector <float> vertices_;

    /**
     * @brief The indices for each piece on the board.
     */
    std::vector <unsigned int> indices_;

    /**
     * @brief The board holding the pieces.
     */
    const board_t &board_;
};

}