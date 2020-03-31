
#include "board.hpp"
#include "random.hpp"
#include <string>

namespace bulls_and_cows 
{
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
        std::cout << secret_code.value[5];
        while (i < attempt.value.size())
        {
            if (stratt[i] == strcode[i])
            {
                std::cout << stratt;
                std::cout << " ";
                std::cout << strcode;
                std::cout << " ";
                feedback.bulls++;
                stratt = stratt.replace(i, 1, ":");
                strcode = strcode.replace(i, 1, ".");
                std::cout << stratt;
                std::cout << " ";
                std::cout << strcode;
                std::cout << " ";
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

                    std::cout << stratt;
                    std::cout << " ";
                    std::cout << strcode;
                    std::cout << " ";
                    feedback.cows++;
                    stratt.replace(i, 1, "/");
                    strcode.replace(k, 1, "#");

                    std::cout << stratt;
                    std::cout << " ";
                    std::cout << strcode;
                    std::cout << " ";
                }
                k++;
            }
            i++;
            k = i;
        }
        return feedback;
    }
    bool is_end_of_game(const GameOptions& game_options, const Board& board)
    {
        if (board.attempts_and_feedbacks.size() ==
            game_options.maximum_allowed_character)
        {
            std::cout << " GAME OVER !\n";
            return true;
        }
        else
        {
            return false;
        }
    }
    // TODO: define the body of the functions declared in board.cpp
 // namespace bulls_and_cows
}