#include "game.hpp"

void tetris::tick()
{
    if (state >= 0)
    {
        update_counters();
        if (state > 0)
        {
            keys.update_shift();
            keys.update_rotation();
        }
        if (state == 30)
        {
            for (std::size_t src = board.size() - 1, dest = board.size() - 1;
                 src > 0;)
            {
                if (board[src][0] == square::clear)
                    src--;
                board[dest--] = board[src--];
            }
        }
        return;
    }
    // acquire inputs
    shift_t shift = keys.update_shift();
    rotation_t rotation = keys.update_rotation();

    // perform translation
    active_piece.rotate(rotation);
    active_piece.translate(shift);

    switch (active_piece.tick(level.g()))
    {
        case locking_state::tick:
            update_counters(false, false, true);
            break;
        case locking_state::reset:
            update_counters(false, true, false);
            break;
        case locking_state::none:
            update_counters();
            break;
        default:
            break;
    }

    // check for line clears
    for (auto &row: board)
    {
        // find first element where is_empty is true
        if (std::find_if(row.begin(), row.end(), is_empty) == row.end())
        {
            // clear the row
            std::fill(row.begin(), row.end(), square::clear);
            update_counters(true);
        }
    }
}

int tetris::time() const noexcept
{
    return clk;
}

square tetris::next() const noexcept
{
    return rng.next();
}

const board_t &tetris::b() const noexcept
{
    return board;
}

void tetris::update_counters(bool line_clear, bool fall1, bool land)
{
    ++clk;

    if (line_clear)
        state = ARE + CLEAR;
    else if (lock == 0)
        state = ARE;
    else
        --state;

    if (fall1)
        lock = LOCK;
    else if (land)
        --lock;
}
