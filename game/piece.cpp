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
    if (collide(pos_, shift_t::down))
    {
        subpixel_ = 0;
        return locking_state::tick;
    }

    // otherwise, move down
    constexpr int DENOM = 128;
    int final_y = pos_.y_ + (g / DENOM);
    if (g < DENOM)
    {
        subpixel_ += g;
        if (subpixel_ < DENOM) // the piece doesn't move down even though it can
            return locking_state::none;

        final_y++;
        subpixel_ -= DENOM;
    }
    else
        subpixel_ = 0;

    // here, we know for sure the piece can move down at least 1 square
    for (; pos_.y_ <= final_y; pos_.y_++)
    {
        if (collide(pos_, shift_t::down))
        {
            return locking_state::tick;
        }
    }
    return locking_state::reset;
}

bool piece::translate(shift_t shift)
{
    if (shift == shift_t::none or collide(pos_, shift))
        return false;

    pos_.x_ += (shift == shift_t::left) ? -1 : 1;
    return true;
}

void piece::rotate(rotation_t rotation)
{
    if (rotation == rotation_t::none)
    {
        return;
    }

    int old_orientation = orientation_;

    orientation_ = orientation_ + (rotation == rotation_t::ccw ? 1 : -1);
    if (orientation_ < 0)
        orientation_ = 3;
    else if (orientation_ > 3)
        orientation_ = 0;

    if (collide(pos_, shift_t::none))
    {
        if (type_ == square::I or
            ((type_ == square::J or type_ == square::L or type_ == square::T) and
             !can_rotate_jlt()))
        {
            orientation_ = old_orientation;
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
        orientation_ = old_orientation;
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

    return std::ranges::any_of(LUT[index(type_)][orientation_],
                               [&](const ivec2 &offset)
                               {
                                   ivec2 square_pos = new_pos + offset;
                                   return square_pos.y_ >= board_.size() or
                                          square_pos.x_ < 0 or
                                          square_pos.x_ >= board_[0].size() or
                                          !is_empty(
                                              board_[square_pos.y_][square_pos.x_]);
                               });
}

bool piece::can_rotate_jlt()
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            ivec2 square_pos = pos_ + ivec2{i, j};
            if (!is_empty(board_[square_pos.y_][square_pos.x_]))
            {
                return (j != 1);
            }
        }
    }
    return true;
}

std::array<ivec2, 4> piece::piece_squares() const
{
    return squares(pos_);
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
        squares[i] = piece_pos + LUT[index(type_)][orientation_][i];
    }

    return squares;
}

ivec2 piece::shadow_position() const
{
    ivec2 shadow_pos{pos_};

    while (!collide(shadow_pos, shift_t::down))
    {
        shadow_pos += ivec2{1, 0};
    }

    return shadow_pos;
}

void piece::reset(square type)
{
    pos_ = ivec2{0, 3};
    orientation_ = 0;
    subpixel_ = 0;
    type_ = type;
}
