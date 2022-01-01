#include <GL/glew.h>
#include "frame.hpp"

namespace mesh {

frame::frame(sampler &sampler, const GLFWvidmode *mode)
    : mesh(sampler)
{
    bind();
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(SQUARE_INDICES), SQUARE_INDICES.data(), GL_STATIC_DRAW);
    auto coords = sampler_("frame");

    int width  = mode->width    * 3;
    int height = mode->height   * 4;

    float x = height > width ? 1.0f : (float)height / (float)width;
    float y = width > height ? 1.0f : (float)width / (float)height;

    vertices_ = {
        -x, -y, coords.Nx, coords.Ny,
        -x, y, coords.Nx, coords.Py,
        x, -y, coords.Px, coords.Ny,
        x, y, coords.Px, coords.Py
    };

    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices_), vertices_.data(), GL_STATIC_DRAW);
    set_vertex_layout();
    unbind();
}

void frame::draw()
{
    bind();
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
    unbind();
}

}