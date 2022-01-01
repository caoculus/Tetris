#include "active.hpp"

namespace mesh {

active::active(sampler &sampler, const game::piece &active_piece, const game::level_counter &level)
    : mesh(sampler), active_piece_(active_piece), level_(level)
    {
        update();
    }

void active::draw()
{
    if (!p_vertices_.empty())
    {
    }
    if (!s_vertices_.empty())
    {

    }
}

void active::update()
{
    auto type = active_piece_.type();
    if (type == square::none)
        return;

    const auto active_type_i = static_cast<std::size_t>(type);
    const auto shadow_type_i = active_type_i + 7;

    auto active_sq = active_piece_.piece_squares();
    auto shadow_sq = active_piece_.shadow_squares();

//    for (const auto &[y, x] : active_sq)
//    {
//
//    }


}

}