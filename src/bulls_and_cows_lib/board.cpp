
#include "board.hpp"
#include "random.hpp"
#include "input.hpp"
#include <algorithm>
#include <vector>

namespace bulls_and_cows 
{

    // TODO: define the body of the functions declared in board.cpp
    // Create a board and with a new random secret code composed of allowed characters

    Board create_board(const GameOptions& game_options)

    {

        Board panel{};

        char new_char;

        for (unsigned int i = 0; i < game_options.number_of_characters_per_code; i++)

        {

            new_char = generate_random_character(game_options.minimum_allowed_character,
                                                 game_options.maximum_allowed_character);

            panel.secret_code.value.push_back(new_char);
        }

        return panel;
    }

    // Validate that a user-entered code contains proper number of allowed characters

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

    // tentative == taille du code et comprise entre max et min allowed character

    bool validate_attempt(const GameOptions& game_options, const Code& attempt)

    {

        if (attempt.value.size() != game_options.number_of_characters_per_code) // Analyse pour voir si les tailes des
                                                                                // nchiffre = nb character per code

        {

            return false; // booléen
        }

        for (const char attempt_char : attempt.value) // Analyse si le chararctere est plausible( between min and max)

        {

            if (attempt_char > game_options.maximum_allowed_character ||
                attempt_char < game_options.minimum_allowed_character)

            {

                return false;
            }
        }

        return true;
    }

    // Test if this is the end of the game

    bool is_end_of_game(const GameOptions& game_options, const Board& board)
    {

        if (game_options.max_number_of_attempts !=
            board.attempts_and_feedbacks
                .size()) // Compare si le nombre de tentative est = au nombre max autorisée, si oui renvoie true

        {

            return false;
        }

        return true;
    }

    // Test if the last attempt is a win

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

    // Display the scret code and the list of attempts of the board

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

                         "| ATTEMPTS       | bulls   |  cows|  \n"

                         "-----------------------------------| \n";

        for (auto element : board.attempts_and_feedbacks)

        {

            output_stream << "| " << element.attempt.value << "\t\t | " << element.feedback.bulls << "\t   | "

                          << element.feedback.cows << "\t   | \n";
        }

        output_stream << "-------------------\n";
    }

    Code ask_attempt(std::ostream& output_stream, std::istream& input_stream, const GameOptions& game_options,

                     const Board& board)

    {

        Code attempt{};

        auto nb_attempt = board.attempts_and_feedbacks.size() + 1;

        unsigned int nb_char = game_options.number_of_characters_per_code;

        const char max = game_options.maximum_allowed_character;

        const char min = game_options.minimum_allowed_character;

        output_stream << "Try a nex attempts\n attempt number" << nb_attempt << "(" << nb_char

                      << "different characters betwen '" << min << "' and '" << max << "'): ";

        attempt.value = ask_string(input_stream);

        return attempt;
    }

}

 // namespace bulls_and_cows