#include "piece.hpp"
#include "level.hpp"
#include <stdexcept>
#include <algorithm>

std::size_t game::piece::index(square type)
{
    if (type == square::none)
        throw std::invalid_argument(
            "square::none cannot be indexed as there is no piece there");
    return static_cast<std::size_t>(type) - 1;

}

locking_state game::piece::tick(uint16_t g)
{
    // check for collision, if it cannot move down, tick and reset subpixel to 0
    if (collide(pos_, shift_t::down))
    {
        subpixel_ = 0;
        return locking_state::tick;
    }

    // otherwise, move down
    int final_y = pos_.y + (g / game::level_counter::DENOM);
    if (g < game::level_counter::DENOM)
    {
        subpixel_ += g;
        // the piece doesn't move down even though it can
        if (subpixel_ < game::level_counter::DENOM)
            return locking_state::none;

        final_y++;
        subpixel_ -= game::level_counter::DENOM;
    }

    // here, we know for sure the piece can move down at least 1 square
    for (; pos_.y < final_y; pos_.y++)
    {
        if (collide(pos_, shift_t::down))
        {
            return locking_state::tick;
        }
    }

    return collide(pos_, shift_t::down) ? locking_state::tick
                                        : locking_state::none;
}

bool game::piece::translate(shift_t shift)
{
    if (shift == shift_t::none or shift == shift_t::down or
        collide(pos_, shift))
        return false;

    pos_.x += (shift == shift_t::left) ? -1 : 1;
    return true;
}

bool game::piece::rotate(rotation_t rotation, bool kick)
{
    if (rotation == rotation_t::none)
    {
        return true;
    }

    int8_t old_orientation = orientation_;

    orientation_ = static_cast<int8_t>(orientation_ +
                                       (rotation == rotation_t::ccw ? 1 : -1));

    if (orientation_ < 0)
        orientation_ = 3;
    else if (orientation_ > 3)
        orientation_ = 0;

    if (collide(pos_, shift_t::none))
    {
        if (!kick or type_ == square::I or type_ == square::O or
            ((type_ == square::J or type_ == square::L or
              type_ == square::T) and !can_rotate_jlt()))
        {
            orientation_ = old_orientation;
            return false;
        }
        if (translate(shift_t::right))
        {
            return true;
        }
        if (translate(shift_t::left))
        {
            return true;
        }
        orientation_ = old_orientation;
        return false;
    }

    return true;
}

bool game::piece::collide(ivec2 pos, shift_t shift) const
{
    ivec2 new_pos{};
    switch (shift)
    {
        case shift_t::none:
            new_pos = pos;
            break;
        case shift_t::left:
            new_pos = pos + ivec2{0, -1};
            break;
        case shift_t::down:
            new_pos = pos + ivec2{1, 0};
            break;
        case shift_t::right:
            new_pos = pos + ivec2{0, 1};
            break;
    }

    bool ret = std::ranges::any_of(LUT[index(type_)][orientation_],
        [&](const ivec2 &offset)
        {
            ivec2 square_pos = new_pos + offset;
            return square_pos.y >= board_.size() or
                   square_pos.x < 0 or
                   square_pos.x >= board_[0].size() or
                   !is_empty(
                       board_[square_pos.y][square_pos.x]);
        });

    return ret;
}

bool game::piece::can_rotate_jlt()
{
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (!is_empty(board_[pos_.y + i][pos_.x + j]))
                return (j != 1);
    return true;
}

std::array<ivec2, 4> game::piece::piece_squares() const
{
    return squares(pos_);
}

std::array<ivec2, 4> game::piece::shadow_squares() const
{
    return squares(shadow_position());
}

std::array<ivec2, 4> game::piece::squares(ivec2 pos) const
{
    std::array<ivec2, 4> squares{};

    for (int i = 0; i < 4; i++)
    {
        squares[i] = pos + LUT[index(type_)][orientation_][i];
    }

    return squares;
}

ivec2 game::piece::shadow_position() const
{
    ivec2 shadow_pos{pos_};

    while (!collide(shadow_pos, shift_t::down))
    {
        shadow_pos += ivec2{1, 0};
    }

    return shadow_pos;
}

bool game::piece::spawn(square type, rotation_t rotation)
{
    pos_ = ivec2{0, 3};
    orientation_ = 0;
    subpixel_ = 0;
    type_ = type;
    // try rotating without kick, and then try not rotating
    return ((rotation != rotation_t::none and rotate(rotation, false)) or
            !collide(pos_, shift_t::none));
}
