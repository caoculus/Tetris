#include "game.hpp"
#include "level.hpp"
#include <iostream>

std::ostream& game::operator<<(std::ostream& os, const game::piece &p) {
    os << "piece(" << p.pos_.y << "," << p.pos_.x << ")";
    return os;
}

void game::tetris::tick()
{
    ++clk_;

    // just wait for delay on positive states
    if (state_ > 0)
    {
        wait_delay();
    }
    // when state is 0 (spawning frame), try to spawn a piece
    else if (state_ == 0)
    {
        spawn_piece();
    }
    // normal gameplay when state is -1
    else
    {
        move_piece();
    }

//    std::cout << active_piece_ << std::endl;
}

inline void game::tetris::wait_delay()
{
    // update shift to track DAS except on frame before piece spawn (to
    // emulate TGM)
    if (state_ > 1 and state_ <= ARE)
    {
        keys_.update_shift();
    }

    // jump to line clear animation after flash ends in ARE if line clear
    if (line_clear_ and state_ == ARE - FLASH + 1)
    {
        state_ = ARE + CLEAR;
    }
    // drop lines at end of line clear animation and jump to after flash in ARE
    else if (state_ == ARE + 1)
    {
        drop_lines();
        state_ = ARE - FLASH;
    }
    // just decrement otherwise
    else
    {
        --state_;
    }
}

inline void game::tetris::drop_lines()
{
    for (std::size_t src = board_.size() - 1, dest = board_.size() - 1;
         src > 0;)
    {
        if (board_[src][0] == square::clear)
            src--;
        else
            board_[dest--] = board_[src--];
    }

    update_board_ = true;
}

inline void game::tetris::spawn_piece()
{
    // get the translation, but don't use it
    // call the rotation with spawn_frame = true
    keys_.update_shift();
    rotation_t rotation = keys_.update_rotation(true);

    // game over if the piece can't spawn
    if (!active_piece_.spawn(rng_(), rotation))
    {
        throw game_over_exception();
    }

    // otherwise, move down according to spawn gravity
    uint16_t g = level_.g();
    uint16_t spawn_g = (g >= level_counter::DENOM) ? g : 0;

    // tick piece and update lock_ if touching stack
    // otherwise reset lock_
    if (active_piece_.tick(spawn_g) == locking_state::tick)
    {
        --lock_;
    }
    else
    {
        lock_ = LOCK;
    }

    --state_;
}

inline void game::tetris::move_piece()
{
    // acquire inputs
    shift_t shift = keys_.update_shift();
    rotation_t rotation = keys_.update_rotation();

    // perform translation
    active_piece_.rotate(rotation);
    active_piece_.translate(shift);

    // effective gravity
    uint16_t g = std::max(level_.g(),
        static_cast<uint16_t>(128 * (shift == shift_t::down)));

    // update lock_
    switch (active_piece_.tick(g))
    {
        case locking_state::tick:
            (shift == shift_t::down) ? lock_ = 0 : --lock_;
            break;
        case locking_state::reset:
            lock_ = LOCK;
            break;
        case locking_state::none:
            break;
    }

    // if piece locks
    if (lock_ == 0)
    {
        draw_piece();
        clear_lines();
        lock_ = LOCK;
        state_ = ARE;
    }
}

inline void game::tetris::draw_piece()
{
    for (auto &[y, x]: active_piece_.piece_squares())
    {
        board_[y][x] = active_piece_.type();
    }

    update_board_ = true;
}

inline void game::tetris::clear_lines()
{
    int num_cleared = 0;

    for (auto &row: board_)
    {
        // find first element where is_empty is true
        if (std::find_if(row.begin(), row.end(), is_empty) ==
            row.end())
        {
            // clear the row
            std::fill(row.begin(), row.end(), square::clear);
            ++num_cleared;
        }
    }

    // update level based on num_cleared and set line clear flag
    if (num_cleared > 0)
    {
        line_clear_ = true;
        level_ += num_cleared;
        update_board_ = true;
    }
    else
    {
        ++level_;
    }
}
