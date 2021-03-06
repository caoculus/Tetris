#include "level.hpp"

game::level_counter &game::level_counter::operator++() noexcept
{
    if (level_ % 100 != 99 and level_ < 998 and ++level_ >= LEVEL_STEPS[step_])
        ++step_;
    return *this;
}

game::level_counter &game::level_counter::operator+= (int n) noexcept
{
    level_ = std::min(999, level_ + n);
    while (level_ >= LEVEL_STEPS[step_])
        ++step_;
    return *this;
}

uint16_t game::level_counter::g() const noexcept
{
    return G_STEPS[step_];
}

game::level_counter::operator int() const noexcept
{
    return level_;
}
