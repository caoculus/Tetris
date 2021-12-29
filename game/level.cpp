#include "level.hpp"

level_counter &level_counter::operator++() noexcept
{
    if (level % 100 != 99 and level < 998 and ++level >= LEVEL_STEPS[step])
        ++step;
    return *this;
}

level_counter level_counter::operator++(int) noexcept
{
    auto tmp = *this;
    ++*this;
    return tmp;
}

level_counter &level_counter::operator+= (int n) noexcept
{
    level = std::min(999, level + n);
    while (level >= LEVEL_STEPS[step])
        ++step;
    return *this;
}

uint16_t level_counter::g() const noexcept
{
    return G_STEPS[step];
}

level_counter::operator int() const noexcept
{
    return level;
}
