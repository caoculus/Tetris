#include "game.hpp"

std::size_t tetris::piece::index(square type)
{
    if (type == square::none)
        throw std::invalid_argument("square::none cannot be indexed as there is no piece there");
    return static_cast<std::size_t>(type) - 1;

}

bool tetris::piece::tick(uint16_t g)
{
    constexpr int DENOM = 128;
    int final_y = pos.y + (g / DENOM);
    if (g < DENOM)
    {
        subpixel += g;
        if (subpixel >= DENOM)
        {
            final_y++;
            subpixel -= DENOM;
        }
    }
    else 
        subpixel = 0;

    for (; pos.y <= final_y; pos.y++)
    {
        for (int sq = 0; sq < 4; sq++)
        {
            const ivec2 offset = LUT[index(type)][orientation][sq];
            const ivec2 square_pos = pos + offset;
            if (square_pos.y >= board.size() or 
                !is_empty(board[square_pos.y][square_pos.x]))
                return true;
        }
    }
    return false;
}

void tetris::piece::translate(bool left)
{
    int move = left ? -1 : 1;
    for (int sq = 0; sq < 4; sq++)
    {
        const ivec2 offset = LUT[index(type)][orientation][sq];
        const ivec2 square_pos = pos + offset;
        int new_x = square_pos.x + move;
        if (new_x < 0 or new_x >= board.size() or 
            !is_empty(board[square_pos.y][new_x]))
            return;
    }

    pos.x += move;
}

