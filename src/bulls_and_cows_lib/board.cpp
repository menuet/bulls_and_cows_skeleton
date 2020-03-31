
#include "board.hpp"

namespace bulls_and_cows {

    // TODO: define the body of the functions declared in board.cpp
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

} // namespace bulls_and_cows
