#include "board.hpp"
#include "input.hpp"
#include "random.hpp"
#include <algorithm>
#include <vector>

namespace bulls_and_cows {

    // TODO: define the body of the functions declared in board.cpp

    // Créer un tableau et avec un nouveau code secret aléatoire composé de caractères autorisés
    Board create_board(const GameOptions& game_options)
    {
        Board test{};
        char new_char;
        for (unsigned int i = 0; i < game_options.number_of_characters_per_code; i++)
        {
            new_char = generate_random_character(game_options.minimum_allowed_character,
                                                 game_options.maximum_allowed_character);
            test.secret_code.value.push_back(new_char);
        }
        return test;
    }

    // Valider qu'un code saisi par l'utilisateur contient le nombre adéquat de caractères autorisés
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
    // tentative == taille du code et comprise entre max et min allowed character
    bool validate_attempt(const GameOptions& game_options, const Code& attempt)
    {
        if (attempt.value.size() !=
            game_options.number_of_characters_per_code) // Verification de la taille de la tentative
        {
            return false;
        }
        for (const char attempt_char :
             attempt.value) // Verifie si les caractere de la tentatives sont compris entre le min et max
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

    // Tester si la dernière tentative est une victoire
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

    // Afficher le code et la liste des tentatives
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

        output_stream << "\n Try a nex attempts attempt number " << nb_attempt << "(" << nb_char
                      << "different characters betwen '" << min << "' and '" << max << "'): ";
        attempt.value = ask_string(input_stream);
        return attempt;
    }
} // namespace bulls_and_cows