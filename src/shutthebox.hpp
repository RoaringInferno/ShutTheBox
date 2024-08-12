#pragma once

#include "dice.hpp"
#include "io.hpp"

#include <bitset>
#include <vector>
#include <string>

class ShutTheBox
{
    /**
     * A tile's state can be represented by a boolean value.
     * The boolean's value is true if the tile is flipped (unavailable), and false if it is not (can still be flipped).
     * The tiles are indexed from 0-8, but are displayed to the player from 1-9.
     */
public: // Typedefs
    typedef unsigned char tile_index_t; // Represents the index of a tile.
    typedef unsigned char score_t; // Represents the score of the player
    typedef unsigned char dice_roll_t; // Represents the result of a dice roll
    typedef std::bitset<9> tile_config_t; // Represents a configuration of tiles
private: // Constants
    const score_t MAX_SCORE = 45; // The maximum score possible

    const std::string INVALID_MOVE_MESSAGE = "Invalid Move!\n"; // The message to display when an invalid move is made
    const std::string LOSS_MESSAGE = ""; // The message to display when the player loses
    const std::string WIN_MESSAGE = "You Win!\n"; // The message to display when the player wins
    const std::string SCORE_MESSAGE = "Score: "; // The message to display the score
    const std::string ROLL_MESSAGE = "Roll: "; // The message to display the dice roll
    const std::string MOVE_MESSAGE = "Move: "; // The message to display the move
    const std::string GAME_OVER_MESSAGE = "Game Over; "; // The message to display when the game is over
    const std::string AVAILABLE_TILES_MESSAGE = "Available Tiles: "; // The message to display the available tiles
private: // Private Members
    IO io; // The IO object used to interact with the player
    tile_config_t tiles; // The current configuration of tiles
    d6 dice; // The dice used in the game
    score_t score; // The score of the player
private: // Private Static Methods
    static std::string tile_index_to_string(const tile_index_t tile_index); // Convert the tile indices to a string
    static void parse_input(const std::string& input, std::vector<tile_index_t>& move); // Parse the input into a move
private: // Private Methods
    void play_turn(const dice_roll_t roll); // Play a turn of the game with a given dice roll

    std::vector<tile_config_t> get_possible_moves(dice_roll_t) const; // Get all possible moves for the player
    bool is_flipped(tile_index_t tile) const; // Check if a tile is flipped
    bool set_tile(tile_index_t tile, bool value); // Set the state of a tile
    bool flippable_move(tile_config_t move) const; // Check if a move is able to be flipped
    void calculate_score(); // Calculate the score of the player
    dice_roll_t roll_dice(); // Roll the dice (2d6)
public: // Public Methods
    ShutTheBox();
    ~ShutTheBox();

    void play(); // Start the game loop

    score_t get_score() const; // Get the score of the player
};