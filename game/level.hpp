#pragma once

#include "common.hpp"
#include <array>
namespace game
{
/**
 * @brief The level_counter class behaves like an integer and it is used to
 * control the level of the game based on TGM rules.
 *
 * @details The level behaves like an integer with additional features. After a
 * new piece spawns, the level is incremented using the increment operator.
 * After n lines are clear, n is added to the level.
 *
 * Note that if the level ends with 99 or 998, it can only be changed by
 * clearing lines. If the level is 999, the game is over so the level cannot be
 * changed.
 *
 * The level counter also has a g() function that returns the current g value,
 * which dictates the speed new pieces fall.
 *
 */
class level_counter
{
public:
    /**
     * @brief The denominator of the g() function.
     */
    static constexpr int DENOM = 128;

    level_counter() = default;

    level_counter(const level_counter &) = delete;
    level_counter &operator=(const level_counter &) = delete;

    /**
     * @brief update the level counter upon the spawning of a new piece.
     *
     * @details The level counter is incremented by 1 if the current level does
     * not end with 99, or is 998.
     *
     * @return reference of *this to allow chaining.
     */
    level_counter &operator++() noexcept;

    /**
     * @brief update of the level counter upon a line clear of n lines.
     *
     * @param n number of lines cleared.
     * @pre n must be between 1 and 4.
     *
     * @return reference of *this to allow chaining.
     */
    level_counter &operator+= (int n) noexcept;

    /**
     * @return the gravity value at the current level (as 128-ths of lines per 
     * frame) as an 16-bit integer.
     */
    [[nodiscard]] uint16_t g() const noexcept;

    /**
     * @return the current level.
     */
    operator int() const noexcept;

    /** 
     * @return The section the level is in. 
     * @note There are a total of 10 sections. 
     */
    [[nodiscard]] std::size_t section() const noexcept { return level_/100; }

private:
    int level_{}, step_{};

    /**
     * @brief the gravity values of the game depending on the step, (hence
     * level), as a fraction of DENOM.
     */
    static constexpr std::array<uint16_t, 30> G_STEPS {
        2, 3, 4, 5, 6, 8, 16, 24, 32, 40, 48, 56, 64, 72, 2,
        16, 32, 48, 64, 80, 96, 112, 128, 256, 384, 512, 640, 512, 384, 2560
    };

    /**
     * @brief the step of the game depending on the level.
     */
    static constexpr std::array<int, 30> LEVEL_STEPS {
        30, 35, 40, 50, 60, 70, 80, 90, 100, 120, 140, 160, 170, 200, 220, 230,
        233, 236, 239, 243, 247, 251, 300, 330, 360, 400, 420, 450, 500, 1000
    };
};
}
