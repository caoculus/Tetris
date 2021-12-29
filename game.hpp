#pragma once

#include "common.hpp"
#include <stdexcept>

class tetris
{

public:
    tetris();

    ~tetris();

    void tick();

private:
    enum class locking_state {
        none, tick, reset
    };

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
         * @param left true to move left, false to move right.
         */
        void translate(bool left);

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
    };

    board_t board;
    uint32_t clock;
};