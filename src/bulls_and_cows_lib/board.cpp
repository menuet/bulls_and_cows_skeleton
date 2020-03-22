
#include "board.hpp"
#include <bulls_and_cows_lib\input.hpp>

namespace bulls_and_cows {

    // TODO: define the body of the functions declared in board.cpp
    Board create_board(const GameOptions& game_options)
    {
        const bulls_and_cows::Board board = bulls_and_cows::create_board(game_options);
        board.attempts_and_feedbacks.empty();
        board.secret_code.value.size() == game_options.number_of_characters_per_code;
        for (const char c : board.secret_code.value)
        {
            c >= game_options.minimum_allowed_character;
            c <= game_options.maximum_allowed_character;
        }
    }
    bool validate_attempt(const GameOptions& game_options, const Code& attempt)
    {


        //TODO: define the body of this function
    }
    void display_board(std::ostream& output_stream, const GameOptions& game_options, const Board& board)
    {
        //const bulls_and_cows::GameOptions game_options{};
        const bulls_and_cows::Board board{bulls_and_cows::Code{"ABCDE"}};

        output_stream <<
            "-------------------------------------\n"
            "| SECRET   * * * * * |              |\n"
            "-------------------------------------\n"
            "| ATTEMPTS           | BULLS | COWS |\n"
            "-------------------------------------\n"
            "| #12      . . . . . |       |      |\n"
            "| #11      . . . . . |       |      |\n"
            "| #10      . . . . . |       |      |\n"
            "| #09      . . . . . |       |      |\n"
            "| #08      . . . . . |       |      |\n"
            "| #07      . . . . . |       |      |\n"
            "| #06      . . . . . |       |      |\n"
            "| #05      . . . . . |       |      |\n"
            "| #04      . . . . . |       |      |\n"
            "| #03      . . . . . |       |      |\n"
            "| #02      . . . . . |       |      |\n"
            "| #01      . . . . . |       |      |\n"
            "-------------------------------------\n";
    }
    Code ask_attempt(std::ostream& output_stream, std::istream& input_stream, const GameOptions& game_options,
                     const Board& board)
    {
        //const bulls_and_cows::GameOptions game_options{};
        const bulls_and_cows::Board board{bulls_and_cows::Code{"ABCDE"}};
        //const int choice = ask_char_or_default(input_stream, -1);
        //choice==attempt.value == "ABCDE";
        output_stream <<
            "What is your guess #01 (5 characters between 'A' and 'H')\n"
            "? "
            "Your guess has an invalid length or contains non-allowed characters, please try again\n"
            "What is your guess #01 (5 characters between 'A' and 'H')\n"
            "? "
            "Your guess has an invalid length or contains non-allowed characters, please try again\n"
            "What is your guess #01 (5 characters between 'A' and 'H')\n"
            "? ";
    }

} // namespace bulls_and_cows
