#include "number.hpp"
#include "game/game.hpp"
namespace mesh
{

number::number(sampler &s, const game::level_counter &level,
               const uint32_t &clk, const uint32_t &score, const uint8_t &grade)
    : mesh(s), level_(level), clk_(clk), score_(score), grade_(grade)
{
    bind();
    constexpr auto const VBO_SIZE = sizeof(clk_vertices_) + sizeof(numer_) + sizeof(denom_) +
        sizeof(score_vertices_) + sizeof(next_grade_vertices_) + sizeof(sprite_vertices_);

    glBufferData(GL_ARRAY_BUFFER, VBO_SIZE, nullptr, GL_DYNAMIC_DRAW);
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

    if (grade_ != intern_grade_)
        update_grade();

    glDrawElements(GL_TRIANGLES, INDICES.size(), GL_UNSIGNED_INT, nullptr);
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

    update_number<3>(denom_, sampler_, intern_denom_, 109, 196);

    glBufferSubData(GL_ARRAY_BUFFER, sizeof(clk_vertices_), sizeof(denom_),
        denom_.data());
}

inline void number::update_numer()
{
    intern_numer_ = level_;
    update_number<3>(numer_, sampler_, intern_numer_, 109, 180);

    glBufferSubData(GL_ARRAY_BUFFER, sizeof(clk_vertices_) + sizeof(denom_),
        sizeof(numer_), numer_.data());
}

inline void number::update_score()
{
    intern_score_ = score_;
    update_number<6>(score_vertices_, sampler_, intern_score_, 110, 145);
    
    glBufferSubData(GL_ARRAY_BUFFER,
        sizeof(clk_vertices_) + sizeof(denom_) + sizeof(numer_),
        sizeof(score_vertices_), score_vertices_.data());
}

inline void number::update_grade()
{
    intern_grade_ = grade_;

    update_number<6>(next_grade_vertices_, sampler_, GRADES[intern_grade_], 110, 79);
    
    auto const &sprite = sampler_("grade", intern_grade_);

    sprite_vertices_ = {
        86 / 160.f - 1.f, 1.f - 58 / 120.f, sprite.Nx, sprite.Ny,
        86 / 160.f - 1.f, 1.f - 35 / 120.f, sprite.Nx, sprite.Py,
        110/ 160.f - 1.f, 1.f - 58 / 120.f, sprite.Px, sprite.Ny,
        110/ 160.f - 1.f, 1.f - 35 / 120.f, sprite.Px, sprite.Py
    };

    constexpr auto const OFFSET = sizeof(clk_vertices_) + sizeof(denom_) + sizeof(numer_) + sizeof(score_vertices_);

    glBufferSubData(GL_ARRAY_BUFFER, OFFSET, sizeof(next_grade_vertices_), next_grade_vertices_.data());
    
    glBufferSubData(GL_ARRAY_BUFFER, OFFSET + sizeof(next_grade_vertices_),
        sizeof(sprite_vertices_), sprite_vertices_.data());
}

}