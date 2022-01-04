#pragma once

#include "mesh.hpp"
namespace mesh
{

class dim : public mesh
{
public:
    dim(sampler &sampler, std::size_t dim);

    void draw() override;
private:
    bool to_draw_;
};

}