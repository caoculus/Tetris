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
    board(sampler &sampler, board_t &board);

    void draw() override;

    void update();

private:
    std::vector <float> vertices_;
    std::vector <unsigned int> indices_;
    board_t &board_;
};

}