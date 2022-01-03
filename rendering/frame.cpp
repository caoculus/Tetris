#include <GL/glew.h>
#include "frame.hpp"

namespace mesh {

frame::frame(sampler &sampler)
    : mesh(sampler)
{
    bind();
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(SQUARE_INDICES), SQUARE_INDICES.data(), GL_STATIC_DRAW);
    auto coords = sampler_("frame");

    vertices_ = {
        -1.f, -1.f, coords.Nx, coords.Ny,
        -1.f, 1.f, coords.Nx, coords.Py,
        1.f, -1.f, coords.Px, coords.Ny,
        1.f, 1.f, coords.Px, coords.Py
    };

    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices_), vertices_.data(), GL_STATIC_DRAW);
    set_vertex_layout();
    unbind();
}

void frame::draw()
{
    bind();
    glDrawElements(GL_TRIANGLES, SQUARE_INDICES.size(), GL_UNSIGNED_INT, nullptr);
    unbind();
}

}