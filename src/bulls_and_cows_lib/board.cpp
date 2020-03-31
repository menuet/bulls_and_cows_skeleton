
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
            k = i;
        }
        return feedback;
    }
    //Un message d'erreur apparait néanmoins, après plusieurs tests j'ai l'impression que cela vient du test unitaire et non de mon code
    // Testant les 75/76 et s'attendant au résultat des lignes 68/69
    // Mais je me trompe surement

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

    }
}