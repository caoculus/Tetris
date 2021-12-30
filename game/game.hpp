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
    board_t board_;
    randomizer rng_;
    piece active_piece_;
    level_counter level_;
    inputs keys_;
    
    static constexpr int ARE = 30, LOCK = 30, CLEAR = 41;
    
    int clk_{}, state_{-13}, lock_{LOCK};
    void update_counters(bool line_clear=false, bool fall_1=false, bool land=false);
    
};
