#include "mesh.hpp"
#include <GL/glew.h>

mesh::mesh(sampler &__sampler) 
    : sampler_(__sampler) 
{
    glGenBuffers(1, &ibo);
    glGenBuffers(1, &vbo);
}

mesh::~mesh() 
{
    glDeleteBuffers(1, &ibo);
    glDeleteBuffers(1, &vbo);
}

void mesh::set_vertex_layout()
{
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), nullptr);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float),
                          (void *)(2 * sizeof(float)));
    glEnableVertexAttribArray(1);
}

void mesh::bind() const
{
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
}

void mesh::unbind() const
{
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
