
#include "board.hpp"

namespace bulls_and_cows {

    // TODO: define the body of the functions declared in board.cpp
    Board create_board(const GameOptions& game_options)
    {
        //std::vector<char> answer{};
        Board myboard{};

        for (unsigned int i = 0U; i < game_options.number_of_characters_per_code; i++)
        {
            if (game_options.maximum_allowed_character >= 65 && game_options.maximum_allowed_character <= 90 &&
                game_options.minimum_allowed_character >= 65 && game_options.minimum_allowed_character <= 90)
            {
                myboard.secret_code.value = myboard.secret_code.value + bulls_and_cows::generate_random_character(
                                                                    game_options.minimum_allowed_character,
                                                                    game_options.maximum_allowed_character);
            }

            else if (game_options.maximum_allowed_character >= 48 && game_options.maximum_allowed_character <= 57 &&
                     game_options.minimum_allowed_character >= 48 && game_options.minimum_allowed_character <= 57)
            {
                myboard.secret_code.value = myboard.secret_code.value + (char)bulls_and_cows::generate_random_integer(
                                                                    game_options.minimum_allowed_character,
                                                                    game_options.maximum_allowed_character);
            }

            else
            {
            }


        }
        return myboard;
    }


    bool validate_attempt(const GameOptions& game_options, const Code& attempt)
    {
        if (game_options.number_of_characters_per_code == attempt.value.size())
        {
            for (const char& c : attempt.value)
            {
                if ((c < game_options.minimum_allowed_character) | (c > game_options.maximum_allowed_character))
                {
                    return false;
                }
            }
            return true;
        }
        else
        {
            return false;
        }
    }

    Feedback compare_attempt_with_secret_code(const Code& attempt, const Code& secret_code)
    {
        Feedback myfeed;
        for (int i = 0; i < secret_code.value.size(); i++)
        {
            char temp = secret_code.value[i];
            for (int j = 0; j < attempt.value.size(); j++)
            {
                if (secret_code.value.find(attempt.value[j]))
                {
                    myfeed.cows++;
                    break;
                }
                if (temp == attempt.value[j])
                {
                    myfeed.bulls++;
                    break;
                }
            }
        }
        return myfeed;
    }

    bool is_end_of_game(const GameOptions& game_options, const Board& board)
    {
        if (game_options.max_number_of_attempts == board.attempts_and_feedbacks.size())
        {
            return true;
        }
        return false;
    }


    bool is_win(const GameOptions& game_options, const Board& board)
    {
        if (board.attempts_and_feedbacks.back().attempt.value == board.secret_code.value)
        {
            return true;
        }

        return false;
    }


    Code ask_attempt(std::ostream& output_stream, std::istream& input_stream, const GameOptions& game_options,const Board& board)
    {
        // Max number of attemps and max number of caracter ...
        Code incode;
        std::string temp = "";
        int current_attempt = (int)board.attempts_and_feedbacks.size();
        output_stream << "Please enter your guess for the " << current_attempt
                      << " (Tips : " << game_options.number_of_characters_per_code << " between "
                      << game_options.minimum_allowed_character << " and " << game_options.maximum_allowed_character
                      << ") :";
        input_stream >> incode.value;
        return incode;
    }


    void display_board(std::ostream& output_stream, const GameOptions& game_options, const Board& board)
    {
        // start of head printing
        int anssize = game_options.number_of_characters_per_code;
        std::string espaces = "";
        std::string moins = "--------------------------";
        std::string etoiles = "";
        std::string points = "";

        for (unsigned int i = 0U; i < game_options.number_of_characters_per_code; i++)
        {
            points = points + ". ";
        }
        for (int j = 0; j < anssize; j++)
        {
            etoiles = etoiles + "* ";
            espaces = espaces + "  ";
            moins = moins + "--";
        }
        moins = moins + "\n";

        output_stream << moins << "| SECRET  " << etoiles << "|              |\n"
                      << moins << "| ATTEMPTS" << espaces << "| BULLS | COWS |\n"
                      << moins << "\n";
        // end of head printing

        int sz = (int)board.attempts_and_feedbacks.size();
        for (unsigned int i = 0U; i < game_options.max_number_of_attempts; i++) // for all attempts
        {
            // board.attempts_and_feedbacks[sz - i];
            if (i < game_options.max_number_of_attempts - sz) // writting the empty attempts
            {

                if (game_options.max_number_of_attempts - i < 10)
                {
                    output_stream << "| #" << '0' << game_options.max_number_of_attempts - i << '   ' << '   ' << points
                                  << "|"
                                  << "   "
                                  << " "
                                  << "   "
                                  << "|"
                                  << "  " << board.attempts_and_feedbacks[i].feedback.cows << "   |\n";
                }
                // two different cases to put the 0 digit in case of need
                else
                {
                    output_stream << "| #" << game_options.max_number_of_attempts - i << '   ' << '   ' << points << "|"
                                  << "   "
                                  << " "
                                  << "   "
                                  << "|"
                                  << "  "
                                  << " "
                                  << "   |\n";
                }
            }

            else
            { // writting played attempts
                std::string codeout;
                for (unsigned int k = 0U; k < game_options.number_of_characters_per_code; k++)
                {
                    codeout = codeout + board.attempts_and_feedbacks[i].attempt.value + " ";
                }
                if (game_options.max_number_of_attempts - i < 10)
                {
                    output_stream << "| #" << '0' << game_options.max_number_of_attempts - i << '   ' << '   '
                                  << codeout + "|"
                                  << "   " << board.attempts_and_feedbacks[i].feedback.bulls << "   "
                                  << "|"
                                  << "  " << board.attempts_and_feedbacks[i].feedback.cows << "   |\n";
                }

                else
                {
                    output_stream << "| #" << game_options.max_number_of_attempts - i << '   ' << '   ' << codeout + "|"
                                  << "   " << board.attempts_and_feedbacks[i].feedback.bulls << "   "
                                  << "|"
                                  << "  " << board.attempts_and_feedbacks[i].feedback.cows << "   |\n";
                }
            }
        }

        output_stream << moins;
    }



} // namespace bulls_and_cows
