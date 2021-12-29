#include "randomizer.hpp"

randomizer::randomizer()
{
    std::uniform_int_distribution<int> first_piece_dist {1, 4};
    switch(first_piece_dist(rng))
    {
        case 1: next_piece = square::I; break;
        case 2: next_piece = square::L; break;
        case 3: next_piece = square::J; break;
        case 4: next_piece = square::T; break;
        default: break;
    }
    history.push_back(square::Z);
    history.push_back(square::Z);
    history.push_back(square::Z);
    history.push_back(next_piece);
}

square randomizer::operator()()
{
    square ret = next_piece;
    for (int i = 0; i < 4; ++i)
    {
        // generate a new piece
        next_piece = static_cast<square>(dist(rng));
        if (std::find(history.begin(), history.end(), next_piece) == history.end())
            break;
    }
    history.pop_front();
    history.push_back(next_piece);
    return ret;
}

[[nodiscard]] square randomizer::next() const noexcept
{
    return next_piece;
}
