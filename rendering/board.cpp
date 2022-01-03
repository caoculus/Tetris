#include <GL/glew.h>
#include "board.hpp"
namespace mesh
{

board::board(sampler &sampler, const board_t &board)
    : mesh(sampler), board_(board)
{
    update();
    bind();
    set_vertex_layout();
    unbind();
}

void board::draw()
{
    if (indices_.empty())
        return;

    bind();
    glDrawElements(GL_TRIANGLES, indices_.size(), GL_UNSIGNED_INT, nullptr);
    unbind();
}

void board::update()
{
    vertices_.clear();
    indices_.clear();

    for (int y = 0; y < board_.size(); ++y)
    {
        for (int x = 0; x < board_[y].size(); ++x)
        {
            if (board_[y][x] == square::none)
                continue;

            std::size_t begin_index = vertices_.size() / 4;
            auto coords = sampler_("clear");

            if (board_[y][x] != square::clear)
                coords = sampler_("piece", static_cast<std::size_t>(board_[y][x]));

            for (const auto &index : SQUARE_INDICES)
                indices_.push_back(begin_index + index);

            vertices_.insert(vertices_.end(), {
                x + 0.f, y + 0.f, coords.Nx, coords.Py,
                x + 0.f, y + 1.f, coords.Nx, coords.Ny,
                x + 1.f, y + 0.f, coords.Px, coords.Py,
                x + 1.f, y + 1.f, coords.Px, coords.Ny
            });
        }
    }
    
    bind();
    glBufferData(GL_ARRAY_BUFFER, vertices_.size() * sizeof(float), vertices_.data(), GL_DYNAMIC_DRAW);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices_.size() * sizeof(unsigned int), indices_.data(), GL_DYNAMIC_DRAW);
    unbind();
}

}
