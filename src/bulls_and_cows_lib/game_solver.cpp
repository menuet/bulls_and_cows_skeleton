
#include "game_solver.hpp"
#include "random.hpp"
#include <algorithm>
#include <string>
#include <iostream>
#include <cctype>
#include <stdlib.h>

namespace bulls_and_cows {

     // TODO: define the body of the functions declared in game_solver.cpp

    void generation_all_codes(const GameOptions& game_options, PossibleSolutions& pls, std::string used_alphabeat, Code& codes)
    {
        for (char temp : used_alphabeat)
        {
            if (codes.value.length() < game_options.number_of_characters_per_code)
            {
                codes.value.push_back(temp);
                //num++;
                generation_all_codes(game_options, pls, used_alphabeat,codes);
                codes.value.pop_back();
            }
            else if (codes.value.length() >= game_options.number_of_characters_per_code)
            {
                pls.codes.push_back(codes);
                break;
            }
            //num--;
        }
    }


       void deleteduplicates(PossibleSolutions& pls)
    {
        auto end = std::remove_if(pls.codes.begin(), pls.codes.end(), [](Code const& code) -> bool {
            // use of lambda expression to pass several parameters to remove_if
            std::string used_chars;
            for (const char& c : code.value)
                if (used_chars.find(c) != std::string::npos)
                {
                    return true;
                }
                else
                {
                    used_chars.push_back(c);
                }
                return false;
        });
        pls.codes.erase(end, pls.codes.end());
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

        //generation_all_codes(1, game_options.number_of_characters_per_code, game_options, avc, used_alphabeat, codes);
        generation_all_codes(game_options, avc, used_alphabeat, codes);


        std::cout << "char from min to max : " << used_alphabeat <<"\n";
        if (game_options.unicate) deleteduplicates(avc);
        return avc;
    }


    Code pick_random_attempt(const PossibleSolutions& possible_solutions)
    {
        int pos = (generate_random_integer(0, static_cast<int> (possible_solutions.codes.size()-1)));
        //oui le static_cast est pas beau mais j'ai pas trouvé mieux pour l'instant
        return possible_solutions.codes[pos];
        //Pas tester mais techniquement ca retourne un attempt aléatoire entre 0 et la taille max du tableau
    }


    void remove_incompatible_codes_from_possible_solutions(const AttemptAndFeedback& attempt_and_feedback, PossibleSolutions& possible_solutions)
    {
        auto it = std::remove_if(possible_solutions.codes.begin(), possible_solutions.codes.end(), 
            [attempt_and_feedback](Code &c) -> bool {
                        Feedback tempfeed = compare_attempt_with_secret_code(c, attempt_and_feedback.attempt);
                        if (tempfeed.bulls != attempt_and_feedback.feedback.bulls || tempfeed.cows != attempt_and_feedback.feedback.cows) // Same as (bulls == adf_bulls
                        {
                            return true;
                        }
                        return false;
                    });
        possible_solutions.codes.erase(it, possible_solutions.codes.end());
    }

} // namespace bulls_and_cows