
#include "game_solver.hpp"
#include "random.hpp"

namespace bulls_and_cows {

     // TODO: define the body of the functions declared in game_solver.cpp

    void recursif(int num, int max, const GameOptions& game_options, PossibleSolutions& pls, std::string used_alphabeat,
                  Code codes)
    {
        for (char temp : used_alphabeat)
        {
            if (num <= max)
            {
                codes.value.push_back(temp);
                num++;

                recursif(num, max, game_options, pls, used_alphabeat, codes);
                codes.value.pop_back();
            }
            else if (num > max)
            {
                pls.codes.push_back(codes);
                //std::cout << "Vecteur suivant ajouté : " << codes.value << "\n";
                //num--;
                break;
            }
            num--;
        }
    }

    PossibleSolutions generate_all_possible_codes(const GameOptions& game_options)
    {
        PossibleSolutions avc{}; // Comme l'état de mon cerveau pour faire cette fonction
        std::string used_alphabeat;
        //Génération de la chaine avec toutes les lettres du min a la max
        for (char c = game_options.minimum_allowed_character; c <= game_options.maximum_allowed_character; c++)
        {
           used_alphabeat.push_back(c);
        }
        Code codes; 
        recursif(1, game_options.number_of_characters_per_code, game_options, avc, used_alphabeat, codes);

        std::cout << "char from min to max : " << used_alphabeat <<"\n";
        return avc;
    }


    Code pick_random_attempt(const PossibleSolutions& possible_solutions)
    {
        int pos = (generate_random_integer(0, static_cast<int> (possible_solutions.codes.size())));
        //oui le static_cast est pas beau mais j'ai pas trouvé mieux pour l'instant
        return possible_solutions.codes[pos];
        //Pas tester mais techniquement ca retourne un attempt aléatoire entre 0 et la taille max du tableau
    }


    void remove_incompatible_codes_from_possible_solutions(const AttemptAndFeedback& attempt_and_feedback, PossibleSolutions& possible_solutions)
    {
        for (Code codes : possible_solutions.codes)
        {
            AttemptAndFeedback tempattemp{};
            tempattemp.feedback = bulls_and_cows::compare_attempt_with_secret_code(codes, ???);

        }
    }
} // namespace bulls_and_cows
