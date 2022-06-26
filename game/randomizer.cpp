#include "randomizer.hpp"
#include <algorithm>

game::randomizer::randomizer()
{
    std::uniform_int_distribution<int> first_piece_dist {1, 4};
    switch(first_piece_dist(rng_))
    {
        case 1: next_piece_ = square::I; break;
        case 2: next_piece_ = square::L; break;
        case 3: next_piece_ = square::J; break;
        case 4: next_piece_ = square::T; break;
        default: break;
    }
    history_.push_back(square::Z);
    history_.push_back(square::Z);
    history_.push_back(square::Z);
    history_.push_back(next_piece_);
}

square game::randomizer::operator()()
{
    square ret = next_piece_;
    for (int i = 0; i < 4; ++i)
    {
        // generate a new piece
        next_piece_ = static_cast<square>(dist_(rng_));
        if (std::find(history_.begin(), history_.end(), next_piece_) == history_.end())
            break;
    }
    history_.pop_front();
    history_.push_back(next_piece_);
    return ret;
}

[[nodiscard]] square game::randomizer::next() const noexcept
{
    return next_piece_;
}
