
#include "game_solver.hpp"

namespace bulls_and_cows {
    // en cours de construction
    // k parmi n --> k étant la longueur du code et n étant le le nb de possiblité pour chaque char du code

    unsigned int Factoriel(unsigned int n)
    {
        return n > 1 ? (n * Factoriel(n - 1)) : 1;
    }

    Code generate_random_code(const GameOptions& game_options)
    {
        Code code{};
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

            for (unsigned int j = 0; j < allowed_char.size(); j++)
            {
                if (allowed_char[j] == temp)
                {
                    allowed_char.erase(allowed_char.begin() +
                                       j);      // supprimer le caractère du vector contenant les caracteres autorisés
                    code.value.push_back(temp); // ajouter à la string secret_code.value
                    i++;
                }
            }
        }

        return code;
    }

    PossibleSolutions generate_all_possible_codes(const GameOptions& game_options)
    {
        PossibleSolutions all_solutions{};
        Code code{};
        unsigned int cpt = 0;
        auto n = game_options.maximum_allowed_character - game_options.minimum_allowed_character + 1;
        auto k = game_options.number_of_characters_per_code;
        unsigned int full = Factoriel(n) / Factoriel(n - k); // n! /(n-k)! = nb arrangement possible


        while (cpt != full) // tant que toutes les possiblités de code n'ont pas été généré
        {
            code = generate_random_code(game_options);
            std::cout << "\n" << code.value << "\n";

            // verification de la présence ou non du code generé dans le vecteur all_solutions.codes

           /* for (unsigned int i = 0; i < all_solutions.codes.size(); i++)
            {
                if (code.value != all_solutions.codes[i].value)
                {
                    all_solutions.codes.push_back(code);
                    cpt++;
                }
            }*/
            for (Code temp : all_solutions.codes)
            {
                if (code.value != temp.value)
                {
                    all_solutions.codes.push_back(code);
                    cpt++;
                }
            }
        }

        return all_solutions;
    }

} // namespace bulls_and_cows
