#include "game.hpp"

void tetris::tick()
{
    if (state_ > 0)
    {
        update_counters();
        if (state_ > 1 and state_ <= 30)
        {
            keys_.update_shift();
            keys_.update_rotation();
        }
        if (state_ == 30)
        {
            // line clear animation complete
            for (std::size_t src = board_.size() - 1, dest = board_.size() - 1;
                 src > 0;)
            {
                if (board_[src][0] == square::clear)
                    src--;
                board_[dest--] = board_[src--];
            }
        }
        return;
    }

    if (state_ == 0)
    {
        keys_.update_rotation(true);
        active_piece_.reset(rng_());
    }

    // acquire inputs
    shift_t shift = keys_.update_shift();
    rotation_t rotation = keys_.update_rotation();

    // perform translation
    active_piece_.rotate(rotation);
    active_piece_.translate(shift);

    switch (active_piece_.tick(level_.g()))
    {
        case locking_state::tick: 
            if (shift == shift_t::down or lock_ < 0)
            {
                update_counters(false, true, false);
                for (auto &sq : active_piece_.piece_squares())
                    board_[sq.y_][sq.x_] = active_piece_.ty();
                
                // check for line clears
                for (auto &row: board_)
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
            update_counters(false, false, true); 
            break;
        case locking_state::reset: 
            update_counters(false, true, false); 
            break;
        case locking_state::none: 
            update_counters(); 
            break;
        default: break;
    }

}

int tetris::time() const noexcept
{
    return clk_;
}

square tetris::next() const noexcept
{
    return rng_.next();
}

const board_t &tetris::b() const noexcept
{
    return board_;
}

void tetris::update_counters(bool line_clear, bool fall_1, bool land)
{
    ++clk_;

    if (line_clear)
        state_ = ARE + CLEAR;
    else if (lock_ == 0)
        state_ = ARE;
    else
        --state_;

    if (fall_1)
        lock_ = LOCK;
    else if (land)
        --lock_;
}
