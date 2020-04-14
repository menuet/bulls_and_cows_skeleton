
#include "board.hpp"
#include "random.hpp"
#include <string>

namespace bulls_and_cows {
    Board create_board(const GameOptions& game_options)
    {
        Board board;
        std::string code;

        while (code.size() < game_options.number_of_characters_per_code)
        {
            code += generate_random_character(game_options.minimum_allowed_character,
                                              game_options.maximum_allowed_character);
        }

        board.secret_code.value = code;
        return board;
    }

    bool validate_attempt(const GameOptions& game_options, const Code& attempt)
    {
        if (game_options.number_of_characters_per_code == attempt.value.size())
        {
            for (unsigned int i = 0; i < game_options.number_of_characters_per_code; i++)
            {
                if ((attempt.value[i] < game_options.minimum_allowed_character) ||
                    (attempt.value[i] > game_options.maximum_allowed_character))
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
        Feedback feedback;
        unsigned i = 0;
        unsigned k = 0;
        std::string strcode = secret_code.value;
        std::string stratt = attempt.value;

        while (i < attempt.value.size())
        {
            if (stratt[i] == strcode[i])
            {
                feedback.bulls++;
                stratt = stratt.replace(i, 1, ":");
                strcode = strcode.replace(i, 1, ".");
            }
            i++;
        }
        i = 0;
        while (i < attempt.value.size())
        {
            while (k < attempt.value.size())
            {
                if (stratt[i] == strcode[k])
                {
                    feedback.cows++;
                    stratt.replace(i, 1, "/");
                    strcode.replace(k, 1, "#");
                }
                k++;
            }
            i++;
            k = 0;
        }
        return feedback;
    }

    bool is_end_of_game(const GameOptions& game_options, const Board& board)
    {
        if (board.attempts_and_feedbacks.size() == game_options.max_number_of_attempts)
        {
            std::cout << " GAME OVER !\n";
            std::cout << " Try Again \n";
            return true;
        }
        else
        {
            return false;
        }
    }

    bool is_win(const GameOptions& game_options, const Board& board)
    {
        if (board.attempts_and_feedbacks.empty())
        {
            return false;
        }

        if (board.attempts_and_feedbacks.back().attempt.value == board.secret_code.value)
        {
            std::cout << "~~~~~~~~ YOU WON ~~~~~~~~\n";
            return true;
        }

        return false;
    }

    void display_board(std::ostream& output_stream, const GameOptions& game_options, const Board& board)
    {
        for (unsigned a = 0; a < game_options.number_of_characters_per_code; a++)
        {
            output_stream << "--";
        }
        output_stream << "---------------------------\n"
                      << "| SECRET   ";

        for (unsigned b = 0; b < game_options.number_of_characters_per_code; b++)
        {
            output_stream << "* ";
        }

        output_stream << "|              |\n---------------------------";
        for (unsigned c = 0; c < game_options.number_of_characters_per_code; c++)
        {
            output_stream << "--";
        }
        output_stream << "\n"
                         "| ATTEMPTS ";

        for (unsigned d = 0; d < game_options.number_of_characters_per_code; d++)
        {
            output_stream << "  ";
        }
        output_stream << "| BULLS | COWS |\n";
        for (unsigned e = 0; e < game_options.number_of_characters_per_code; e++)
        {
            output_stream << "--";
        }
        output_stream << "---------------------------\n";
        for (unsigned i = game_options.max_number_of_attempts; i > 0; i--)
        {
            std::string nb_points{};
            for (unsigned f = 0; f < game_options.number_of_characters_per_code; f++)
            {
                nb_points += ". ";
            }
            if (board.attempts_and_feedbacks.size() < i)
            {
                if (i > 9)
                    output_stream << "| #" << i << "      " << nb_points << "|       |      |\n";
                else
                    output_stream << "| #0" << i << "      " << nb_points << "|       |      |\n";
            }
            else
            {
                if (i > 9)
                {
                    output_stream << "| #" << i << "      ";
                    for (unsigned h = 0; h < game_options.number_of_characters_per_code; h++)
                    {
                        output_stream << board.attempts_and_feedbacks[i - 1].attempt.value[h] << " ";
                    }
                    output_stream << "|  " << board.attempts_and_feedbacks[i - 1].feedback.bulls << "    |  "
                                  << board.attempts_and_feedbacks[i - 1].feedback.cows << "   |\n";
                }

                else
                {
                    output_stream << "| #0" << i << "      ";
                    for (unsigned h = 0; h < game_options.number_of_characters_per_code; h++)
                    {
                        output_stream << board.attempts_and_feedbacks[i - 1].attempt.value[h] << " ";
                    }
                    output_stream << "|  " << board.attempts_and_feedbacks[i - 1].feedback.bulls << "    |  "
                                  << board.attempts_and_feedbacks[i - 1].feedback.cows << "   |\n";
                }
            }
        }
        output_stream << "-------------------------------------\n";
    }

    
    

    Code ask_attempt(std::ostream& output_stream, std::istream& input_stream, const GameOptions& game_options,
                     const Board& board)
    {

        
        Code code;
        
        bool validattempt = validate_attempt(game_options, code);

        while (validattempt == false)
        {
            output_stream << "What is your guess (" << game_options.number_of_characters_per_code
                          << " characters between '" << game_options.minimum_allowed_character << "' and '"
                          << game_options.maximum_allowed_character << "')\n? ";
            input_stream >> code.value;

            validattempt = validate_attempt(game_options, code);

            if (validattempt == false)
            {
                output_stream
                    << "Your guess has an invalid length or contains non-allowed characters, please try again\n";
            }
        }
        return code;
    }

} // namespace bulls_and_cows