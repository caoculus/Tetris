#pragma once

#include "sampler.hpp"

class mesh
{
public:
    mesh(sampler &__sampler);

    virtual ~mesh();

    virtual void draw() const = 0;

protected:
    unsigned int ibo {}, vbo {};
    sampler &sampler_;

    void set_vertex_layout();

    void bind() const;
    void unbind() const;
};