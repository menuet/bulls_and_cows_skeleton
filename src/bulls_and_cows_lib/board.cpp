
#include "board.hpp"
#include "input.hpp"
#include "random.hpp"
#include <vector>

namespace bulls_and_cows {

    Board create_board(const GameOptions& game_options)
    {
        Board myboard{};

        // On crée un vecteur et on insert dedans tous les charactères autorisés
        std::vector<char> allowed_char{};

        for (auto i = game_options.minimum_allowed_character; i <= game_options.maximum_allowed_character; i++)
        {
            allowed_char.push_back(i);
        }

        unsigned int n = 0;
        while (n != game_options.number_of_characters_per_code)
        {
            // On genère aléatoirement un char parmi les char autorisés dans le vecteur contenant les char autorisés.
            char alea_char = generate_random_character(allowed_char.front(), allowed_char.back());

            for (unsigned int k = 0; k < allowed_char.size(); k++)
            {
                if (allowed_char[k] == alea_char)
                {
                    allowed_char.erase(allowed_char.begin() + k); // on supprime le char de la liste des char autorisés
                    myboard.secret_code.value.push_back(alea_char); // on l'insert dans le code secret
                    n++;
                }
            }
        }

        // std::cout << myboard.secret_code.value;
        return myboard;
    }

    bool validate_attempt(const GameOptions& game_options, const Code& attempt)
    {
        if (attempt.value.size() != game_options.number_of_characters_per_code)
        {
            return false;
        }

        for (const char attempt_char : attempt.value)
        {
            if (attempt_char < game_options.minimum_allowed_character ||
                attempt_char > game_options.maximum_allowed_character)
            {
                return false;
            }
        }

        for (unsigned int i = 0; i < attempt.value.size();
             i++) // permet de detecter la présence de doublon de char dans l'attempt
        {
            for (unsigned int j = 0; j < attempt.value.size(); j++)
            {
                if ((attempt.value[i] == attempt.value[j]) && (i != j))
                {
                    return false;
                }
            }
        }

        return true;
    }

    Feedback compare_attempt_with_secret_code(const Code& attempt, const Code& secret_code)
    {
        Feedback myfeedback{};
        int cpt_bulls = 0;
        int cpt_cows = 0;

        for (unsigned int i = 0; i < attempt.value.size(); i++)
        {
            for (unsigned int j = 0; j < secret_code.value.size(); j++)
            {
                if (attempt.value[j] == secret_code.value[i])
                {
                    if (i == j)
                    {
                        cpt_bulls++;
                    }
                    else
                    {
                        cpt_cows++;
                    }
                }
            }
        }

        myfeedback.bulls = cpt_bulls;
        myfeedback.cows = cpt_cows;

        return myfeedback;
    }

    bool is_end_of_game(const GameOptions& game_options, const Board& board)
    {
        return board.attempts_and_feedbacks.size() == game_options.max_number_of_attempts;
    }

    bool is_win(const GameOptions& game_options, const Board& board)
    {
        for (AttemptAndFeedback tempo : board.attempts_and_feedbacks)
        {
            if (tempo.feedback.bulls == game_options.number_of_characters_per_code)
            {
                return true;
            }
        }
        return false;
    }

    void display_board(std::ostream& output_stream, const GameOptions& game_options, const Board& board) //
    {
        Code secret{};
        const char star = '*';

        if (is_win(game_options, board) || is_end_of_game(game_options, board))
        {
            secret.value = board.secret_code.value;
        }

        else
        {
            for (unsigned int i = 0; i < game_options.number_of_characters_per_code; i++)
            {
                secret.value.push_back(star);
                secret.value.push_back(' ');
            }
        }

        output_stream << "----------------------------------\n"
                         "| SECRET CODE : "<<secret.value<< "\n"
                         "----------------------------------|\n"
                         "| ATTEMPTS         | BULLS | COWS |\n"
                         "----------------------------------|\n";
        for (auto element : board.attempts_and_feedbacks)
        {
            output_stream << "| "<< element.attempt.value <<"\t\t   | "<< element.feedback.bulls <<"\t   | "
                          <<element.feedback.cows<< "\t  |\n";
        }
        output_stream << "----------------------------------\n";
    }

    Code ask_attempt(std::ostream& output_stream, std::istream& input_stream, const GameOptions& game_options,
                     const Board& board)
    {
        Code attempt{};
        auto nb_guess = board.attempts_and_feedbacks.size() + 1;
        auto nb_char = game_options.number_of_characters_per_code;
        auto min = game_options.minimum_allowed_character;
        auto max = game_options.maximum_allowed_character;

        output_stream << "What is your guess #" << nb_guess << " (" << nb_char << " different characters between '"
                      << min << "' and '" << max << "') : ";
        attempt.value = ask_string(input_stream);

        return attempt;
    }

} // namespace bulls_and_cows
