#include <GL/glew.h>
#include "next.hpp"

namespace mesh
{

next::next(sampler &sampler, const square &init)
    : mesh(sampler)
{
    bind();
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(SQUARE_INDICES), SQUARE_INDICES.data(), GL_STATIC_DRAW);
    update(init);
    bind();
    set_vertex_layout();
    unbind();
}

void next::update(const square &next)
{
    auto sq = static_cast<std::size_t>(next);
    if (sq_ == sq)
        return;
    
    sq_ = sq;

    auto coords = sampler_("next", sq_);
    vertices_ = {
        3.f, -2.f, coords.Nx, coords.Py,
        3.f, 0.125f, coords.Nx, coords.Ny,
        7.f, -2.f, coords.Px, coords.Py,
        7.f, 0.125f, coords.Px, coords.Ny
    };
    
    bind();
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices_), vertices_.data(), GL_DYNAMIC_DRAW);
    unbind();
}

void next::draw()
{
    bind();
    glDrawElements(GL_TRIANGLES, SQUARE_INDICES.size(), GL_UNSIGNED_INT, nullptr);
    unbind();
}

}