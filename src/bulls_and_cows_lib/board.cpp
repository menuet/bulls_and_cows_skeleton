
#include "board.hpp"
#include <bulls_and_cows_lib\input.hpp>

namespace bulls_and_cows {

    // TODO: define the body of the functions declared in board.cpp
    Board create_board(const GameOptions& game_options)
    {
        Board gameboard{};
        //return gameboard;
    }
    bool validate_attempt(const GameOptions& game_options, const Code& attempt)
    {
        if (game_options.number_of_characters_per_code == attempt.value)
        {
        } return true;
    }
    void display_board(std::ostream& output_stream, const GameOptions& game_options, const Board& board)
    {
        output_stream 
           << "-------------------------------------\n"
           << "| SECRET   * * * * * |              |\n"
           << "-------------------------------------\n"
           << "| ATTEMPTS           | BULLS | COWS |\n"
           << "-------------------------------------\n"
           << "| #12      . . . . . |       |      |\n"
           << "| #11      . . . . . |       |      |\n"
           << "| #10      . . . . . |       |      |\n"
           << "| #09      . . . . . |       |      |\n"
           << "| #08      . . . . . |       |      |\n"
           << "| #07      . . . . . |       |      |\n"
           << "| #06      . . . . . |       |      |\n"
           << "| #05      . . . . . |       |      |\n"
           << "| #04      . . . . . |       |      |\n"
           << "| #03      . . . . . |       |      |\n"
           << "| #02      . . . . . |       |      |\n"
           << "| #01      . . . . . |       |      |\n"
           << "-------------------------------------\n";
    }
    Code ask_attempt(std::ostream& output_stream, std::istream& input_stream, const GameOptions& game_options,
                     const Board& board)
    {
    }

} // namespace bulls_and_cows
