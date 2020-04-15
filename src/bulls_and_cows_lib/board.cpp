#include "board.hpp"
#include <bulls_and_cows_lib\random.cpp>

namespace bulls_and_cows {

    Board create_board(const GameOptions& game_options)
    {
        Board board;
        std::string code{};
        for (unsigned int i = 0; i < game_options.number_of_characters_per_code; i++)
        {

            board.secret_code.value += generate_random_character(game_options.minimum_allowed_character,
                                                                 game_options.maximum_allowed_character);
        }

        return board;
    }

    bool validate_attempt(const GameOptions& game_options, const Code& attempt)
    {
        if (attempt.value.size() != game_options.number_of_characters_per_code)

        {
            return false;
        }
        for (const char& character : attempt.value)
        {
            if (character < game_options.minimum_allowed_character ||
                character > game_options.maximum_allowed_character)
            {
                return false;
            }
        }
        return true;
    }

    Feedback compare_attempt_with_secret_code(const Code& attempt, const Code& secret_code)
    {
        Feedback myfeedback{};
        int bulls = 0;
        int cows = 0;

        for (unsigned int i = 0; i < attempt.value.size(); i++)
        {
            for (unsigned int j = 0; j < secret_code.value.size(); j++)
            {
                if (attempt.value[j] == secret_code.value[i])
                {
                    if (i == j)
                    {
                        bulls++;
                    }
                    else
                    {
                        cows++;
                    }
                }
            }
        }

        myfeedback.bulls = bulls;
        myfeedback.cows = cows;

        return myfeedback;
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

    void display_board(std::ostream& output_stream, const GameOptions& game_options, const Board& board) //
    {
        Code code;
        const char c = '*';

        if (is_win(game_options, board) || is_end_of_game(game_options, board))
        {
            code.value = board.secret_code.value;
        }

        else
        {
            for (unsigned int i = 0; i < game_options.number_of_characters_per_code; i++)
            {
                code.value.push_back(c);
                code.value.push_back(' ');
            }
        }

        output_stream << "----------------------------------\n"
                         "| SECRET CODE : "
                      << code.value
                      << "\n"
                         "Your Tries"
                         "\n"
                         "----------------------------------|\n"
                         "| ATTEMPTS         | BULLS | COWS |\n"
                         "----------------------------------|\n";
        for (auto element : board.attempts_and_feedbacks)
        {
            output_stream << "| " << element.attempt.value << "\t\t   | " << element.feedback.bulls << "\t   | "
                          << element.feedback.cows << "\t  |\n";
        }
        output_stream << "---------------------------------\n";
    }

    Code ask_attempt(std::ostream& output_stream, std::istream& input_stream, const GameOptions& game_options,
                     const Board& board)
    {
        Code combinaison;
        std::cout << "Write your combinaison:\n";
        std::cin >> combinaison.value;

        while (validate_attempt == false)
        {
            std::cout << "Choose your combinaison (" << game_options.number_of_characters_per_code
                      << " characters between '" << game_options.minimum_allowed_character << "' and '"
                      << game_options.maximum_allowed_character << "')\n? ";
            std::cin >> combinaison.value;
        }

        return combinaison;
    }
} // namespace bulls_and_cows
