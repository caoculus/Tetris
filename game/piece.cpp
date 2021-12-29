#include "piece.hpp"
#include <stdexcept>
#include <algorithm>

std::size_t piece::index(square type)
{
    if (type == square::none)
        throw std::invalid_argument(
            "square::none cannot be indexed as there is no piece there");
    return static_cast<std::size_t>(type) - 1;

}

locking_state piece::tick(uint16_t g)
{
    // check for collision, if it cannot move down, tick and reset subpixel to 0
    if (collide(pos, shift_t::down))
    {
        subpixel = 0;
        return locking_state::tick;
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
        if (collide(pos, shift_t::down))
        {
            return locking_state::tick;
        }
    }
    return locking_state::reset;
}

bool piece::translate(bool left)
{
    int move = left ? -1 : 1;
    shift_t shift = left ? shift_t::left : shift_t::right;

    if (collide(pos, shift))
    {
        return false;
    }

    pos.x += move;
    return true;
}

void piece::rotate(bool left)
{
    int old_orientation = orientation;

    orientation = orientation + (left ? -1 : 1);
    if (orientation < 0)
        orientation = 3;
    else if (orientation > 3)
        orientation = 0;

    if (collide(pos, shift_t::none))
    {
        if (type == square::I or
            ((type == square::J or type == square::L or type == square::T) and
             !can_rotate_jlt()))
        {
            orientation = old_orientation;
            return;
        }
        if (translate(false))
        {
            return;
        }
        if (translate(true))
        {
            return;
        }
        orientation = old_orientation;
    }
}

bool piece::collide(ivec2 old_pos, shift_t shift)
{
    ivec2 new_pos{};
    switch (shift)
    {
        case shift_t::none:
            new_pos = old_pos;
            break;
        case shift_t::left:
            new_pos = old_pos + ivec2{-1, 0};
            break;
        case shift_t::down:
            new_pos = old_pos + ivec2{0, 1};
            break;
        case shift_t::right:
            new_pos = old_pos + ivec2{1, 0};
            break;
    }

    return std::ranges::any_of(LUT[index(type)][orientation],
                               [&](const ivec2 &offset)
                               {
                                   const ivec2 square_pos = new_pos + offset;
                                   return square_pos.y >= board.size() or
                                          square_pos.x < 0 or
                                          square_pos.x >= board[0].size() or
                                          !is_empty(
                                              board[square_pos.y][square_pos.x]);
                               });
}

bool piece::can_rotate_jlt()
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            ivec2 square_pos = pos + ivec2{i, j};
            if (!is_empty(board[square_pos.y][square_pos.x]))
            {
                return (j != 1);
            }
        }
    }
    return true;
}

