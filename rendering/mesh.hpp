#pragma once

#include "sampler.hpp"

namespace mesh {
class mesh
{
public:
    virtual ~mesh();

    virtual void draw() = 0;

protected:
    unsigned int ibo {}, vbo {}, vao {};
    sampler &sampler_;

    mesh(sampler &sampler);

    void set_vertex_layout();

    void bind() const;
    void unbind() const;
};

}