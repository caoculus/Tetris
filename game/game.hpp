#pragma once

#include "common.hpp"
#include "randomizer.hpp"
#include "piece.hpp"
#include "level.hpp"

class tetris
{

public:
    tetris(GLFWwindow *window) : keys_(window),
                                 active_piece_(rng_.next(), board_)
    {}

    void tick();

    [[nodiscard]] int time() const noexcept;

    [[nodiscard]] square next() const noexcept;

    [[nodiscard]] const board_t &b() const noexcept;

private:
    static constexpr int ARE = 30, LOCK = 30, CLEAR = 41;
    board_t board_{};
    randomizer rng_{};
    inputs keys_;
    level_counter level_{};
    int clk_{}, state_{-13}, lock_{LOCK};
    piece active_piece_;

    void update_counters(bool line_clear = false, bool fall_1 = false,
                         bool land = false);
};
