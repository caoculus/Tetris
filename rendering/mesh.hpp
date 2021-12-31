#pragma once

class mesh
{
public:
    mesh();

    virtual void draw() const = 0;

protected:
    unsigned int ibo {}, vbo {};

    void set_vertex_layout();

    void bind() const;
    void unbind() const;
};