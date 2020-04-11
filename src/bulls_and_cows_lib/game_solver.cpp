
#include "game_solver.hpp"

namespace bulls_and_cows {
    // en cours de construction

    // fonction r�cursive qui genere tous les codes possibles (valide ou non)
    void all_possible_code(int num, int max, const GameOptions& game_options, PossibleSolutions& var_all_possible_codes,
                           Code codes)
    {
        std::string all_allowed_char;

        for (char c = game_options.minimum_allowed_character; c <= game_options.maximum_allowed_character; c++)
        {
            all_allowed_char.push_back(c);
        }

        for (char temp : all_allowed_char)
        {
            if (num <= max)
            {
                codes.value.push_back(temp);
                num++;
                all_possible_code(num, max, game_options, var_all_possible_codes, codes);
                codes.value.pop_back();
            }
            else if (num > max)
            {
                var_all_possible_codes.codes.push_back(codes);
                break;
            }
            num--;
        }
    }

    // fonction qui genere tous les codes possibles (valide uniquement)
    PossibleSolutions generate_all_possible_codes(const GameOptions& game_options)
    {
        PossibleSolutions var_all_possible_codes{}; // contiendra tous les codes possibles (doublons compris)
        PossibleSolutions final_possible_code{};    // contiendra tous les codes autoris�s
        Code code;
        auto nb_char_code = game_options.number_of_characters_per_code;

        all_possible_code(1, nb_char_code, game_options, var_all_possible_codes,
                          code); // on gen�re tous les codes possibles ici (on les stock dans var_all_possible_code)

        for (unsigned int i = 0; i < var_all_possible_codes.codes.size(); i++)
        {
            if (bulls_and_cows::validate_attempt(
                    game_options,
                    var_all_possible_codes.codes[i])) // on s�l�ctionne seulement les codes valides (sans doublon)
            {
                final_possible_code.codes.push_back(
                    var_all_possible_codes.codes[i]); // on insert le code valide dans le vecteur final
            }
        }

        return final_possible_code;
    }

    Code pick_random_attempt(const PossibleSolutions& possible_solutions)
    {
        int min = 0;
        int max = (int)possible_solutions.codes.size() - 1; // cast
        int rand = generate_random_integer(min, max);

        return possible_solutions.codes[rand];
    }

    void remove_incompatible_codes_from_possible_solutions(const AttemptAndFeedback& attempt_and_feedback,
                                                           PossibleSolutions& possible_solutions, const Board& board)
    {
        Feedback temp_feedback{};
        for (auto temp : possible_solutions.codes)
        {
            auto i = 0;
            // je compare chaque code avec le code secret, en r�cup�rant le nb de bulls et cows
            temp_feedback = compare_attempt_with_secret_code(temp, board.secret_code); 

            // si le nb de bulls et cows du code qui vient d'�tre compar� est �gal au nb de bulls et cows de l'attempt original, alors on vire ce code des solutions possibles
            if (temp_feedback.bulls == attempt_and_feedback.feedback.bulls && 
                temp_feedback.cows == attempt_and_feedback.feedback.cows)
            {
                possible_solutions.codes.erase(possible_solutions.codes.begin()+i);
            }
            i++;
        }
    }

} // namespace bulls_and_cows
