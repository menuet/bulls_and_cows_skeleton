#include "board.hpp"
#include "random.hpp"
#include "input.hpp"
#include <algorithm>
#include <vector>
#include "game_options.hpp"
using namespace bulls_and_cows;


namespace bulls_and_cows {


    Board create_board(const GameOptions& game_options)
    {

        Board board{};
        // On remplit de façon aléatoire un vecteur (plutot qu'une string pour avoir un code dynamique) avec la fonction generate_random_character "les caractères autorisés"
        //std::vector<char> filling_code;
        for (unsigned int j = 0; j < game_options.number_of_characters_per_code; j++)
        {
            char temp = generate_random_character(game_options.minimum_allowed_character,
                game_options.maximum_allowed_character);
            board.secret_code.value.push_back(temp);
        }
        return board;
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

        return true;
    }

    Feedback compare_attempt_with_secret_code(const Code& attempt, const Code& secret_code)

    {
        //Dans le cas de la tentative on incrémente si le caractère vérifie la bonne place et le bon terme
        Feedback feedback{};

        int countBulls = 0;
        int countCows = 0;

        for (unsigned int i = 0; i < attempt.value.size(); i++)
        {
            for (unsigned int j = 0; j < secret_code.value.size(); j++)

            {

                if (attempt.value[j] == secret_code.value[i])//on vérifie la place

                {

                    if (i == j) // teste de la double égalité pour vérificarion
                    {

                        countBulls++;
                    }
                    else
                    {

                        countCows++;
                    }
                }
            }


        }


        feedback.bulls = countBulls;
        feedback.cows = countCows;


        return feedback;
    }


    bool is_end_of_game(const GameOptions& game_options, const Board& board)
    {
        if (board.attempts_and_feedbacks.size() == game_options.max_number_of_attempts) //si c'est la fin du jeu le true l'arrête sinon false il continue
        {
            return true;
        }   
            return false;
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


    void display_board(std::ostream& output_stream, const GameOptions& game_options, const Board& board)
    {
        Code secret{};
        const char star = '-';
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

        output_stream << "----------------------------\n"
            "| SECRET"
            << secret.value
            << "|                        | \n"
            "----------------------------------|\n"
            "| ATTEMPTS           | bulls_and_cows| COWS| \n"
            "------------------------------------| \n";

        for (auto element : board.attempts_and_feedbacks)
        {

            output_stream << "\n" << element.attempt.value << "\t\t |"
                << element.feedback.bulls << "\t | "
                << element.feedback.cows << "\t   | \n";
        }

        output_stream << "-\n";

    }

    Code ask_attempt(std::ostream& output_stream, std::istream& input_stream, const GameOptions& game_options,
        const Board& board)
    {
        Code attempt{};


        auto nb_attempt = board.attempts_and_feedbacks.size() + 1;
        unsigned int nb_char = game_options.number_of_characters_per_code;
        const char max = game_options.maximum_allowed_character;
        const char min = game_options.minimum_allowed_character;

        output_stream << "Cela est votre " << nb_attempt << " tentative(s), choisissez " << nb_char << " caractères entre " << min
            << " et " << max << ": ";


        attempt.value = ask_string(input_stream);
        return attempt;

    }

} // namespace bulls_and_cows
