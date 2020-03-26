
#include "board.hpp"
#include <bulls_and_cows_lib\input.hpp>
#include <bulls_and_cows_lib\random.hpp>
using namespace bulls_and_cows;

namespace bulls_and_cows {

    // TODO: define the body of the functions declared in board.cpp
    Board create_board(const GameOptions& game_options)
    {
        Board gameboard{};
        gameboard.secret_code.value.resize(game_options.number_of_characters_per_code);// else we are out of range
        for(unsigned int i = 0; i < game_options.number_of_characters_per_code; i++)
        {
            gameboard.secret_code.value[i] = generate_random_character(game_options.minimum_allowed_character,
                                                                            game_options.maximum_allowed_character);

        }
        return gameboard;

      
    }
    bool validate_attempt(const GameOptions& game_options, const Code& attempt)
    {
        if (game_options.number_of_characters_per_code == attempt.value.size())
        {
            for (const char &c : attempt.value)
            {
                if (c < game_options.minimum_allowed_character || c > game_options.maximum_allowed_character)//checking if the user-entered character is out of 
                {
                    return false;
                }
            }
        }
        else
        {
            return false;
        }
        return true;
    }
    bool is_end_of_game(const GameOptions& game_options, const Board& board)
    {
        if (board.attempts_and_feedbacks.size()==game_options.maximum_allowed_character) //the space for attempts is full 
        {
            std::cout << " GAME OVER ! Is the end of game \n";
            std::cout << " The secret was : " + board.secret_code.value;
            return true;
        }
        else
        {
            return false;
        }
    }
    bool is_win(const GameOptions& game_options, const Board& board)
    {
        if (board.attempts_and_feedbacks.back().attempt.value== board.secret_code.value)//"end.() -->reference to the last element entered "
        {
            std::cout << " YOU WON !";
            return true;
        }
        else if (board.attempts_and_feedbacks.empty())
        {
            return false;
        }
        return false;

    }
    Code ask_attempt(std::ostream& output_stream, std::istream& input_stream, const GameOptions& game_options,
                     const Board& board)
    {
        Code attempt;
        while (!validate_attempt(game_options, attempt) && output_stream << game_options.maximum_allowed_character)
        {
                output_stream << "Can you provide another string please";
                input_stream >> attempt.value;
        }
        return attempt;
    }



    void display_board(std::ostream& output_stream, const GameOptions& game_options, const Board& board)
    {

        if (board.attempts_and_feedbacks.empty()) //case when the user has not yet played
        {
            output_stream << "-------------------------------------\n"
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
        else
        {
            output_stream << "" << board.secret_code.value << "\n";
           for (unsigned int i = 0; i < board.attempts_and_feedbacks.size(); i++)
            {
               const auto attempt_user = board.attempts_and_feedbacks.back().attempt.value;
               output_stream << "| #" << (i + 1) << " :" << attempt_user << "\n";
            }
               
        }
    }
   

} // namespace bulls_and_cows
