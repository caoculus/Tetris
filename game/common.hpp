#pragma once

#include <array>
#include <cstdint>
#include <GLFW/glfw3.h>

/**
 * Represents a piece shift input for the game.
 */
enum class shift_t : uint8_t {
    none, left, down, right
};

/**
 * Represents a piece rotation input for the game.
 */
enum class rotation_t : uint8_t {
    none, ccw, cw
};

/**
 * @brief Represents a locking state of a piece.
 */
enum class locking_state : uint8_t {
    none, tick, reset
};

class inputs
{
public:
    /**
     * @brief Construct a new inputs object by checking for the specific keys
     * the user pressed in the window during the current frame.
     */
    inputs(GLFWwindow *_window) : window(_window) {};

    /**
     * @brief Get the shift input based on the keys pressed in the window.
     *
     * @return shift_t the shift input
     */
    shift_t update_shift();

    /**
     * @brief Get the rotation input based on the keys pressed in the window.
     *
     * @param spawn_frame whether the game piece spawns on this frame
     * @return rotation_t the rotation input
     */
    rotation_t update_rotation(bool spawn_frame = false);

private:
    static constexpr int K_LEFT = GLFW_KEY_A;
    static constexpr int K_DOWN = GLFW_KEY_S;
    static constexpr int K_RIGHT = GLFW_KEY_D;
    static constexpr int K_CCW1 = GLFW_KEY_J;
    static constexpr int K_CW = GLFW_KEY_K;
    static constexpr int K_CCW2 = GLFW_KEY_L;

    static constexpr int DAS = 15;

    shift_t prev_shift{shift_t::none};

    bool prev_k_ccw1_pressed{false};
    bool prev_k_cw_pressed{false};
    bool prev_k_ccw2_pressed{false};

    uint8_t das{0};

    GLFWwindow *window;
};

/**
 * @brief enum class representing the objects that can occupy a square in the 
 * game's board.
 * 
 */
enum class square
{
    none, I, J, L, O, S, T, Z, i, j, l, o, s, t, z, flash, clear
};

/**
 * @brief Determine if the square is empty.  
 * 
 * @return bool true if the square is empty and false otherwise.
 */
bool is_empty(const square &);

/**
 * @brief A row of 10 squares representing a horizontal line of the play-field. 
 * If the row is occupied, the line should clear. 
 */
using row_t = std::array<square, 10>;

/**
 * @brief Board should be indexed as [row][column].
 * 
 * @warning The zero-th row is the top row, and it is not really a part of the 
 * game. 
 */
using board_t = std::array<row_t, 21>;

/**
 * @brief A pair of two integers that can represent the position of a piece on the board.
 */
class ivec2
{
public:
    int y, x;

    ivec2() = default;

    constexpr ivec2(int y, int x) : y(y), x(x)
    {}

    ivec2 operator+(const ivec2 &other) const
    {
        return {y + other.y, x + other.x};
    }

    ivec2 operator-(const ivec2 &other) const
    {
        return {y - other.y, x - other.x};
    }

    ivec2 &operator+=(const ivec2 &other)
    {
        return (*this = *this + other);
    }

    bool operator==(const ivec2 &other) const
    {
        return y == other.y && x == other.x;
    }

    bool operator!=(const ivec2 &other) const
    {
        return !(*this == other);
    }
};

