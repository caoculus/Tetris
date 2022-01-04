#pragma once

#include "mesh.hpp"
namespace mesh
{
/**
 * @brief Enables the ability to dim the background to make pieces more visible.
 * 
 * @details The dim is accomplished by drawing a quad behind the background that
 * is the same size as the background. The quad is drawn with a color that is
 * black with a transparency that is determined by the user.
 */
class dim : public mesh
{
public:
    dim(sampler &sampler, std::size_t dim);

    void draw() override;
private:
    /**
     * @brief If no dim is requested, the quad is not drawn.
     */
    bool to_draw_;
};

}