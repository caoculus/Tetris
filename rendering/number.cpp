#include "number.hpp"
#include <iostream>
namespace mesh
{

number::number(sampler &s, const game::level_counter &level, const int &clk)
    : mesh(s), level_(level), clk_(clk)
{
    bind();
    glBufferData(GL_ARRAY_BUFFER, sizeof(clk_vertices_) + sizeof(numer_) + sizeof(denom_), nullptr, GL_DYNAMIC_DRAW);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(INDICES), INDICES.data(), GL_STATIC_DRAW);
    set_vertex_layout();
    unbind();
}

void number::draw()
{
    bind();

    // update clock
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
        160 / 160.f - 1.f, 1.f - 224 / 120.f, s.Nx , s.Ny ,
        160 / 160.f - 1.f, 1.f - 212 / 120.f, s.Nx , s.Py ,
        168 / 160.f - 1.f, 1.f - 224 / 120.f, s.Px , s.Ny ,
        168 / 160.f - 1.f, 1.f - 212 / 120.f, s.Px , s.Py ,
        178 / 160.f - 1.f, 1.f - 224 / 120.f, tt.Nx, tt.Ny,
        178 / 160.f - 1.f, 1.f - 212 / 120.f, tt.Nx, tt.Py,
        186 / 160.f - 1.f, 1.f - 224 / 120.f, tt.Px, tt.Ny,
        186 / 160.f - 1.f, 1.f - 212 / 120.f, tt.Px, tt.Py,
        188 / 160.f - 1.f, 1.f - 224 / 120.f, t.Nx , t.Ny ,
        188 / 160.f - 1.f, 1.f - 212 / 120.f, t.Nx , t.Py ,
        196 / 160.f - 1.f, 1.f - 224 / 120.f, t.Px , t.Ny ,
        196 / 160.f - 1.f, 1.f - 212 / 120.f, t.Px , t.Py ,
        122 / 160.f - 1.f, 1.f - 224 / 120.f, mm.Nx, mm.Ny,
        122 / 160.f - 1.f, 1.f - 212 / 120.f, mm.Nx, mm.Py,
        130 / 160.f - 1.f, 1.f - 224 / 120.f, mm.Px, mm.Ny,
        130 / 160.f - 1.f, 1.f - 212 / 120.f, mm.Px, mm.Py,
        132 / 160.f - 1.f, 1.f - 224 / 120.f, m.Nx , m.Ny ,
        132 / 160.f - 1.f, 1.f - 212 / 120.f, m.Nx , m.Py ,
        140 / 160.f - 1.f, 1.f - 224 / 120.f, m.Px , m.Ny ,
        140 / 160.f - 1.f, 1.f - 212 / 120.f, m.Px , m.Py 
    };

    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(clk_vertices_), clk_vertices_.data());

    if (intern_denom_ != (1+level_.section()) * 100)
    {
        intern_denom_ = (1+level_.section()) * 100;
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
            101/ 160.f - 1.f, 1.f - 206 / 120.f, ten.Px, ten.Ny,
            101/ 160.f - 1.f, 1.f - 196 / 120.f, ten.Px, ten.Py,
            102/ 160.f - 1.f, 1.f - 206 / 120.f, one.Nx, one.Ny,
            102/ 160.f - 1.f, 1.f - 196 / 120.f, one.Nx, one.Py,
            109/ 160.f - 1.f, 1.f - 206 / 120.f, one.Px, one.Ny,
            109/ 160.f - 1.f, 1.f - 196 / 120.f, one.Px, one.Py
        };
        
        glBufferSubData(GL_ARRAY_BUFFER, sizeof(clk_vertices_), sizeof(denom_), denom_.data());
    }

    if (level_ != intern_numer_)
    {
        intern_numer_ = level_;
        n_ones = intern_numer_ % 10;
        n_tens = (intern_numer_ % 100) / 10;
        n_hundreds = intern_numer_ / 100;

        const auto hundred = sampler_("number", n_hundreds);
        const auto ten = sampler_("number", n_tens);
        const auto one = sampler_("number", n_ones);

        numer_ = {
            102/ 160.f - 1.f, 1.f - 190 / 120.f, one.Nx, one.Ny,
            102/ 160.f - 1.f, 1.f - 180 / 120.f, one.Nx, one.Py,
            109/ 160.f - 1.f, 1.f - 190 / 120.f, one.Px, one.Ny,
            109/ 160.f - 1.f, 1.f - 180 / 120.f, one.Px, one.Py,
            94 / 160.f - 1.f, 1.f - 190 / 120.f, ten.Nx, ten.Ny,
            94 / 160.f - 1.f, 1.f - 180 / 120.f, ten.Nx, ten.Py,
            101/ 160.f - 1.f, 1.f - 190 / 120.f, ten.Px, ten.Ny,
            101/ 160.f - 1.f, 1.f - 180 / 120.f, ten.Px, ten.Py,
            86 / 160.f - 1.f, 1.f - 190 / 120.f, hundred.Nx, hundred.Ny,
            86 / 160.f - 1.f, 1.f - 180 / 120.f, hundred.Nx, hundred.Py,
            93 / 160.f - 1.f, 1.f - 190 / 120.f, hundred.Px, hundred.Ny,
            93 / 160.f - 1.f, 1.f - 180 / 120.f, hundred.Px, hundred.Py            
        };
    }
    
    if (n_hundreds)
    {
        glBufferSubData(GL_ARRAY_BUFFER, sizeof(clk_vertices_) + sizeof(denom_), sizeof(numer_), numer_.data());
        glDrawElements(GL_TRIANGLES, INDICES.size(), GL_UNSIGNED_INT, nullptr);
    }
    else if (n_tens)
    {
        glBufferSubData(GL_ARRAY_BUFFER, sizeof(clk_vertices_) + sizeof(denom_), sizeof(numer_) * 2 / 3, numer_.data());
        glDrawElements(GL_TRIANGLES, INDICES.size() - 6, GL_UNSIGNED_INT, nullptr);
    }
    else
    {
        glBufferSubData(GL_ARRAY_BUFFER, sizeof(clk_vertices_) + sizeof(denom_), sizeof(numer_) / 3, numer_.data());
        glDrawElements(GL_TRIANGLES, INDICES.size() - 12, GL_UNSIGNED_INT, nullptr);
    }

    unbind();
}

}