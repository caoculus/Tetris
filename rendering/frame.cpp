#include <GL/glew.h>
#include "frame.hpp"

namespace mesh {

frame::frame(sampler &sampler)
    : mesh(sampler)
{
    bind();
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(SQUARE_INDICES), SQUARE_INDICES.data(), GL_STATIC_DRAW);
    auto coords = sampler_("frame");

    // vertices_ = {
    //     -x, -y, coords.Nx, coords.Ny,
    //     -x, y, coords.Nx, coords.Py,
    //     x, -y, coords.Px, coords.Ny,
    //     x, y, coords.Px, coords.Py
    // };
    vertices_ = {
        -1.0f, -1.0f, coords.Nx, coords.Ny,
        -1.0f, 1.0f, coords.Nx, coords.Py,
        1.0f, -1.0f, coords.Px, coords.Ny,
        1.0f, 1.0f, coords.Px, coords.Py        
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