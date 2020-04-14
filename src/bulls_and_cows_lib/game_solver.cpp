
#include "game_solver.hpp"
#include "random.hpp"
#include <iostream>
#include <vector>

namespace bulls_and_cows {

	// fonction récursive qui genere tous les codes possibles (valide ou non)
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
        PossibleSolutions final_possible_code{};    // contiendra tous les codes autorisés
        Code code;
        auto nb_char_code = game_options.number_of_characters_per_code;

        all_possible_code(1, nb_char_code, game_options, var_all_possible_codes,
                          code); // on genère tous les codes possibles ici (on les stock dans var_all_possible_code)

        for (unsigned int i = 0; i < var_all_possible_codes.codes.size(); i++)
        {
             // on séléctionne seulement les codes valides (sans doublon)
            
                final_possible_code.codes.push_back(
                var_all_possible_codes.codes[i]); // on insert le code valide dans le vecteur final
            
        }

        return final_possible_code;
    }

}



