#include "board.hpp"
#include "random.hpp"

namespace bulls_and_cows {
    Board create_board(const GameOptions& game_options) // Return Board
    {
        Board board;        // Creation board
        std::string code{}; // Chaine de caracteres vide

        for (unsigned i = 0; i < game_options.number_of_characters_per_code; i++)
        {
            code += generate_random_character(game_options.minimum_allowed_character,
                                              game_options.maximum_allowed_character); // Creation code secret
        }

        board.secret_code.value = code;
        return board;
    }

    bool validate_attempt(const GameOptions& game_options, const Code& attempt)
    {
        if (attempt.value.length() != game_options.number_of_characters_per_code)
        {
            return false;
        }

        for (auto a : attempt.value) // for remplacer par range for / auto comme pointeur - prend la valeur de chaque lettre une par une
        {
            if (a < game_options.minimum_allowed_character || a > game_options.maximum_allowed_character)
            {
                return false;
            }
        }

        return true;
    }

    Feedback compare_attempt_with_secret_code(Code attempt, Code secret_code) // const pour pouvoir modifier la vlauer d'une copie qu'on créé (supprimer const crer une coopie)
    {
        Feedback feedback;

        for (unsigned i = 0; i < attempt.value.size(); i++)
        {
            if (attempt.value[i] ==
                secret_code.value[i]) // Si la lettre de la tentative est égale a une lettre du code secret et a la memem place
            {
                feedback.bulls++;
                secret_code.value.replace(i, 1, "?"); // ? quand on a triter un truc
                attempt.value.replace(i, 1, "!"); // pour pa retraiter on met un ! quand s'est deja traiter
            }
        }

        for (auto a : attempt.value)
        {
            auto iter = std::find(secret_code.value.begin(), secret_code.value.end(), a); // fonction find debut et fin d'un string et un caractere dedans / renvoie un pointeur vers l'emplacement de la lettre si elle y est
            // si pas d'eleme se met a la fin de la liste
            // iter stock le pointeur
            if (iter != secret_code.value.end()) // si fin pas la lettre donc osef mais is lettre on augmente cows
            {
                feedback.cows++;
                *iter = '?'; // comme en haut / * => pour acceder la a valeur de iter
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

        if (board.attempts_and_feedbacks.empty()) // si liste d'essai vide = pas gagner donc faux
        {
            return false;
        }

        if (board.attempts_and_feedbacks.back().attempt.value ==
            board.secret_code.value) // attributs - attempsfeedback = tentatives + feedback du coup juste attempt pour
                                     // les tentatives .attempt - accéder a un string = .value pour avoir la valeur
        {
            return true;
        }

        return false;
    }

    void display_board(std::ostream& output_stream, const GameOptions& game_options, const Board& board)
    {
        output_stream << "-------------------------------------\n"
                      << "| SECRET   * * * * * |              |\n"
                      << "-------------------------------------\n"
                      << "| ATTEMPTS           | BULLS | COWS |\n"
                      << "-------------------------------------\n";

        for (unsigned i = game_options.max_number_of_attempts; i > 0; i--)
        {
            if (board.attempts_and_feedbacks.size() < i)
            {
                if (i < 10)
                    output_stream << "| #0";
                else
                    output_stream << "| #";

                output_stream << i << "      . . . . . |       |      |\n";
            }

            else
            {
                if (i < 10)
                    output_stream << "| #0";
                else
                    output_stream << "| #";

                output_stream << i << "       " << board.attempts_and_feedbacks.at(i - 1).attempt.value << " |   "
                              << board.attempts_and_feedbacks.at(i - 1).feedback.bulls << "   |  "
                              << board.attempts_and_feedbacks.at(i - 1).feedback.cows << "   |\n"; //at = indice
            }
        }
        output_stream << "-------------------------------------\n";
    }

    Code ask_attempt(std::ostream& output_stream, std::istream& input_stream, const GameOptions& game_options,
                     const Board& board)
    {
        Code attempt;

        output_stream << "Rentrez un premier code (" << game_options.number_of_characters_per_code
                      << " caractères entre '" << game_options.minimum_allowed_character << "' et '"
                      << game_options.maximum_allowed_character << "')" << std::endl;

        input_stream >> attempt.value;

        while (!validate_attempt(game_options, attempt))
        {
            output_stream << "Votre supposition de code a une longueur incorrecte ou contient des caractères non-autorisés, veuillez réessayer\n"
                          << "Rentrez un premier code (" << game_options.number_of_characters_per_code
                          << " caractères entre '" << game_options.minimum_allowed_character << "' et '"
                          << game_options.maximum_allowed_character << "')" << std::endl;

            input_stream >> attempt.value;

        }

        return attempt;
    }

} // namespace bulls_and_cows