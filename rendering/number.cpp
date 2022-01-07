#include "number.hpp"

namespace mesh
{

number::number(sampler &s, const game::level_counter &level,
               const uint32_t &clk, const uint32_t &score)
    : mesh(s), level_(level), clk_(clk), score_(score)
{
    bind();
    glBufferData(GL_ARRAY_BUFFER,
        sizeof(clk_vertices_) + sizeof(numer_) + sizeof(denom_) +
        sizeof(score_vertices_), nullptr, GL_DYNAMIC_DRAW);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(INDICES), INDICES.data(),
        GL_STATIC_DRAW);
    set_vertex_layout();
    unbind();
}

void number::draw()
{
    bind();

    update_clk();

    if (intern_denom_ != (1 + level_.section()) * 100)
        update_denom();

    if (intern_score_ != score_)
        update_score();

    if (level_ != intern_numer_)
        update_numer();

    if (1 /*n_hundreds_*/)
    {
        glBufferSubData(GL_ARRAY_BUFFER, sizeof(clk_vertices_) + sizeof(denom_),
            sizeof(numer_), numer_.data());
        glDrawElements(GL_TRIANGLES, INDICES.size(), GL_UNSIGNED_INT, nullptr);
    }
    // else if (n_tens_)
    // {
    //     glBufferSubData(GL_ARRAY_BUFFER, sizeof(clk_vertices_) + sizeof(denom_), sizeof(numer_) * 2 / 3, numer_.data());
    //     glDrawElements(GL_TRIANGLES, INDICES.size() - 6, GL_UNSIGNED_INT, nullptr);
    // }
    // else
    // {
    //     glBufferSubData(GL_ARRAY_BUFFER, sizeof(clk_vertices_) + sizeof(denom_), sizeof(numer_) / 3, numer_.data());
    //     glDrawElements(GL_TRIANGLES, INDICES.size() - 12, GL_UNSIGNED_INT, nullptr);
    // }

    unbind();
}

inline void number::update_clk()
{
    const auto mm = sampler_("number", clk_ / 36000);
    const auto m = sampler_("number", (clk_ / 3600) % 10);
    const auto ss = sampler_("number", (clk_ % 3600) / 600);
    const auto s = sampler_("number", ((clk_ % 3600) / 60) % 10);
    const auto tt = sampler_("number", (clk_ % 60) / 6);
    const auto t = sampler_("number", (((clk_ % 60) % 6) * 10) / 6);

    clk_vertices_ = {
        150 / 160.f - 1.f, 1.f - 224 / 120.f, ss.Nx, ss.Ny,
        150 / 160.f - 1.f, 1.f - 212 / 120.f, ss.Nx, ss.Py,
        158 / 160.f - 1.f, 1.f - 224 / 120.f, ss.Px, ss.Ny,
        158 / 160.f - 1.f, 1.f - 212 / 120.f, ss.Px, ss.Py,
        160 / 160.f - 1.f, 1.f - 224 / 120.f, s.Nx, s.Ny,
        160 / 160.f - 1.f, 1.f - 212 / 120.f, s.Nx, s.Py,
        168 / 160.f - 1.f, 1.f - 224 / 120.f, s.Px, s.Ny,
        168 / 160.f - 1.f, 1.f - 212 / 120.f, s.Px, s.Py,
        178 / 160.f - 1.f, 1.f - 224 / 120.f, tt.Nx, tt.Ny,
        178 / 160.f - 1.f, 1.f - 212 / 120.f, tt.Nx, tt.Py,
        186 / 160.f - 1.f, 1.f - 224 / 120.f, tt.Px, tt.Ny,
        186 / 160.f - 1.f, 1.f - 212 / 120.f, tt.Px, tt.Py,
        188 / 160.f - 1.f, 1.f - 224 / 120.f, t.Nx, t.Ny,
        188 / 160.f - 1.f, 1.f - 212 / 120.f, t.Nx, t.Py,
        196 / 160.f - 1.f, 1.f - 224 / 120.f, t.Px, t.Ny,
        196 / 160.f - 1.f, 1.f - 212 / 120.f, t.Px, t.Py,
        122 / 160.f - 1.f, 1.f - 224 / 120.f, mm.Nx, mm.Ny,
        122 / 160.f - 1.f, 1.f - 212 / 120.f, mm.Nx, mm.Py,
        130 / 160.f - 1.f, 1.f - 224 / 120.f, mm.Px, mm.Ny,
        130 / 160.f - 1.f, 1.f - 212 / 120.f, mm.Px, mm.Py,
        132 / 160.f - 1.f, 1.f - 224 / 120.f, m.Nx, m.Ny,
        132 / 160.f - 1.f, 1.f - 212 / 120.f, m.Nx, m.Py,
        140 / 160.f - 1.f, 1.f - 224 / 120.f, m.Px, m.Ny,
        140 / 160.f - 1.f, 1.f - 212 / 120.f, m.Px, m.Py
    };

    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(clk_vertices_),
        clk_vertices_.data());
}

inline void number::update_denom()
{
    intern_denom_ = (1 + level_.section()) * 100;
    if (intern_denom_ == 1000)
        intern_denom_ = 999;

    const auto hundred = sampler_("number", intern_denom_ / 100);
    const auto ten = sampler_("number", (intern_denom_ % 100) / 10);
    const auto one = sampler_("number", intern_denom_ % 10);

    denom_ = {
        86 / 160.f - 1.f, 1.f - 206 / 120.f, hundred.Nx, hundred.Ny,
        86 / 160.f - 1.f, 1.f - 196 / 120.f, hundred.Nx, hundred.Py,
        93 / 160.f - 1.f, 1.f - 206 / 120.f, hundred.Px, hundred.Ny,
        93 / 160.f - 1.f, 1.f - 196 / 120.f, hundred.Px, hundred.Py,
        94 / 160.f - 1.f, 1.f - 206 / 120.f, ten.Nx, ten.Ny,
        94 / 160.f - 1.f, 1.f - 196 / 120.f, ten.Nx, ten.Py,
        101 / 160.f - 1.f, 1.f - 206 / 120.f, ten.Px, ten.Ny,
        101 / 160.f - 1.f, 1.f - 196 / 120.f, ten.Px, ten.Py,
        102 / 160.f - 1.f, 1.f - 206 / 120.f, one.Nx, one.Ny,
        102 / 160.f - 1.f, 1.f - 196 / 120.f, one.Nx, one.Py,
        109 / 160.f - 1.f, 1.f - 206 / 120.f, one.Px, one.Ny,
        109 / 160.f - 1.f, 1.f - 196 / 120.f, one.Px, one.Py
    };

    glBufferSubData(GL_ARRAY_BUFFER, sizeof(clk_vertices_), sizeof(denom_),
        denom_.data());
}

inline void number::update_numer()
{
    intern_numer_ = level_;
    n_ones_ = intern_numer_ % 10;
    n_tens_ = (intern_numer_ >= 10) ? (intern_numer_ % 100) / 10 : 10;
    n_hundreds_ = (intern_numer_ >= 100) ? intern_numer_ / 100 : 10;

    const auto hundred = sampler_("number", n_hundreds_);
    const auto ten = sampler_("number", n_tens_);
    const auto one = sampler_("number", n_ones_);

    numer_ = {
        102 / 160.f - 1.f, 1.f - 190 / 120.f, one.Nx, one.Ny,
        102 / 160.f - 1.f, 1.f - 180 / 120.f, one.Nx, one.Py,
        109 / 160.f - 1.f, 1.f - 190 / 120.f, one.Px, one.Ny,
        109 / 160.f - 1.f, 1.f - 180 / 120.f, one.Px, one.Py,
        94 / 160.f - 1.f, 1.f - 190 / 120.f, ten.Nx, ten.Ny,
        94 / 160.f - 1.f, 1.f - 180 / 120.f, ten.Nx, ten.Py,
        101 / 160.f - 1.f, 1.f - 190 / 120.f, ten.Px, ten.Ny,
        101 / 160.f - 1.f, 1.f - 180 / 120.f, ten.Px, ten.Py,
        86 / 160.f - 1.f, 1.f - 190 / 120.f, hundred.Nx, hundred.Ny,
        86 / 160.f - 1.f, 1.f - 180 / 120.f, hundred.Nx, hundred.Py,
        93 / 160.f - 1.f, 1.f - 190 / 120.f, hundred.Px, hundred.Ny,
        93 / 160.f - 1.f, 1.f - 180 / 120.f, hundred.Px, hundred.Py
    };
}

inline void number::update_score()
{
    intern_score_ = score_;
    const auto s0 = sampler_("number", intern_score_ % 10);
    const auto s1 = sampler_("number",
        (intern_score_ >= 10) ? (intern_score_ % 100) / 10 : 10);
    const auto s2 = sampler_("number",
        (intern_score_ >= 100) ? (intern_score_ % 1000) / 100 : 10);
    const auto s3 = sampler_("number",
        (intern_score_ >= 1000) ? (intern_score_ % 10000) / 1000 : 10);
    const auto s4 = sampler_("number",
        (intern_score_ >= 10000) ? (intern_score_ % 100000) / 10000 : 10);
    const auto s5 = sampler_("number",
        (intern_score_ >= 100000) ? (intern_score_ % 1000000) / 100000 : 10);

    score_vertices_ = {
        103 / 160.f - 1.f, 1.f - 155 / 120.f, s0.Nx, s0.Ny,
        103 / 160.f - 1.f, 1.f - 145 / 120.f, s0.Nx, s0.Py,
        110 / 160.f - 1.f, 1.f - 155 / 120.f, s0.Px, s0.Ny,
        110 / 160.f - 1.f, 1.f - 145 / 120.f, s0.Px, s0.Py,
        95 / 160.f - 1.f, 1.f - 155 / 120.f, s1.Nx, s1.Ny,
        95 / 160.f - 1.f, 1.f - 145 / 120.f, s1.Nx, s1.Py,
        102 / 160.f - 1.f, 1.f - 155 / 120.f, s1.Px, s1.Ny,
        102 / 160.f - 1.f, 1.f - 145 / 120.f, s1.Px, s1.Py,
        86 / 160.f - 1.f, 1.f - 155 / 120.f, s2.Nx, s2.Ny,
        86 / 160.f - 1.f, 1.f - 145 / 120.f, s2.Nx, s2.Py,
        93 / 160.f - 1.f, 1.f - 155 / 120.f, s2.Px, s2.Ny,
        93 / 160.f - 1.f, 1.f - 145 / 120.f, s2.Px, s2.Py,
        78 / 160.f - 1.f, 1.f - 155 / 120.f, s3.Nx, s3.Ny,
        78 / 160.f - 1.f, 1.f - 145 / 120.f, s3.Nx, s3.Py,
        85 / 160.f - 1.f, 1.f - 155 / 120.f, s3.Px, s3.Ny,
        85 / 160.f - 1.f, 1.f - 145 / 120.f, s3.Px, s3.Py,
        70 / 160.f - 1.f, 1.f - 155 / 120.f, s4.Nx, s4.Ny,
        70 / 160.f - 1.f, 1.f - 145 / 120.f, s4.Nx, s4.Py,
        77 / 160.f - 1.f, 1.f - 155 / 120.f, s4.Px, s4.Ny,
        77 / 160.f - 1.f, 1.f - 145 / 120.f, s4.Px, s4.Py,
        62 / 160.f - 1.f, 1.f - 155 / 120.f, s5.Nx, s5.Ny,
        62 / 160.f - 1.f, 1.f - 145 / 120.f, s5.Nx, s5.Py,
        69 / 160.f - 1.f, 1.f - 155 / 120.f, s5.Px, s5.Ny,
        69 / 160.f - 1.f, 1.f - 145 / 120.f, s5.Px, s5.Py
    };

    glBufferSubData(GL_ARRAY_BUFFER,
        sizeof(clk_vertices_) + sizeof(denom_) + sizeof(numer_),
        sizeof(score_vertices_), score_vertices_.data());
}

}