#include "shutthebox.hpp"

#include <iostream>

std::string ShutTheBox::tile_index_to_string(const tile_index_t tile_index)
{
    return std::to_string(tile_index + 1);
}

void ShutTheBox::parse_input(const std::string &input, std::vector<tile_index_t> &move)
{
    for (char c : input)
        {
            if (c >= '1' && c <= '9')
            {
                move.push_back(c - '1');
            }
        }
}

void ShutTheBox::play_turn(const dice_roll_t roll)
{
    while (true)
    {
        // Get Player Input
        std::string input;
        io.get_input(input);
        std::vector<tile_index_t> move;
        //   Parse the input
        parse_input(input, move);

        // Check if the move is valid
        //  All tiles in the move must be available
        //  The sum of the tiles in the move must be equal to the roll
        score_t move_sum = 0;
        for (tile_index_t i : move)
        {
            if (is_flipped(i)) // Invalid Move (tile is already flipped)
            {
                std::cout << INVALID_MOVE_MESSAGE;
                continue;
            }
            move_sum += i + 1;
        }
        if (move_sum != roll) // Invalid Move (sum of tiles is not equal to the roll)
        {
            std::cout << INVALID_MOVE_MESSAGE;
            continue;
        }
        // Play the move (flip the tiles)
        for (tile_index_t i : move)
        {
            tiles[i] = true;
        }
        break;
    }
}

std::vector<ShutTheBox::tile_config_t> ShutTheBox::get_possible_moves(dice_roll_t roll) const
{
    const std::vector<std::vector<tile_index_t>> all_possible_moves[11] = // All possible moves for each possible roll. Tile identifiers are values, not indexes (must subtract 1 to get the index)
    {
        {{0,0},{1}}, // 2
        {{0,1},{2}}, // 3
        {{0,2},{3}}, // 4
        {{0,3},{1,2},{4}}, // 5
        {{0,4},{1,3},{5},{0,1,2}}, // 6
        {{0,5},{1,4},{2,3},{6},{0,1,3}}, // 7
        {{0,6},{1,5},{2,4},{7},{0,1,4},{0,2,3}}, // 8
        {{0,7},{1,6},{2,5},{3,4},{8},{0,1,5},{0,2,4},{1,2,3}}, // 9
        {{0,8},{1,7},{2,6},{3,5},{0,1,6},{0,2,5},{0,3,4},{1,2,4},{0,1,2,3}}, // 10
        {{1,8},{2,7},{3,6},{4,5},{0,1,7},{0,2,6},{0,3,5},{1,2,5},{1,3,4},{0,1,2,4}}, // 11
        {{2,8},{3,7},{4,6},{0,1,8},{0,2,7},{0,3,6},{0,4,5},{1,2,6},{1,3,5},{0,1,2,5},{0,1,3,4},{2,3,4}}, // 12
    };

    std::vector<tile_config_t> moves;
    for (const std::vector<tile_index_t>& move : all_possible_moves[roll - 2])
    {
        tile_config_t move_config;
        for (tile_index_t i : move) // Convert the move to a tile_config_t
        {
            move_config[i] = true;
        }
        if (flippable_move(move_config)) // Check if the move is flippable
        {
            moves.push_back(move_config); // Add the move to the list of possible moves
        }
    }
    return moves;
}

bool ShutTheBox::is_flipped(tile_index_t tile) const
{
    return tiles[tile];
}

bool ShutTheBox::flippable_move(tile_config_t move) const
{
    for (tile_index_t i = 0; i < 9; i++)
    {
        if (move[i]) // If the tile is in the move
        {
            if (is_flipped(i)) // If the tile is already flipped
            {
                return false; // The move is not flippable
            }
        }
    }
    return true; // The move is flippable
}

void ShutTheBox::calculate_score()
{
    this->score = 0;
    for (tile_index_t i = 0; i < 9; i++)
    {
        if (!is_flipped(i))
        {
            score += i + 1;
        }
    }
}

ShutTheBox::dice_roll_t ShutTheBox::roll_dice()
{
    return dice.roll();
}

ShutTheBox::ShutTheBox() :
    tiles(0), // All tiles are initially available (false)
    dice(),
    io(),
    score(MAX_SCORE) // The initial score is the sum of all the tiles
{
}

ShutTheBox::~ShutTheBox()
{
}

void ShutTheBox::play()
{
    io.clear_console(); // Clear the console
    while(true) {
        // Roll the dice
        dice_roll_t roll1 = roll_dice();
        dice_roll_t roll2 = roll_dice();
        dice_roll_t roll = roll1 + roll2;

        // Display
        //  Tiles & Score
        io.push(AVAILABLE_TILES_MESSAGE);
        for (tile_index_t i = 0; i < 9; i++)
        {
            if (!is_flipped(i))
            {
                io.push(tile_index_to_string(i));
                io.push(" ");
            }
        }
        io.get_output_buffer().pop_back(); // Remove the trailing space
        io.push("\n");
        io.push(SCORE_MESSAGE);
        io.push(std::to_string(score));
        io.push("\n");
        //  Roll
        io.push(ROLL_MESSAGE);
        //   Display the sum of the dice
        io.push(std::to_string(roll));
        //   Display the individual dice rolls
        io.push("(");
        io.push(std::to_string(roll1));
        io.push(", ");
        io.push(std::to_string(roll2));
        io.push(")");
        io.push("\n");

        io.flush(); // Flush the output buffer to the console

        // Check if the game is over
        //  Get possible moves
        std::vector<tile_config_t> moves = get_possible_moves(roll);
        //  If there are no possible moves, the game is over
        if (moves.empty())
        {
            io.push(GAME_OVER_MESSAGE);
            // Game Loss Message
            io.push(LOSS_MESSAGE);
            // Display the final score
            io.push(SCORE_MESSAGE);
            io.push(std::to_string(score));
            io.push("\n");
            break;
        }

        // Play the turn
        play_turn(roll);

        // Calculate the score
        calculate_score();
        if (score == 0) // Victory condition (all tiles are flipped)
        {
            io.push(GAME_OVER_MESSAGE);
            // Game Win Message
            io.push(WIN_MESSAGE);
            break;
        }
    }
    io.flush(); // Flush the output buffer to the console
}
