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
     * @return the type of the next piece that will be spawned.
     */
    [[nodiscard]] square next() const noexcept
    { return rng_.next(); }

    /**
     * @return the contents of the game board.
     */
    [[nodiscard]] constexpr const board_t &board() const noexcept
    { return board_; }
    
    /** 
     * @return the current state of the game.
     */
    [[nodiscard]] constexpr const state_t &state() const noexcept
    { return state_; }

    /** 
     * @return //TODO: comments 
     */
    [[nodiscard]] constexpr const uint8_t &frame_num() const noexcept
    { return frame_num_; }

    /**
     * @brief whether or not the rendering of the board requires a update.
     */
    [[nodiscard]] constexpr bool update() const noexcept
    { return update_board_; }

    /**
     * @brief upon update, reset the update board flag.
     */
    void update(bool) noexcept
    { update_board_ = false; }

    /** 
     * @return a const reference to the active piece.
     */
    [[nodiscard]] constexpr const piece &active_piece() const noexcept
    { return active_piece_; }

    /** 
     * @return a const reference to the level counter.
     */
    [[nodiscard]] constexpr const level_counter &level() const noexcept
    { return level_; }

    /** 
     * @return a const reference to the clock.
     */
    [[nodiscard]] constexpr const uint32_t &clk() const noexcept 
    { return clk_; }

    /**
     * @return a const reference to the current score.
     */
    [[nodiscard]] constexpr const uint32_t &score() const noexcept
    { return score_; }
    
    /** 
     * @return a const reference to the current grade.
     */
    [[nodiscard]] constexpr const uint8_t &grade() const noexcept
    { return grade_; }

private:
    /**
     * @brief Some of the main delays present in the TGM game.
     */
    static constexpr uint32_t ARE = 26, LOCK = 30, CLEAR = 41, FLASH = 3;

    /**
     * @brief The board that store the pieces that are already locked.
     */
    board_t board_{};

    /**
     * @brief Random number generator to generate the pieces.
     */
    randomizer rng_{};

    /**
     * @brief The inputs to the game provided by the user on every frame.
     */
    inputs keys_;

    /**
     * @brief The level counter.
     */
    level_counter level_{};

    /**
     * @brief The clock object.
     * @details starts counting at the beginning of the game once per frame, 
     * and ends when the player reaches level 999 or the game is over.
     */
    uint32_t clk_{0};

    /**
     * @brief The score.
     */
    uint32_t score_{0};
    
    /**
     * @brief The combo. 
     * @details Locking a piece without clearing lines resets Combo to 1. 
     * Otherwise, the game updates Combo as follows, before calculating Score.
     */
    uint32_t combo_{1};

    /**
     * @brief The number of lines the current piece was soft dropped.
     */
    uint32_t dropped_{0};

    /**
     * @brief The internal grade value (from 0 to 18, with 18 being Grand Master).
     */
    uint8_t grade_{0};

    // TODO: comments
    uint8_t frame_num_{0};
    state_t state_{state_t::spawn};
    piece active_piece_;
    bool line_clear_{false};
    bool update_board_{false};
    bool game_over_{false};
    bool GM_possible{true};
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

