
#include "board.hpp"
#include "random.hpp"
#include <iostream>



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
            for (const char& a : attempt.value)
            {
                if ((a < game_options.minimum_allowed_character) | (a > game_options.maximum_allowed_character))
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
        while (i < attempt.value.size())
        {
            while (k < attempt.value.size())
            {

                if (attempt.value[i] == secret_code.value[k] && i == k)
                {
                    feedback.bulls++;
                }

                else if (attempt.value[i] == secret_code.value[k] && i != k)
                {
                    feedback.cows++;
                }
                k++;
            }
            i++;
            feedback.cows = feedback.cows - feedback.bulls;
        }
        return feedback;
    }

    bool is_end_of_game(const GameOptions& game_options, const Board& board)
    {
        if (board.attempts_and_feedbacks.size() == game_options.max_number_of_attempts)
        {
            return true;
        }
        return false;
    }

    bool is_win(const GameOptions& game_options, const Board& board)
    {
        if ((board.attempts_and_feedbacks.empty()))
            return false;

        if (board.attempts_and_feedbacks.back().attempt.value == board.secret_code.value)
        {
            return true;
        }

        return false;
    }

    void display_board(std::ostream& output_stream, const GameOptions& game_options, const Board& board)
    {
        size_t i = game_options.max_number_of_attempts;
        output_stream << "-------------------------------------\n"
                      << "| SECRET   * * * * * |              |\n"
                      << "-------------------------------------\n"
                      << "| ATTEMPTS           | BULLS | COWS |\n"
                      << "-------------------------------------\n";
        while (i > board.attempts_and_feedbacks.size())
        {
            // int bull = board.attempts_and_feedbacks[i].feedback.bulls;
            // unsigned int cow = board.attempts_and_feedbacks[i].feedback.cows;
            if (i > 9)
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
                    output_stream << "| #" << i << "      . . . . . |  "
                                  << "     |   "
                                     "   |\n";

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
                    output_stream << "| #0" << i << "      . . . . . |       |      |\n";
                    if (i > 9)
                    {
                        output_stream << "| #" << i << "      . . . . . |  "
                                      << board.attempts_and_feedbacks[i].feedback.bulls << "    |   "
                                      << board.attempts_and_feedbacks[i].feedback.cows << "   |\n";
                    }

                    else
                    {
                        output_stream << "| #0" << i << "      . . . . . |       |      |\n";
                    }
                }
                i--;
            }
            output_stream << "-------------------------------------\n";
        }
    }
} // namespace bulls_and_cows

