#pragma once

#include "sampler.hpp"
#include "game/common.hpp"
#include "mesh.hpp"
#include <vector>

namespace mesh
{

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
    std::vector <float> vertices_;
    std::vector <unsigned int> indices_;
    const board_t &board_;
};

}