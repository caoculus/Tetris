#include "piece.hpp"
#include <stdexcept>

std::size_t piece::index(square type)
{
    if (type == square::none)
        throw std::invalid_argument("square::none cannot be indexed as there is no piece there");
    return static_cast<std::size_t>(type) - 1;

}

locking_state piece::tick(uint16_t g)
{
    // check for collision, if it cannot move down, tick and reset subpixel to 0
    for (const auto &offset : LUT[index(type)][orientation])
    {
        const ivec2 square_pos = pos + offset + ivec2{1, 0};
        // if it's on ground or there is square below, count
        if (square_pos.y >= board.size() or !is_empty(board[square_pos.y][square_pos.x]))
        {
            subpixel = 0;
            return locking_state::tick;
        }
    }

    // otherwise, move down
    constexpr int DENOM = 128;
    int final_y = pos.y + (g / DENOM);
    if (g < DENOM)
    {
        subpixel += g;
        if (subpixel < DENOM) // the piece doesn't move down even though it can
            return locking_state::none;
        
        final_y++;
        subpixel -= DENOM;
    }
    else 
        subpixel = 0;

    // here, we know for sure the piece can move down at least 1 square
    for (; pos.y <= final_y; pos.y++)
    {
        for (const auto &offset : LUT[index(type)][orientation])
        {
            const ivec2 square_pos = pos + offset;
            if (square_pos.y >= board.size() or 
                !is_empty(board[square_pos.y][square_pos.x]))
                return locking_state::tick;
        }
    }
    return locking_state::reset;
}

void piece::translate(bool left)
{
    int move = left ? -1 : 1;
    for (const auto &offset : LUT[index(type)][orientation])
    {
        const ivec2 square_pos = pos + offset;
        int new_x = square_pos.x + move;
        if (new_x < 0 or new_x >= board.size() or 
            !is_empty(board[square_pos.y][new_x]))
            return;
    }

    pos.x += move;
}

void piece::rotate(bool left)
{
    int new_orientation = orientation + (left ? -1 : 1);
    if (new_orientation < 0)
        new_orientation = 3;
    else if (new_orientation > 3)
        new_orientation = 0;

    // TODO: this is only a naive implementation, need to check for collision
    // and potential kicks.
    for (const auto &offset : LUT[index(type)][new_orientation])
    {
        const ivec2 square_pos = pos + offset;
        if (square_pos.y >= board.size() or 
            !is_empty(board[square_pos.y][square_pos.x]))
            return;
    }

    orientation = new_orientation;
}
