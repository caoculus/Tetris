#include "game/randomizer.hpp"
#include <iostream>
#include <cassert>

static std::ostream &operator<< (std::ostream &os, const square &sq)
{
    switch (sq)
    {
        case square::I: os << "I"; break;
        case square::L: os << "L"; break;
        case square::J: os << "J"; break;
        case square::T: os << "T"; break;
        case square::O: os << "O"; break;
        case square::S: os << "S"; break;
        case square::Z: os << "Z"; break;
        default: break;
    }
    return os;
}

int main(int argc, char **argv)
{
    randomizer r;
    square next_one = r.next();
    for (int i = 0; i < 20; ++i)
    {
        square this_one = r();
        assert(this_one == next_one);
        std::cout << this_one << " ";
        next_one = r.next();
    }
    std::cout << std::endl;
    return 0;
}