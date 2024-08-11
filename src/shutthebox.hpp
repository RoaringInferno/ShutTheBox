#pragma once

#include "dice.hpp"
#include "io.hpp"

#include <bitset>
#include <vector>

class ShutTheBox
{
    /**
     * A tile's state can be represented by a boolean value.
     * The boolean's value is true if the tile is flipped (unavailable), and false if it is not (can still be flipped).
     */
private: // Typedefs
    typedef unsigned char tile_index_t; // Represents the index of a tile, from 0-8 => 1-9 (both inclusive)
    typedef unsigned char score_t; // Represents the score of the player
    typedef unsigned char dice_roll_t; // Represents the result of a dice roll
    typedef std::bitset<9> tile_config_t; // Represents a configuration of tiles
private: // Private Members
    IO io; // The IO object used to interact with the player
    tile_config_t tiles; // The current configuration of tiles
    d6 dice; // The dice used in the game
    score_t score; // The score of the player
private: // Private Methods
    void play_turn(const dice_roll_t roll); // Play a turn of the game with a given dice roll

    std::vector<tile_config_t> get_possible_moves(dice_roll_t) const; // Get all possible moves for the player
    bool is_flipped(tile_index_t tile) const; // Check if a tile is flipped
    score_t calculate_score() const; // Calculate the score of the player
    dice_roll_t roll_dice() const; // Roll the dice (2d6)
public: // Public Methods
    ShutTheBox();
    ~ShutTheBox();

    void play(); // Start the game loop

    score_t get_score() const; // Get the score of the player
};