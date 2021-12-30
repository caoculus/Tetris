#pragma once

#include "common.hpp"

class piece
{
public:
    static constexpr ivec2 LUT[7][4][4] = {
        // I piece
        {
            {{1, 0}, {1, 1}, {1, 2}, {1, 3}},
            {{0, 2}, {1, 2}, {2, 2}, {3, 2}},
            {{1, 0}, {1, 1}, {1, 2}, {1, 3}},
            {{0, 2}, {1, 2}, {2, 2}, {3, 2}},
        },
        // J piece
        {
            {{1, 0}, {1, 1}, {1, 2}, {2, 2}},
            {{0, 1}, {0, 2}, {1, 1}, {2, 1}},
            {{1, 0}, {2, 0}, {2, 1}, {2, 2}},
            {{0, 1}, {1, 1}, {2, 0}, {2, 1}},
        },
        // L piece
        {
            {{1, 0}, {1, 1}, {1, 2}, {2, 0}},
            {{0, 1}, {1, 1}, {2, 1}, {2, 2}},
            {{1, 2}, {2, 0}, {2, 1}, {2, 2}},
            {{0, 0}, {0, 1}, {1, 1}, {2, 1}},
        },
        // O piece
        {
            {{1, 1}, {1, 2}, {2, 1}, {2, 2}},
            {{1, 1}, {1, 2}, {2, 1}, {2, 2}},
            {{1, 1}, {1, 2}, {2, 1}, {2, 2}},
            {{1, 1}, {1, 2}, {2, 1}, {2, 2}},
        },
        // S piece
        {
            {{1, 1}, {1, 2}, {2, 0}, {2, 1}},
            {{0, 0}, {1, 0}, {1, 1}, {2, 1}},
            {{1, 1}, {1, 2}, {2, 0}, {2, 1}},
            {{0, 0}, {1, 0}, {1, 1}, {2, 1}},
        },
        // T piece
        {
            {{1, 0}, {1, 1}, {1, 2}, {2, 1}},
            {{0, 1}, {1, 1}, {1, 2}, {2, 1}},
            {{1, 1}, {2, 0}, {2, 1}, {2, 2}},
            {{0, 1}, {1, 0}, {1, 1}, {2, 1}},
        },
        // Z piece
        {
            {{1, 0}, {1, 1}, {2, 1}, {2, 2}},
            {{0, 2}, {1, 1}, {1, 2}, {2, 1}},
            {{1, 0}, {1, 1}, {2, 1}, {2, 2}},
            {{0, 2}, {1, 1}, {1, 2}, {2, 1}},
        },
    };

    static std::size_t index(square sq);

public:
    piece(square _type, const board_t &_board) : type(_type), board(_board)
    {}

    /**
     * @brief Process one tick of the piece with one frame. 
     * @requires the piece to be in a valid position on the board before the
     * tick
     * 
     * @param g the gravity value divided by 128.
     * 
     * @return true if the piece would land, false otherwise. 
     */
    locking_state tick(uint16_t g);

    /**
     * @brief Translate the piece horizontally, and does nothing if the 
     * piece is already at the edge of the board.
     * @requires the piece to be in a valid position on the board before the
     * 
     * @param shift the direction to shift. If the direction is none, do nothing.
     */
    bool translate(shift_t shift);

    /**
     * @brief 
     * 
     * @param left 
     */
    void rotate(bool left);

private:
    uint8_t orientation{0};
    uint8_t subpixel{0};
    const square type;
    ivec2 pos{0, 3};
    const board_t &board;

    /**
     * @brief Check if this piece would collide after shifting it in the given direction.
     *
     * @param shift direction to shift the piece, or none for no shift
     * @return true if the piece would collide, false otherwise.
     */
    bool collide(ivec2 old_pos, shift_t shift);

    /**
     * @brief Check if this piece can be rotated, according to TGM middle column
     * rules for J, L, and T pieces.
     * @requires the type of this piece is J, L, or T
     *
     * @return true if the piece can be rotated, false otherwise.
     */
    bool can_rotate_jlt();
};
