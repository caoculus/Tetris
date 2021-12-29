#include "game.hpp"

void tetris::update_counters()
{
    --clk;

    if (0 /*something causing das to reset*/)
        das = DAS;
    else if (0 /*something that doesn't cause the das to skip*/)
        --das;
    
    if (0 /*line clear*/)
        state = ARE + CLEAR;
    else if (0 /*after piece locked*/)
        state = ARE;
    else 
        --state;

    if (0 /*piece locked*/)
        lock = LOCK;
    else
        --lock;
    

}