
#include "board.hpp"
#include "random.hpp"

#include <chrono>
#include <fstream>
#include <iostream>
#include <thread>

namespace bulls_and_cows {

    // TODO: define the body of the functions declared in board.cpp
    // Create a board and with a new random secret code composed of allowed characters
    Board create_board(const GameOptions& game_options)
    {
        Board board;
        int unsigned i;

        for (i = 0; i < game_options.number_of_characters_per_code; i++)
        {
            board.secret_code.value =
                board.secret_code.value + generate_random_character(game_options.minimum_allowed_character,
                                                                    game_options.maximum_allowed_character);
        }

        return board;
    }

    // Validate that a user-entered code contains proper number of allowed characters
    bool validate_attempt(const GameOptions& game_options, const Code& attempt)
    {
        int unsigned i;
        int unsigned verif = 0;

        if (attempt.value.size() == game_options.number_of_characters_per_code)
        {
            for (i = 0; i < game_options.number_of_characters_per_code; i++)
            {
                if (attempt.value[i] > game_options.minimum_allowed_character ||
                    attempt.value[i] < game_options.maximum_allowed_character)
                {
                    verif++;
                }
            }
            if (verif == game_options.number_of_characters_per_code)
            {
                return true;
            }
            else
            {
                return false;
            }
        }
        else
        {
            return false;
        }
    }

    // Compare a user-entered code with the secret code and give the corresponding number of bulls and cows
    Feedback compare_attempt_with_secret_code(const Code& attempt, const Code& secret_code)
    {
        int unsigned i;
        Feedback feedback;

        std::size_t f;

        for (i = 0; i < attempt.value.size(); i++)
        {
            if (attempt.value[i] == secret_code.value[i])
            {
                feedback.bulls++;
            }
        }

        for (i = 0; i < attempt.value.size(); i++)
        {
            f = secret_code.value.find(attempt.value[i]);
            if (f != std::string::npos)
                feedback.cows++;
        }

        return feedback;
    }

    // Test if this is the end of the game
    bool is_end_of_game(const GameOptions& game_options, const Board& board)
    {
        if (game_options.max_number_of_attempts == board.attempts_and_feedbacks.size())
        {
            return true;
        }
        return false;
    }

    // Test if the last attempt is a win
    bool is_win(const GameOptions& game_options, const Board& board)
    {

        if (board.attempts_and_feedbacks.empty())
            return false;
        else if (board.attempts_and_feedbacks.back().attempt.value == board.secret_code.value)
        {
            return true;
        }
        else
            return false;
    }

    // Display the scret code and the list of attempts of the board
    void display_board(std::ostream& output_stream, const GameOptions& game_options, const Board& board)
    {
        int unsigned i;

        std::string secretmot{};
        if (!is_end_of_game(game_options, board) && !is_win(game_options, board))
        {
            for (i = 0; i < board.secret_code.value.size(); i++)
                secretmot = secretmot + "*";
        }
        else
            secretmot = board.secret_code.value;

            output_stream << "-----------------------------------------\n";
        output_stream << "| Secret       " << secretmot << "     |              |\n";
        output_stream << "-----------------------------------------\n";
        output_stream << "| ATTEMPTS               | BULLS | COWS |\n ";
        output_stream << "-----------------------------------------\n";

        for (i = game_options.max_number_of_attempts; i > board.attempts_and_feedbacks.size(); i--)
        {
            if (i < 10)
                output_stream << "| #0" << i << "          - - - - - |       |      |\n";
            else
                output_stream << "| #" << i << "          - - - - - |       |      |\n";
        }

        if (!board.attempts_and_feedbacks.empty())
        {
            for (size_t j = board.attempts_and_feedbacks.size(); j > 0; j--)
            {
                const auto& ValueMot = board.attempts_and_feedbacks[j - 1].attempt.value;
                const auto& bulls = board.attempts_and_feedbacks[j - 1].feedback.bulls;
                const auto& cows = board.attempts_and_feedbacks[j - 1].feedback.cows;
                if (j < 10)
                    output_stream << "| #0" << j << "          " << ValueMot << "     |   " << bulls << "   |   "
                                  << cows << "  |\n";
                else
                    output_stream << "| #" << j << "          " << ValueMot << "     |   " << bulls << "   |   " << cows
                                  << "  |\n";
            }
        }

        output_stream << "-----------------------------------------\n";
    }

    // Ask the user to provide another attempt
    Code ask_attempt(std::ostream& output_stream, std::istream& input_stream, const GameOptions& game_options,
                     const Board& board)
    {
        Code code;

        bool verif = false;

        while (!verif)
        {
            if (board.attempts_and_feedbacks.size() < 10)
                output_stream << "What is your guess #0";
            else
                output_stream << "What is your guess #";

            output_stream << board.attempts_and_feedbacks.size() + 1;
            output_stream << " (" << game_options.number_of_characters_per_code;
            output_stream << " characters between '" << game_options.minimum_allowed_character << "' and '"
                          << game_options.maximum_allowed_character << "' )\n?";

            input_stream >> code.value;

            verif = validate_attempt(game_options, code);
        }

        return code;
    }

} // namespace bulls_and_cows
