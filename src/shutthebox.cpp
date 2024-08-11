#include "shutthebox.hpp"

void ShutTheBox::play_turn(const dice_roll_t roll)
{
    // Get Player Input
    // Check if the move is valid
    //  All tiles in the move must be available
    //  The sum of the tiles in the move must be equal to the roll
    // Play the move (flip the tiles)
}

ShutTheBox::ShutTheBox() :
    tiles(0), // All tiles are initially available (false)
    dice(),
    score(1 + 2 + 3 + 4 + 5 + 6 + 7 + 8 + 9) // The initial score is the sum of all the tiles
{
}

ShutTheBox::~ShutTheBox()
{
}

void ShutTheBox::play()
{
    while(true) {
        // Roll the dice
        dice_roll_t roll = roll_dice();

        // Display
        //  Tiles & Score
        //  Roll

        // Check if the game is over
        //  Get possible moves
        std::vector<tile_config_t> moves = get_possible_moves(roll);
        //  If there are no possible moves, the game is over
        if (moves.empty())
        {
            // Game Loss Message
            break;
        }

        // Play the turn
        play_turn(roll);

        // Calculate the score
        score = calculate_score();
        if (score == 0) // Victory condition (all tiles are flipped)
        {
            // Game Win Message
            break;
        }
    }
}
