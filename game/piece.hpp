#pragma once

#include "common.hpp"

namespace game
{
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

    /**
     * @param sq the type of the piece.
     *
     * @pre sq must be a type corresponding to a real piece (not shadow or line clear).
     *
     * @return the index of an array for only non-empty pieces (i.e. the LUT)
     * corresponding to a given square type.
     */
    static std::size_t index(square sq);

public:
    piece(const board_t &board) : board_(board)
    {}

    /**
     * @brief reset the properties of the piece to represent a new piece that
     * has just spawned on the board.
     *
     * @param type the type of new piece that has just spawned.
     *
     * @return true if the piece is successfully spawned without collision,
     * false otherwise.
     */
    bool spawn(square type, rotation_t rotation);

    /**
     * @brief Process one tick of the piece with one frame.
     * @requires the piece to be in a valid position on the board before the
     * tick and that the piece is a type corresponding to a real piece (not
     * shadow or line clear).
     *
     * @param g the gravity value divided by 128.
     *
     * @return true if the piece would land, false otherwise.
     */
    locking_state tick(uint16_t g);

    /**
     * @brief Translate the piece horizontally unless it collides with another
     * piece or the edge of the board.
     * @requires the piece to be in a valid position on the board before the
     *
     * @param shift the direction to shift. If the direction is none or down, do
     * nothing.
     *
     * @return true if the piece is moved, false if the piece cannot make a
     * valid move.
     */
    bool translate(shift_t shift);

    /**
     * @brief Rotate the piece according to Arika Rotation System.
     *
     * @param rotation the direction to rotate. If the direction is none, do
     * nothing.
     *
     * @return true if the rotation was successful (always true if the
     * rotation is none), false otherwise.
     */
    bool rotate(rotation_t rotation);

    /**
     * @return the positions of the four squares of the piece.
     */
    [[nodiscard]] std::array<ivec2, 4> piece_squares() const;


    /**
     * @details The shadow appears where the piece would land if it is moved
     * down until it collides with another piece or the edge of the board. The
     * shadow is only drawn up to level 100.
     *
     * @return the positions of the four squares of the shadow of this piece
     */
    [[nodiscard]] std::array<ivec2, 4> shadow_squares() const;

    [[nodiscard]] constexpr square type() const
    { return type_; };
private:
    uint8_t orientation_{0};
    uint8_t subpixel_{0};
    ivec2 pos_{0, 3};
    square type_{square::none};
    const board_t &board_;

    /**
     * @brief Check if this piece would collide after shifting it in the given direction.
     *
     * @param pos the position of the piece.
     * @param shift direction to shift the piece, or none for no shift
     * @return true if the piece would collide, false otherwise.
     */
    [[nodiscard]] bool collide(ivec2 pos, shift_t shift) const;

    /**
     * @brief Check if this piece can be rotated, according to TGM middle column
     * rules for J, L, and T pieces.
     * @requires the type of this piece is J, L, or T
     *
     * @return true if the piece can be rotated, false otherwise.
     */
    bool can_rotate_jlt();

    /**
     * @param pos the position of the piece
     * @return the positions of the four squares of this piece type if the
     * piece's position is piece_pos.
     */
    [[nodiscard]] std::array<ivec2, 4> squares(ivec2 pos) const;

    /**
     * @return the position of the shadow of the piece.
     */
    [[nodiscard]] ivec2 shadow_position() const;
};
}
