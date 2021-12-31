#include <GL/glew.h>
#include "frame.hpp"

frame::frame(sampler &__sampler, const GLFWvidmode *mode)
    : mesh(__sampler)
{
    bind();
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices_), indices_.data(), GL_STATIC_DRAW);
    auto coords = sampler_("frame");

    int width  = mode->width    * 3;
    int height = mode->height   * 4;

    float X = height > width ? 1.0f : (float)height / (float)width;
    float Y = width > height ? 1.0f : (float)width / (float)height;

    vertices_ = {
        -X, -Y, coords.Nx, coords.Ny,
        -X,  Y, coords.Nx, coords.Py,
        X,  -Y, coords.Px, coords.Ny,
        X,   Y, coords.Px, coords.Py
    };

    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices_), vertices_.data(), GL_STATIC_DRAW);
    set_vertex_layout();
    unbind();
}

void frame::draw() const
{
    bind();
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
    unbind();
}
