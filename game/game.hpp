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
    
    static constexpr int ARE = 30, LOCK = 30, CLEAR = 41;
    
    int clk{}, state{-13}, lock{LOCK};
    void update_counters(bool line_clear=false, bool fall1=false, bool land=false);
    
};
