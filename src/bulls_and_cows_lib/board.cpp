
#include "board.hpp"
#include <bulls_and_cows_lib\input.hpp>
#include <bulls_and_cows_lib\random.hpp>
using namespace bulls_and_cows;

namespace bulls_and_cows {

    // TODO: define the body of the functions declared in board.cpp
    Board create_board(const GameOptions& game_options)
    {
        Board gameboard{};
        gameboard.secret_code.value.resize(game_options.number_of_characters_per_code); // else we are out of range
        for (unsigned int i = 0; i < game_options.number_of_characters_per_code; i++)
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
            for (const char& c : attempt.value)
            {
                if (c < game_options.minimum_allowed_character ||
                    c > game_options.maximum_allowed_character) // checking if the user-entered character is out of
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
        if (board.attempts_and_feedbacks.size() ==
            game_options.maximum_allowed_character) // the space for attempts is full
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
        if (board.attempts_and_feedbacks.back().attempt.value ==
            board.secret_code.value) //"back.() -->reference to the last element entered "
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
        const char current_enter = board.attempts_and_feedbacks.size();
        int i;
        while (true)
        {
            output_stream << "Enter a letter to discover the secret code" << current_enter
                          << game_options.number_of_characters_per_code << "" << game_options.maximum_allowed_character
                          << "" << game_options.minimum_allowed_character <<"\n";
            input_stream >> attempt.value;
        }


        return attempt;
    }

    void display_board(std::ostream& output_stream, const GameOptions& game_options, const Board& board)
    {
        output_stream << "-------------------------------------\n"
                      << "| SECRET   * * * * * |              |\n"
                      << "-------------------------------------\n"
                      << "| ATTEMPTS           | BULLS | COWS |\n"
                      << "-------------------------------------\n";

        // if ((board.attempts_and_feedbacks.empty()))
        
        for (unsigned int i = board.attempts_and_feedbacks.size(); i--;) // Unsigned to define the min domain
        {
            if (i > 11)
            {
                const auto attempt_user = board.attempts_and_feedbacks.back().attempt.value;
                output_stream << "| #" << (i + 1) << " :" << attempt_user << "\n";
            }
            else
            {
                output_stream << "| 0" << (i + 1) ;
            }

           // output_stream << "          " << board.attempts_and_feedbacks[i].attempt.value << " |   "
                        //  << (board.attempts_and_feedbacks[i].feedback.bulls) << "   |   "
                        //  << +(board.attempts_and_feedbacks[i].feedback.cows) << "  |\n";
        }

       
        for (int i = game_options.max_number_of_attempts; i > board.attempts_and_feedbacks.size() - 1; i--)
        {
            if (i > 8)
            {
                output_stream << "| #" << (i + 1) <<"      . . . . . |       |      |\n";
            }
            else
            {
                output_stream <<"| #0" <<(i + 1) << "      . . . . . |       |      |\n";
            }
        }

       
    }
        
    }
    Feedback compare_attempt_with_secret_code(const Code& attempt, const Code& secret_code)
    {
        std::string secret = secret_code.value;
        std::string result = attempt.value;
        std::string save; //to stock the user cows
        Feedback feed;
        unsigned COWS = 0, BULLS = 0;

        // For bulls
        for (int i = 0; i < secret.size(); i++)
        {
            //int pos = selection.find(result[i]); if ((pos != std::string::npos))
            if (secret[i] == result[i])
            {
                BULLS++;
                
            }
            else 
            {
               
               save+= result[i];
            }
        }

        //For cows
        for (int i = 0; i < save.size(); i++)
        {
            if (secret.find(save[i]) != std::string::npos && secret[save[i]] > 0)
            {
                COWS++;
                save[i]--;
            }
        }
} // namespace bulls_and_cows
