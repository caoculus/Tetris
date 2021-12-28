#pragma once

#include <array>
#include <cstdint>
#include <GLFW/glfw3.h>


class inputs
{
public:
    const bool left, down, right, ccw1, cw, ccw2;

    /**
     * @brief Construct a new inputs object by checking for the specific keys
     * the user pressed in the window during the current frame. 
     */
    inputs(GLFWwindow *);

    /**
     * @brief Get the deltas of user inputs between two frames.
     * 
     * @param other the inputs of the previous frame. 
     * @return inputs the key down events during this frame.
     */
    inputs operator-(const inputs &other) const;

private:
    static constexpr int K_LEFT = GLFW_KEY_A;
    static constexpr int K_DOWN = GLFW_KEY_S;
    static constexpr int K_RIGHT = GLFW_KEY_D;
    static constexpr int K_CCW1 = GLFW_KEY_J;
    static constexpr int K_CW = GLFW_KEY_K;
    static constexpr int K_CCW2 = GLFW_KEY_L;
};

/**
 * @brief enum class representing the objects that can occupy a square in the 
 * game's board.
 * 
 */
enum class square
{
    none, i, j, l, o, s, t, z, I, J, L, O, S, T, Z
};

/**
 * @brief Determine if the square is empty.  
 * 
 * @return bool true if the square is empty and false otherwise.
 */
bool is_empty(const square &);

/**
 * @brief Board should be indexed as [row][column].
 * 
 * @warning The zero-th row is the top row, and it is not really a part of the 
 * game. 
 */
using board_t = std::array<std::array<square, 10>, 21>;

/**
 * @brief A pair of two integers that can represent the position of a piece on the board.
 */
class ivec2
{
public:
    int y, x;

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

    bool operator==(const ivec2 &other) const
    {
        return y == other.y && x == other.x;
    }

    bool operator!=(const ivec2 &other) const
    {
        return !(*this == other);
    }
};

