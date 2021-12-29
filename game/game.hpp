#pragma once

#include "common.hpp"

class tetris
{

public:
    tetris();

    ~tetris();

    void tick();

private:
    board_t board;
    uint32_t clock;
};