
#include "board.hpp"
#include "random.cpp"
#include "input.hpp"

namespace bulls_and_cows {

    // TODO: define the body of the functions declared in board.cpp
    Board create_board(const GameOptions& game_options)
    {
        Board board;
        std::string code{};
        for (unsigned i = 0; i < game_options.number_of_characters_per_code; i++)
        {
            code = code + generate_random_character(game_options.minimum_allowed_character,
                                                    game_options.maximum_allowed_character);
        }
        board.secret_code.value = code;
        return board;
    }

    bool validate_attempt(const GameOptions& game_options, const Code& attempt)
    {
        for (unsigned i = 0; i < game_options.number_of_characters_per_code; i++)
        {
            if (attempt.value[i] < game_options.minimum_allowed_character ||
                attempt.value[i] > game_options.maximum_allowed_character)
            {
                return false;
            }
        }
        if (attempt.value.length() != game_options.number_of_characters_per_code)
        {
            return false;
        }
        return true;
    }

     Feedback compare_attempt_with_secret_code(Code attempt, Code secret_code)
    {
        Feedback feedback;

        for (unsigned i = 0; i < attempt.value.size(); i++)
        {
            if (attempt.value[i] == secret_code.value[i])
            {
                feedback.bulls++;
                secret_code.value.replace(i, 1, "?");
                attempt.value.replace(i, 1, "!");
            }
        }

        for (auto a : attempt.value)
        {
            auto iter = std::find(secret_code.value.begin(), secret_code.value.end(), a);
            if (iter != secret_code.value.end())
            {
                feedback.cows++;
                *iter = '?';
            }
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
        if (board.attempts_and_feedbacks.empty())
        {
            return false;
        }

        if (board.attempts_and_feedbacks.back().attempt.value == board.secret_code.value)
        {
            return true;
        }

        return false;
    }

    void display_board(std::ostream& output_stream, const GameOptions& game_options, const Board& board)
    {

        if (is_win(game_options, board) || is_end_of_game(game_options, board))
        {
            output_stream << "-------------------------------------\n"
                          << "| SECRET   ";
            for (auto charcode : board.secret_code.value)
            {
                output_stream << charcode;
                output_stream << " ";
            }
        }
        else
        {

            output_stream << "-------------------------------------\n"
                          << "| SECRET   ";
            for (unsigned j = 0; j < game_options.number_of_characters_per_code; j++)
            {
                output_stream << "* ";
            }
        }
        output_stream << "|              |\n-------------------------------------\n"
                      << "| ATTEMPTS ";

        for (unsigned l = 0; l < game_options.number_of_characters_per_code; l++)
        {
            output_stream << "  ";
        }
        output_stream << "| BULLS | COWS |\n "
                      << "-------------------------------------\n";

        for (unsigned i = game_options.max_number_of_attempts; i > 0; i--)
        {
            std::string points{};
            for (unsigned k = 0; k < game_options.number_of_characters_per_code; k++)
            {
                points += ". ";
            }
            if (board.attempts_and_feedbacks.size() < i)
            {
                if (i < 10)
                    output_stream << "| #0";
                else
                    output_stream << "| #";
                output_stream << i << "      " << points << "|       |      |\n";
            }
            else
            {
                if (i < 10)
                    output_stream << "| #0";
                else
                    output_stream << "| #";
                output_stream << i << "      ";
                for (auto charbychar : board.attempts_and_feedbacks.at(i - 1).attempt.value)
                {
                    output_stream << charbychar;
                    output_stream << " ";
                }
                output_stream << "|   " << board.attempts_and_feedbacks.at(i - 1).feedback.bulls << "   |  "
                              << board.attempts_and_feedbacks.at(i - 1).feedback.cows << "   |\n";
            }
        }
        output_stream << "-------------------------------------\n";
    }

    Code ask_attempt(std::ostream& output_stream, std::istream& input_stream, const GameOptions& game_options,
                     const Board& board)
    {
        Code attempt;
        output_stream << "What is your guess #01 (" << game_options.number_of_characters_per_code
                      << " characters between '" << game_options.minimum_allowed_character << "' and '"
                      << game_options.maximum_allowed_character << "') ?" << std::endl;
        attempt.value= ask_string(input_stream) ;

        while (!validate_attempt(game_options, attempt))
        {
            output_stream << "Your guess has an invalid length or contains non-allowed characters, please try again\n"
                          << "What is your guess #01 (" << game_options.number_of_characters_per_code
                          << " characters between '" << game_options.minimum_allowed_character << "' and '"
                          << game_options.maximum_allowed_character << "') ?" << std::endl;
         attempt.value = ask_string(input_stream) ;
        }

        return attempt;
    }
} // namespace bulls_and_cows

