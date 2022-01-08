#pragma once

#include <array>
#include <cstdint>
#include <GLFW/glfw3.h>

/**
 * @brief Represents a piece shift input for the game.
 */
enum class shift_t : uint8_t
{
    none, left, down, right
};

/**
 * @brief Represents a piece rotation input for the game.
 */
enum class rotation_t : uint8_t
{
    none, ccw, cw
};

/**
 * @brief Represents a locking state of a piece.
 *
 * @details <code> tick </code> is set when the lock counter for the active
 * piece should be ticked.<br> <code> reset </code> is set when the lock
 * counter for the active piece should be reset.
 */
enum class locking_state : uint8_t
{
    none = 0x0, tick = 0x1, reset = 0x2
};

/**
 * @brief Or overload for locking_state so it can be used for bit flags.
 *
 * @param a The first locking_state.
 * @param b The second locking_state.
 * @return the bitwise or of the two locking states.
 */
inline locking_state operator|(locking_state a, locking_state b)
{
    return static_cast<locking_state>(static_cast<uint8_t>(a) |
                                      static_cast<uint8_t>(b));
}


/**
 * @brief And overload for locking_state so it can be used for bit flags.
 *
 * @param a The first locking_state.
 * @param b The second locking_state.
 * @return the bitwise and of the two locking states.
 */
inline locking_state operator&(locking_state a, locking_state b)
{
    return static_cast<locking_state>(static_cast<uint8_t>(a) &
                                      static_cast<uint8_t>(b));
}

/**
 * @brief Represents the current state of the game.
 *
 * @details The meaning of each state is as follows:<br>
 * <ul>
 * <li> <code> spawn </code> - A piece will be spawned next frame. </li>
 */
enum class state_t : uint8_t
{
    spawn,  // on frame to spawn a new piece
    active, // active piece is in play
    flash,  // flash the current piece
    dim,    // end of flash, dim the current piece, no border
    are,    // other frames of ARE
    clear   // line clear
};

constexpr std::array<int, 18> GRADES {
    400, 800, 1400, 2000, 3500, 5500, 8000, 12000, 16000, 22000, 30000, 
    40000, 52000, 66000, 82000, 100000, 120000, 999999
};

class inputs
{
public:
    /**
     * @brief Construct a new inputs object by checking for the specific keys
     * the user pressed in the window during the current frame.
     */
    explicit inputs(GLFWwindow *window) : window_(window)
    {};

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
    static constexpr int K_LEFT = GLFW_KEY_LEFT;
    static constexpr int K_DOWN = GLFW_KEY_LEFT_SHIFT;
    static constexpr int K_RIGHT = GLFW_KEY_RIGHT;
    static constexpr int K_CCW_1 = GLFW_KEY_DOWN;
    static constexpr int K_CW = GLFW_KEY_UP;
    static constexpr int K_CCW_2 = GLFW_KEY_L;

    static constexpr int DAS = 15;

    shift_t prev_shift_{shift_t::none};

    bool prev_k_ccw_1_pressed_{false};
    bool prev_k_cw_pressed_{false};
    bool prev_k_ccw_2_pressed_{false};

    uint8_t das_{0};

    GLFWwindow *window_;
};

/**
 * @brief enum class representing the objects that can occupy a square in the 
 * game's board.
 * 
 */
enum class square
{
    none, I, J, L, O, S, T, Z, clear
};

/**
 * @brief Determine if the square is empty.  
 * 
 * @return bool true if the square is empty and false otherwise.
 */
constexpr bool is_empty(const square &sq)
{
    return sq == square::none;
}

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
