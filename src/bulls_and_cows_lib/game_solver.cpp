
#include "game_solver.hpp"

namespace bulls_and_cows {
    //en cours de construction
    /*PossibleSolutions generate_all_possible_codes(const GameOptions& game_options)
    {
        PossibleSolutions all_solutions{};
        Code code{};
        unsigned int full = 0;
        unsigned int x = game_options.number_of_characters_per_code;

        while (full != x)
        {
            std::vector<char> allowed_char;
            for (auto i = game_options.minimum_allowed_character; i <= game_options.maximum_allowed_character;
                 i++) // remplir un vector avec la liste des caracteres autorisés
            {
                allowed_char.push_back(i);
            }

            unsigned int i = 0;

            while (i != game_options.number_of_characters_per_code)
            {
                char temp = generate_random_character(allowed_char.front(),
                                                      allowed_char.back()); // piocher dans les caracteres autorisés

                for (unsigned int j = 0; j < allowed_char.size(); j++) //
                {
                    if (allowed_char[j] == temp)
                    {
                        allowed_char.erase(allowed_char.begin() +
                                           j); // supprimer le caractère du vector contenant les caracteres autorisés
                        code.value.push_back(temp); // ajouter à la string secret_code.value
                        i++;
                    }
                }
            }

            for (auto n : all_solutions.codes)
            {
                if (n.value != code.value)
                {
                    all_solutions.codes.push_back(code);
                    full++;
                }
            }

        }
    }*/

} // namespace bulls_and_cows
