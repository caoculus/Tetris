#include "game.hpp"
#include "level.hpp"
#include <iostream>

std::ostream &game::operator<<(std::ostream &os, const game::piece &p)
{
    os << "piece(" << p.pos_.y << "," << p.pos_.x << ")";
    return os;
}

void game::tetris::tick()
{
//    // just wait for delay on positive states
//    if (state_ > 0)
//    {
//        wait_delay();
//    }
//    // when state is 0 (spawning frame), try to spawn a piece
//    else if (state_ == 0)
//    {
//        spawn_piece();
//        if (clk_ != 0)
//        {
//            ++level_;
//        }
//    }
//    // normal gameplay when state is -1
//    else
//    {
//        move_piece();
//    }

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

    ++clk_;

//    std::cout << active_piece_ << std::endl;
//    std::cout << "level: " << (int) level_ << std::endl;
//    std::cout << "state: " << state_ << std::endl;
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

//    // jump to line clear animation after flash ends in ARE if line clear
//    if (line_clear_ and state_ == ARE - FLASH + 1)
//    {
//        state_ = ARE + CLEAR;
//    }
//    // drop lines at end of line clear animation and jump to after flash in ARE
//    else if (state_ == ARE + 1)
//    {
//        drop_lines();
//        state_ = ARE - FLASH;
//    }
//    // just decrement otherwise
//    else
//    {
//        --state_;
//    }
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
    }
}
