
#include "game_solver.hpp"
#include "random.hpp"

namespace bulls_and_cows {
    // TODO: define the body of the functions declared in game_solver.cpp
    PossibleSolutions generate_all_possible_codes(const GameOptions& game_options)
    {
        PossibleSolutions pls{}; // Comme l'état de mon cerveau pour faire cette fonction
        std::string used_alphabeat;
        //Génération de la chaine avec toutes les lettres du min a la max
        for (char c = game_options.minimum_allowed_character; c <= game_options.maximum_allowed_character; c++)
        {
           used_alphabeat.push_back(c);
        }

        //for (char temp : used_alphabeat)
        //{

        //}

        std::cout << "char from min to max : " << used_alphabeat <<"\n";
        return pls;
    }

    Code pick_random_attempt(const PossibleSolutions& possible_solutions)
    {
        int pos = (generate_random_integer(0, static_cast<int> (possible_solutions.codes.size())));
        //oui le static_cast est pas beau mais j'ai pas trouvé mieux pour l'instant
        return possible_solutions.codes[pos];
        //Pas tester mais techniquement ca retourne un attempt aléatoire entre 0 et la taille max du tableau
    }

} // namespace bulls_and_cows
