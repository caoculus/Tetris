#include <GL/glew.h>
#include "background.hpp"
#include <iostream>
bkgd::bkgd(sampler &sampler, game::level_counter &level)
    : mesh(sampler), level_(level), section_(level.section())
{
    bind();
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices_), indices_.data(), GL_STATIC_DRAW);
    auto coords = sampler_("bkgd", section_);

    vertices_ = {
        -1.0f, -1.0f, coords.Nx, coords.Ny,
        -1.0f,  1.0f, coords.Nx, coords.Py,
        1.0f,  -1.0f, coords.Px, coords.Ny,
        1.0f,   1.0f, coords.Px, coords.Py
    };

    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices_), vertices_.data(), GL_DYNAMIC_DRAW);
    set_vertex_layout();
    unbind();
}


void bkgd::draw()
{
    bind();
    if (section_ != level_.section())
    {
        section_ = level_.section();
        auto coords = sampler_("bkgd", section_);

        vertices_ = {
            -1.0f, -1.0f, coords.Nx, coords.Ny,
            -1.0f,  1.0f, coords.Nx, coords.Py,
            1.0f,  -1.0f, coords.Px, coords.Ny,
            1.0f,   1.0f, coords.Px, coords.Py
        };

        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices_), vertices_.data(), GL_DYNAMIC_DRAW);
    }

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
    unbind();
}
