#include "game/level.hpp"
#include "level.hpp"
#include <iostream>
#include <cassert>

int main(int argc, char **argv)
{
    game::level_counter l1, l2, l3, l4;
    l2 += 199;
    l3 += 298;
    l4 += 998;

    // start at level 0 and g being 2
    assert(l1 == 0);
    assert(l1.g() == 2);

    // ensure g changes properly with change in level more than one step
    assert(l2 == 199);
    assert(l2.g() == 72);
    
    // ensure nothing has changed
    l2++;
    assert(l2 == 199);
    assert(l2.g() == 72);

    // advance to next level
    l2 += 1;
    assert(l2 == 200);
    assert(l2.g() == 2);

    l3 += 4;
    assert(l3 == 302);
    assert(l3.g() == 256);

    l4 ++;
    assert(l4 == 998);

    l4 += 4;

    assert(l4 == 999);
    assert(l4.g() == 2560);

    return 0;
}
