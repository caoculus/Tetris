#pragma once

#include "common.hpp"
#include "randomizer.hpp"
#include "piece.hpp"
#include "level.hpp"

class tetris
{

public:
    tetris();

    ~tetris();

    void tick();

private:
    board_t board;
    randomizer rng;
    piece active_piece;
    level_counter level;
    uint32_t clock;
};
