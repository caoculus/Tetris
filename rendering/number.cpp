#include "number.hpp"
#include <iostream>
namespace mesh
{

number::number(sampler &s, const game::level_counter &level)
    : mesh(s), level_(level)
{
    bind();
    glBufferData(GL_ARRAY_BUFFER, sizeof(numer_) + sizeof(denom_), nullptr, GL_DYNAMIC_DRAW);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(N_INDICES), N_INDICES.data(), GL_STATIC_DRAW);
    set_vertex_layout();
    unbind();
}

void number::draw()
{
    bind();
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
        
        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(denom_), denom_.data());
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
        glBufferSubData(GL_ARRAY_BUFFER, sizeof(denom_), sizeof(numer_), numer_.data());
        glDrawElements(GL_TRIANGLES, N_INDICES.size(), GL_UNSIGNED_INT, nullptr);
    }
    else if (n_tens)
    {
        glBufferSubData(GL_ARRAY_BUFFER, sizeof(denom_), sizeof(numer_) * 2 / 3, numer_.data());
        glDrawElements(GL_TRIANGLES, N_INDICES.size() * 5 / 6, GL_UNSIGNED_INT, nullptr);
    }
    else
    {
        glBufferSubData(GL_ARRAY_BUFFER, sizeof(denom_), sizeof(numer_) / 3, numer_.data());
        glDrawElements(GL_TRIANGLES, N_INDICES.size() * 2 / 3, GL_UNSIGNED_INT, nullptr);
    }

    unbind();
}

}