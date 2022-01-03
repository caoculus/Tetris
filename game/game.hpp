#pragma once

#include "common.hpp"
#include "randomizer.hpp"
#include "piece.hpp"
#include "level.hpp"

namespace game
{
class tetris
{

public:
    /**
     * @brief Create a new instance of the tetris game.
     * @param window the window where the game will be rendered
     */
    explicit tetris(GLFWwindow *window) : keys_(window),
                                          active_piece_(board_)
    {}

    /**
     * @brief Process one tick (frame) of the game.
     * @throws game_over_exception if the game is over.
     */
    void tick();

    /**
     * @return the number of frames that have elapsed since the game started.
     */
    [[nodiscard]] constexpr uint32_t time() const noexcept
    { return clk_; }

    /**
     * @return the type of the next piece that will be spawned.
     */
    [[nodiscard]] square next() const noexcept
    { return rng_.next(); }

    /**
     * @return the contents of the game board.
     */
    [[nodiscard]] constexpr const board_t &board() const noexcept
    { return board_; }

    [[nodiscard]] constexpr const state_t &state() const noexcept
    { return state_; }

    [[nodiscard]] constexpr const uint8_t &frame_num() const noexcept
    { return frame_num_; }

    [[nodiscard]] constexpr bool update() const noexcept
    { return update_board_; }

    void update(bool) noexcept
    { update_board_ = false; }

    [[nodiscard]] constexpr piece const &active_piece() const noexcept
    { return active_piece_; }

    [[nodiscard]] constexpr const level_counter &level() const noexcept
    { return level_; }

private:
    static constexpr int ARE = 26, LOCK = 30, CLEAR = 41, FLASH = 3;
    board_t board_{};
    randomizer rng_{};
    inputs keys_;
    level_counter level_{};
    uint32_t clk_{0};
    uint8_t frame_num_{0};
    state_t state_{state_t::spawn};
    bool line_clear_{false};
    piece active_piece_;
    bool update_board_{false};

    /**
     * @brief Update the state of the game during the delay between pieces.
     */
    void wait_delay();

    /**
     * @brief Collapse the cleared lines at the end of the line clear animation.
     */
    void drop_lines();

    /**
     * @brief Attempt to spawn a new piece (with initial rotation based on the
     * user input) if possible.
     * @throws game_over_exception if the game is over
     */
    void spawn_piece();

    /**
     * @brief Translate and rotate the game piece based on the user input.
     */
    void move_piece();

    /**
     * @brief Draw the active piece onto the game board.
     */
    void draw_piece();

    /**
     * @brief Check if there are any lines that can be cleared.
     *
     * @details Sets the line_clear_ flag if there are any and fills cleared
     * rows with the type.
     */
    void clear_lines();
};

class game_over_exception : public std::exception
{
    [[nodiscard]] constexpr const char *what() const noexcept override
    {
        return "Game Over";
    }
};
}

