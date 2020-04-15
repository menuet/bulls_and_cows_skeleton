#include "board.hpp"
#include "input.hpp"
#include "random.hpp"
#include <algorithm>
#include <vector>

namespace bulls_and_cows {

    Board create_board(const GameOptions& game_options)
    {
        Board myboard{};

        for (unsigned int j = 0; j < game_options.number_of_characters_per_code;
             j++) // pour j allant de 0 � number_of_characters_per_code(5)
        {
            char temp = generate_random_character(
                game_options.minimum_allowed_character,
                game_options.maximum_allowed_character); // g�n�rer un caract�re entre le
                                                         // minimum/maximum_allowed_character ici d�finis de A � Z
            myboard.secret_code.value.push_back(temp);   // retourn� le caract�re
        }

        //std::cout << myboard.secret_code.value; // acc�der � la valeur du code secret dans myboard
        return myboard;
    }

    bool validate_attempt(const GameOptions& game_options, const Code& attempt)
    {
        if (attempt.value.size() !=
            game_options.number_of_characters_per_code) // si la taille de ta tentative est diff�rente que
                                                        // number_of_characters_per_code retourne fuax
        {
            return false;
        }

        for (const char attempt_char : attempt.value)
        {
            if (attempt_char < game_options.minimum_allowed_character ||
                attempt_char > game_options.maximum_allowed_character) // v�rifie que les caract�re sojn bien compris
                                                                       // entre le minimum et le maximum
            {
                return false;
            }
        }

        return true;
    }

    // j'essaye de modifier pour r�soudre le probleme de cows et bulls

    Feedback compare_attempt_with_secret_code(const Code& attempt, const Code& secret_code)
    {
        Feedback myfeedback{};
        int cpt_bulls = 0;
        int cpt_cows = 0;

        Code secret_code_temp = secret_code;
        // bulls
        for (unsigned int i = 0; i < attempt.value.size(); i++)
        {
            if (attempt.value[i] == secret_code_temp.value[i])
            {
                cpt_bulls++;
                secret_code_temp.value.replace(i, 1, "!");
                continue;
            }
        }
        for (unsigned int i = 0; i < attempt.value.size(); i++)
        {
            for (unsigned int j = 0; j < secret_code_temp.value.size(); j++)
            {
                if (attempt.value[i] == secret_code_temp.value[j])
                {
                    cpt_cows++;
                    secret_code_temp.value.replace(j, 1, "!");
                    break;
                }
            }
        }

        myfeedback.bulls = cpt_bulls;
        myfeedback.cows = cpt_cows;

        return myfeedback;
    }

    bool is_end_of_game(const GameOptions& game_options, const Board& board)
    {
        return board.attempts_and_feedbacks.size() ==
               game_options.max_number_of_attempts; // si la taille du vecteur vaut le max_number_of_attempts (12) alors
                                                    // fin de partie
    }

    bool is_win(const GameOptions& game_options, const Board& board)
    {
        for (AttemptAndFeedback tempo : board.attempts_and_feedbacks) // r�cup�re un � un les �l�ment du vecteur en les
                                                                      // stockant sur tempo   (foreach en c#)
        {
            if (tempo.feedback.bulls ==
                game_options.number_of_characters_per_code) // on regard si on a bien 5 bulls pour savoir si on a gagner
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

        for (auto element : board.attempts_and_feedbacks) // element parcourt le vecteur de tentative attempt and
                                                          // feedbacks qui est compos� de bulls and cows
        {
            output_stream << "| " << element.attempt.value << "\t\t | " << element.feedback.bulls << "\t   | "
                          << element.feedback.cows << "\t   | \n"; // affiche la tentative entrer et les bulls and cows
        }
        output_stream << "-------------------\n";
    }

    Code ask_attempt(std::ostream& output_stream, std::istream& input_stream, const GameOptions& game_options,
                     const Board& board)
    {
        Code attempt{}; // cr�er un code attempt


        output_stream << "Ceci est votre " << board.attempts_and_feedbacks.size() + 1 << " tentative, choisisez "
                      << game_options.number_of_characters_per_code << " caracters entre "
                      << game_options.minimum_allowed_character << " et " << game_options.maximum_allowed_character
                      << ": ";
        attempt.value = ask_string(input_stream); // input stream c'est la siasie de l'utilisateur on va v�rifi� que
                                                  // c'est un string et si ca l'est on la met dans attempt.value
        return attempt;
    }

} // namespace bulls_and_cows