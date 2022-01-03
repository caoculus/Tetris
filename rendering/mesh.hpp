#pragma once

#include "sampler.hpp"

namespace mesh {

template <std::size_t QUADS>
using quad_vertices = std::array<float, QUADS*16>;

template <std::size_t QUADS>
class quad_indices : public std::array<unsigned int, QUADS*6>
{
public:
    constexpr quad_indices()
    {
        for (std::size_t i {}; i < QUADS; ++i) 
        {
            (*this)[i*6+0] = i*4+0;
            (*this)[i*6+1] = i*4+1;
            (*this)[i*6+2] = i*4+2;
            (*this)[i*6+3] = i*4+1;
            (*this)[i*6+4] = i*4+2;
            (*this)[i*6+5] = i*4+3;
        }
    }
};


/**
 * @brief Any piece of geometry that will be rendered in the game should inherit
 * from this class.
 */
class mesh
{
public:
    /**
     * @brief Destroys the vertex array object and buffer objects.
     */
    virtual ~mesh();

    /**
     * @brief Draw cannot assume any buffers are bound. It should draw the mesh
     * onto the screen assuming all uniforms are set.
     */
    virtual void draw() = 0;

protected:
    /**
     * @brief The OpenGL id of the various buffers.
     */
    unsigned int ibo {}, vbo {}, vao {};

    /**
     * @brief Reference to the sampler with the texture atlas.
     */
    sampler &sampler_;

    /**
     * @brief Create the index buffer object, vertex array object, and vertex
     * buffer object for the mesh.
     * 
     * @param sampler The sampler that is used by the texture atlas load the 
     * texture for the mesh.
     */
    mesh(sampler &sampler);

    /**
     * @brief Set the vertex layout for the mesh. This should be called in the 
     * constructor of the children classes.
     * @requires The vertex array object to be bound.
     * 
     * @details The vertex layout is the following:
     * <list type="bullet">
     * <li> x, y: The position of the vertex.
     * <li> u, v: The texture coordinates of the vertex.
     * </list> 
     */
    void set_vertex_layout();

    /**
     * @brief Bind the vertex array object, vertex buffer object, and index
     * buffer object.
     */
    void bind() const;

    /**
     * @brief Unbind the vertex array object, vertex buffer object, and index
     * buffer object.
     */
    void unbind() const;

    /**
     * @brief Indices (or offsets) for drawing a square.
     */
    static constexpr quad_indices<1> SQUARE_INDICES {};

};

}
