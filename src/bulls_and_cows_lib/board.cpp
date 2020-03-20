
#include "board.hpp"
#include "input.hpp"
#include "random.hpp"
#include <vector>

namespace bulls_and_cows {

    // TODO: define the body of the functions declared in board.cpp
    Board create_board(const GameOptions& game_options)
    {
        Board myboard{};

        std::vector<char> allowed_char;
        for (auto i = game_options.minimum_allowed_character; i <= game_options.maximum_allowed_character;
             i++) // remplir un vector avec la liste des caracteres autorisés
        {
            allowed_char.push_back(i);
        }

        for (unsigned int i = 0; i < game_options.number_of_characters_per_code; i++)
        {
            char temp = generate_random_character(
                allowed_char[0],
                allowed_char[allowed_char.size() - 1]); // piocher dedans en choisissant un index de manière aléatoire

            for (unsigned int j = 0; j < allowed_char.size(); j++) //
            {
                if (allowed_char[j] == temp)
                {
                    allowed_char.erase(allowed_char.begin() + i); // supprimer le caractère du vector contenant les caracteres autorisés
                }
            }
            myboard.secret_code.value.push_back(temp); //ajouter à la string secret_code.value
        }

        /*for (unsigned int i = 0; i < game_options.number_of_characters_per_code; i++)
        {
            auto rand = generate_random_character(game_options.minimum_allowed_character,
                                                  game_options.maximum_allowed_character);

            myboard.secret_code.value.push_back(rand);
        }*/

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

        return true;
    }

    Feedback compare_attempt_with_secret_code(const Code& attempt, const Code& secret_code)
    {
        Feedback myfeedback{};
        int cpt_bulls = 0;
        int cpt_cows = 0;
        unsigned int n = 0;

        for (unsigned int i = 0; i < attempt.value.size(); i++)
        {
            for (unsigned int j = n; j < secret_code.value.size(); j++)
            {
                if (secret_code.value[j] == attempt.value[i])
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
            n++;
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

    void display_board(std::ostream& output_stream, const GameOptions& game_options, const Board& board)
    {
        output_stream << "Secret Code : ";
        for (unsigned int i = 0; i < game_options.number_of_characters_per_code; i++)
        {
            output_stream << "* ";
        }
        output_stream << "\n";

        for (auto element : board.attempts_and_feedbacks)
        {
            output_stream << element.attempt.value << " ||||| "
                          << "Bulls : " << element.feedback.bulls << " // Cows : " << element.feedback.cows << "\n";
        }
    }

    Code ask_attempt(std::ostream& output_stream, std::istream& input_stream, const GameOptions& game_options,
                     const Board& board)
    {
        Code attempt{};
        output_stream << "Enter your attempt : ";
        attempt.value = ask_string(input_stream);

        return attempt;
    }

} // namespace bulls_and_cows
