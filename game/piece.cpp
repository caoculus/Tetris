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

bool piece::translate(shift_t shift)
{
    if (shift == shift_t::none or collide(pos, shift))
        return false;
    
    pos.x += (shift==shift_t::left) ? -1 : 1;
    return true;
}

void piece::rotate(rotation_t rotation)
{
    if (rotation == rotation_t::none)
    {
        return;
    }

    int old_orientation = orientation;

    orientation = orientation + (rotation == rotation_t::ccw ? 1 : -1);
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
        if (translate(shift_t::right))
        {
            return;
        }
        if (translate(shift_t::left))
        {
            return;
        }
        orientation = old_orientation;
    }
}

bool piece::collide(ivec2 piece_pos, shift_t shift) const
{
    ivec2 new_pos{};
    switch (shift)
    {
        case shift_t::none:
            new_pos = piece_pos;
            break;
        case shift_t::left:
            new_pos = piece_pos + ivec2{0, -1};
            break;
        case shift_t::down:
            new_pos = piece_pos + ivec2{1, 0};
            break;
        case shift_t::right:
            new_pos = piece_pos + ivec2{0, 1};
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

std::array<ivec2, 4> piece::piece_squares() const
{
    return squares(pos);
}

std::array<ivec2, 4> piece::shadow_squares() const
{
    return squares(shadow_position());
}

std::array<ivec2, 4> piece::squares(ivec2 piece_pos) const
{
    std::array<ivec2, 4> squares{};

    for (int i = 0; i < 4; i++)
    {
        squares[i] = piece_pos + LUT[index(type)][orientation][i];
    }

    return squares;
}

ivec2 piece::shadow_position() const
{
    ivec2 shadow_pos{pos};

    while (!collide(shadow_pos, shift_t::down))
    {
        shadow_pos += ivec2{1, 0};
    }

    return shadow_pos;
}

piece &piece::operator=(const piece &other)
{
    subpixel = other.subpixel;
    orientation = other.orientation;
    pos = other.pos;
    return *this;
}
