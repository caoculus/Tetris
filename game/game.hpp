#pragma once

#include "common.hpp"
#include "randomizer.hpp"
#include "piece.hpp"
#include "level.hpp"

class tetris
{

public:
    explicit tetris(GLFWwindow *window) : keys_(window),
                                 active_piece_(board_)
    {}

    void tick();

    [[nodiscard]] int time() const noexcept;

    [[nodiscard]] square next() const noexcept;

    [[nodiscard]] const board_t &board() const noexcept;

private:
    static constexpr int ARE = 30, LOCK = 30, CLEAR = 41, FLASH = 3;
    board_t board_{};
    randomizer rng_{};
    inputs keys_;
    level_counter level_{};
    int clk_{0}, state_{0}, lock_{LOCK};
    bool line_clear_{false};
    piece active_piece_;

    void wait_delay();

    void drop_lines();

    void spawn_piece();

    void move_piece();

    void draw_piece();

    void clear_lines();
};

class game_over_exception : public std::exception
{
    [[nodiscard]] constexpr const char * what() const noexcept override
    {
        return "Game Over";
    }
};