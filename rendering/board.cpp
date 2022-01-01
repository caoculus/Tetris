#include "board.hpp"
namespace mesh
{

board::board(sampler &sampler, const board_t &board)
    : mesh(sampler), board_(board)
{
    update();
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

            std::size_t begin_index = vertices_.size();
            auto coords = sampler_("piece", static_cast<std::size_t>(board_[y][x]));

            for (const auto &index : SQUARE_INDICES)
                indices_.push_back(begin_index + index);

            vertices_.insert(vertices_.end(), {
                x + 0.0f, y + 0.0f, coords.Nx, coords.Ny,
                x + 0.0f, y + 1.0f, coords.Nx, coords.Py,
                x + 1.0f, y + 0.0f, coords.Px, coords.Ny,
                x + 1.0f, y + 1.0f, coords.Px, coords.Py
            });
        }
    }
}

}