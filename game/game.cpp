#include "game.hpp"

void tetris::tick()
{
    // acquire inputs
    shift_t p_shift, shift;
    rotation_t p_rotation, rotation;
    keys.get(p_shift, p_rotation);
    keys.update();
    keys.get(shift, rotation);

    if (state > 30) // line clear state. do nothing.
    {
        update_counters();
        return;
    }
    if (state > 0) // wait for piece state. check for das.
    {
        const bool reset_das = p_shift == shift and shift != shift_t::none;
        update_counters();
        return;
    }
    if (state == 0) // exceptional state
    {
        update_counters();
        return;
    }

    // perform translation
    if (das < 0)
    {
        active_piece.translate(shift);
    }

}

int tetris::time() const noexcept 
{ 
    return -clk;
}

square tetris::next() const noexcept
{
    return rng.next();
}

const board_t &tetris::b() const noexcept
{
    return board;
}

void tetris::update_counters(bool line_clear, bool piece_lock)
{
    --clk;
    
    if (line_clear)
        state = ARE + CLEAR;
    else if (piece_lock)
        state = ARE;
    else 
        --state;

    if (piece_lock)
        lock = LOCK;
    else
        --lock;
    

}