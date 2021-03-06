#include "game.hpp"
#include "level.hpp"
#include <iostream>
#include <algorithm>

void game::tetris::tick()
{
    if (game_over_)
    {
        throw game_over_exception();
    }

    if (state_ == state_t::spawn)
    {
        spawn_piece();
        if (clk_ != 0)
        {
            ++level_;
        }
    }
    else if (state_ == state_t::active)
    {
        move_piece();
    }
    else
    {
        wait_delay();
    }
    
    if (level_ == 300 and (clk_ > (4*3600+15*60) or score_ < 12000)
    or  level_ == 500 and (clk_ > (7*3600)       or score_ < 40000)
    or  level_ == 999 and (clk_ >(13*3600+30*60) or score_ < 126000))
        GM_possible = false;
    

    if (level_ < 999)
        ++clk_;
    else if (GM_possible)
        grade_ = 18;
}

inline void game::tetris::wait_delay()
{
    // update shift to track DAS except on frame before piece spawn (to
    // emulate TGM)
    if (state_ == state_t::are)
    {
        keys_.update_shift();
    }

    ++frame_num_;

    switch (state_)
    {
        case state_t::flash:
            if (frame_num_ == FLASH)
            {
                state_ = state_t::dim;
                frame_num_ = 0;
            }
            break;
        case state_t::dim:
            state_ = line_clear_ ? state_t::clear : state_t::are;
            break;
        case state_t::are:
            if (frame_num_ == ARE)
            {
                state_ = state_t::spawn;
                frame_num_ = 0;
            }
            break;
        case state_t::clear:
            if (frame_num_ == CLEAR)
            {
                drop_lines();
                state_ = state_t::are;
                frame_num_ = 0;
            }
        default:
            break;
    }
}

inline void game::tetris::drop_lines()
{
    for (std::size_t src = board_.size() - 1, dest = board_.size() - 1;
         dest != -1;)
    {
        if (src == -1)
        {
            std::fill(board_[dest].begin(), board_[dest].end(), square::none);
            --dest;
        }
        else if (board_[src][0] == square::clear)
        {
            --src;
        }
        else
        {
            board_[dest--] = board_[src--];
        }
    }

    line_clear_ = false;

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
        draw_piece();
        game_over_ = true;
        return;
    }

    // otherwise, move down according to spawn gravity
    uint16_t g = level_.g();
    uint16_t spawn_g = (g >= level_counter::DENOM) ? g : 0;

    // tick piece and set state to active (frame_num_ is already 0)
    active_piece_.tick(spawn_g);
    state_ = state_t::active;

    // reset the lines dropped
    dropped_ = 0;
}

inline void game::tetris::move_piece()
{
    // acquire inputs
    shift_t shift = keys_.update_shift();
    rotation_t rotation = keys_.update_rotation();

    // perform translation
    active_piece_.rotate(rotation);
    active_piece_.translate(shift);

    bool soft_drop = (shift == shift_t::down);
    // effective gravity
    uint16_t g = std::max(level_.g(),
        static_cast<uint16_t>(128 * soft_drop));

    // update the lines dropped if soft drop
    dropped_ += soft_drop * g / 128;

    // update frame_num_
    auto tick_result = active_piece_.tick(g);

    if (static_cast<bool>(tick_result & locking_state::reset))
    {
        frame_num_ = 0;
    }
    if (static_cast<bool>(tick_result & locking_state::tick))
    {
        (shift == shift_t::down) ? frame_num_ = LOCK : ++frame_num_;
    }
    
    // if piece locks
    if (frame_num_ == LOCK)
    {
        draw_piece();
        clear_lines();
        state_ = state_t::flash;
        frame_num_ = 0;
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
    
        combo_ += 2 * num_cleared - 2;

        score_ += (dropped_ + (3 + level_ + num_cleared) / 4) * num_cleared * combo_;
        
        while (score_ > GRADES[grade_])
        {
            ++grade_;
        }
    }
    else
    {
        combo_ = 1;
    }
}
