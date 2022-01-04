#include <GL/glew.h>
#include "dim.hpp"

namespace mesh
{

dim::dim(sampler &sampler, std::size_t dim)
    : mesh(sampler), to_draw_(dim)
{
    if (to_draw_)
    {
        auto coords = sampler("dim", dim);

        bind();

        quad_vertices<1> vertices = {
            -0.5f, 0.5f, coords.Nx, coords.Py,
            -0.5f, 21.5f, coords.Nx, coords.Ny,
            10.5f, 0.5f, coords.Px, coords.Py,
            10.5f, 21.5f, coords.Px, coords.Ny
        };

        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices.data(), GL_STATIC_DRAW);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(SQUARE_INDICES), SQUARE_INDICES.data(), GL_STATIC_DRAW);

        set_vertex_layout();

        unbind();
    }
}

void dim::draw()
{
    if (to_draw_)
    {
        bind();
        glDrawElements(GL_TRIANGLES, SQUARE_INDICES.size(), GL_UNSIGNED_INT, nullptr);
        unbind();
    }
}

}
