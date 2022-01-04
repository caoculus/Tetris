#include <GL/glew.h>
#include "active.hpp"

namespace mesh
{

active::active(sampler &sampler, const game::piece &active_piece,
               const game::level_counter &level, const state_t &state,
               const int &frame_num)
    : mesh(sampler), active_piece_(active_piece), level_(level), state_(state),
      frame_num_(frame_num)
{
    bind();
    glBufferData(GL_ARRAY_BUFFER, sizeof(p_vertices_) + sizeof(s_vertices_),
        nullptr, GL_DYNAMIC_DRAW);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(INDICES), INDICES.data(),
        GL_STATIC_DRAW);
    set_vertex_layout();
    unbind();
}

void active::draw()
{
    update();

//    if ((state_ >= 0 and state_ < 27) or (state_ > 29))
    if (state_ == state_t::spawn or state_ == state_t::are or
        state_ == state_t::clear)
        return;

    bind();
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(s_vertices_),
        s_vertices_.data());
    glBufferSubData(GL_ARRAY_BUFFER, sizeof(s_vertices_), sizeof(p_vertices_),
        p_vertices_.data());

    if (level_ >= 100 or state_ != state_t::active)
        glDrawElements(GL_TRIANGLES, INDICES.size() / 2, GL_UNSIGNED_INT,
            (void const *) (sizeof(INDICES) / 2));
    else
        glDrawElements(GL_TRIANGLES, INDICES.size(), GL_UNSIGNED_INT, nullptr);

    unbind();
}

void active::update()
{
    auto coords = [&]
    {
        switch (state_)
        {
            case state_t::flash:
                return sampler_("flash");
            case state_t::dim:
                return sampler_("piece",
                    static_cast<std::size_t>(active_piece_.type()));
            default:
                return sampler_("active",
                    static_cast<std::size_t>(active_piece_.type()));
        }
    }();

    auto active_sq = active_piece_.piece_squares();
    auto shadow_sq = active_piece_.shadow_squares();

    for (int sq = 0; sq < 4; ++sq)
    {
        p_vertices_[sq * 16 + 0] = active_sq[sq].x + 0.f;
        p_vertices_[sq * 16 + 1] = active_sq[sq].y + 0.f;
        p_vertices_[sq * 16 + 2] = coords.Nx;
        p_vertices_[sq * 16 + 3] = coords.Py;
        p_vertices_[sq * 16 + 4] = active_sq[sq].x + 0.f;
        p_vertices_[sq * 16 + 5] = active_sq[sq].y + 1.f;
        p_vertices_[sq * 16 + 6] = coords.Nx;
        p_vertices_[sq * 16 + 7] = coords.Ny;
        p_vertices_[sq * 16 + 8] = active_sq[sq].x + 1.f;
        p_vertices_[sq * 16 + 9] = active_sq[sq].y + 0.f;
        p_vertices_[sq * 16 + 10] = coords.Px;
        p_vertices_[sq * 16 + 11] = coords.Py;
        p_vertices_[sq * 16 + 12] = active_sq[sq].x + 1.f;
        p_vertices_[sq * 16 + 13] = active_sq[sq].y + 1.f;
        p_vertices_[sq * 16 + 14] = coords.Px;
        p_vertices_[sq * 16 + 15] = coords.Ny;
    }

    coords = sampler_("shadow", static_cast<std::size_t>(active_piece_.type()));

    if (level_ < 100)
    {
        for (int sq = 0; sq < 4; ++sq)
        {
            s_vertices_[sq * 16 + 0] = shadow_sq[sq].x + 0.f;
            s_vertices_[sq * 16 + 1] = shadow_sq[sq].y + 0.f;
            s_vertices_[sq * 16 + 2] = coords.Nx;
            s_vertices_[sq * 16 + 3] = coords.Py;
            s_vertices_[sq * 16 + 4] = shadow_sq[sq].x + 0.f;
            s_vertices_[sq * 16 + 5] = shadow_sq[sq].y + 1.f;
            s_vertices_[sq * 16 + 6] = coords.Nx;
            s_vertices_[sq * 16 + 7] = coords.Ny;
            s_vertices_[sq * 16 + 8] = shadow_sq[sq].x + 1.f;
            s_vertices_[sq * 16 + 9] = shadow_sq[sq].y + 0.f;
            s_vertices_[sq * 16 + 10] = coords.Px;
            s_vertices_[sq * 16 + 11] = coords.Py;
            s_vertices_[sq * 16 + 12] = shadow_sq[sq].x + 1.f;
            s_vertices_[sq * 16 + 13] = shadow_sq[sq].y + 1.f;
            s_vertices_[sq * 16 + 14] = coords.Px;
            s_vertices_[sq * 16 + 15] = coords.Ny;
        }
    }
}

}