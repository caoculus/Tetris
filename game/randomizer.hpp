#pragma once

#include "common.hpp"
#include <random>
#include <deque>

/**
 * @brief Randomizer class that controls the sequence of pieces to be spawned.
 * 
 * @details uses the MT19937 random number generator to generate the sequence of 
 * pieces. The pieces generated are not completely random, but comply with the
 * TGM rules. The first piece is generated to prevent overhangs, and the random
 * number generator will attempt to generate new pieces that are different from
 * the previous 4 pieces.
 */
class randomizer
{
public:
    randomizer();

    /**
     * @brief return the next piece and generate a new next piece and update the
     * RNG state. 
     * 
     * @details The randomizer will attempt four times to generate a piece that 
     * is not in the history. If it fails to do so, then it will return a random
     * piece.
     * 
     * @return the next piece
     */
    square operator()();

    /**
     * @brief return the next piece to be displayed on the "Next" section of the
     * screen. 
     * 
     * @return the next square that will be generated.
     */
    [[nodiscard]] square next() const noexcept;

private: 
    std::mt19937 rng {std::random_device{}()};
    
    /**
     * @brief There are seven pieces in total. 
     * 
     */
    std::uniform_int_distribution<int> dist {1, 7};

    /**
     * @brief Four pieces in the history, which are discriminated against for 
     * generating the next piece.
     * 
     * @details The pieces start off with four Z pieces at the beginning.  
     * 
     */
    std::deque<square> history;

    /**
     * @brief The next piece to return when asked for a piece. 
     */
    square next_piece;
};