#pragma once

#include "sampler.hpp"

namespace mesh {

/**
 * @brief The array to store the vertices for drawing quadralaterals with the
 * vertex layout used for all draws in this game.
 * 
 * @tparam QUADS number of quadralaterals.
 * 
 * @details The vertex layout is {x (pos), y (pos), u (tex), v (tex)} using 
 * single-precision floating point values for each component.
 */
template <std::size_t QUADS>
using quad_vertices = std::array<float, QUADS*16>;

/**
 * @brief Indices for drawing quadralaterals using two triangles in OpenGL.
 * 
 * @tparam QUADS number of quadralaterals.
 * 
 * @details The indices are stored in a std::array. Each quad has two triangles
 * hence 6 indices. The indices are {0, 1, 2, 1, 2, 3} for the first quad, and
 * offset by 4 each time for subsequent quads.
 */
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
     * <ul>
     * <li> x, y: The position of the vertex. </li>
     * <li> u, v: The texture coordinates of the vertex. </li>
     * </ul>
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
