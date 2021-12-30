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

    [[nodiscard]] int time() const noexcept;
    [[nodiscard]] square next() const noexcept;
    [[nodiscard]] const board_t &b() const noexcept;
    
private:
    board_t board;
    randomizer rng;
    piece active_piece;
    level_counter level;
    inputs keys;
    
    
    int clk{}, das{-8}, state{-8}, lock{-8};
    void update_counters(bool line_clear=false, bool fall1=false, bool land=false);

    static constexpr int DAS = 14, ARE = 30, LOCK = 30, CLEAR = 41;
};
