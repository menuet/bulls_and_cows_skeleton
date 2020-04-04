
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
        int pos = (generate_random_integer(0, static_cast<int> (possible_solutions.codes.size()-1)));
        //oui le static_cast est pas beau mais j'ai pas trouvé mieux pour l'instant
        return possible_solutions.codes[pos];
        //Pas tester mais techniquement ca retourne un attempt aléatoire entre 0 et la taille max du tableau
    }



    void remove_incompatible_codes_from_possible_solutions(const AttemptAndFeedback& attempt_and_feedback, PossibleSolutions& possible_solutions)
    {
        for (size_t i = 0; i < possible_solutions.codes.size()-1; i++)
        {
        Feedback tempfeed =compare_attempt_with_secret_code(possible_solutions.codes[i],attempt_and_feedback.attempt);
            if (tempfeed.bulls != attempt_and_feedback.feedback.bulls || tempfeed.cows != attempt_and_feedback.feedback.cows)
            {
                possible_solutions.codes.erase(possible_solutions.codes.begin() + i);
            }
        }
        //int i = 0;
        ////while (i <= possible_solutions.codes.size())
        ////{
        //    possible_solutions.codes.erase(std::remove_if(
        //        possible_solutions.codes.begin(), possible_solutions.codes.end(),
        //        [&i, attempt_and_feedback, &possible_solutions](Code c) -> bool {
        //            Feedback tempfeed =
        //                compare_attempt_with_secret_code(possible_solutions.codes[i], attempt_and_feedback.attempt);
        //            std::cout << "code to compare : " << possible_solutions.codes[i].value
        //                      << "and comparason for bulls and cows ares : bulls " << tempfeed.bulls << " cows "
        //                      << tempfeed.cows << "\n";
        //            if (tempfeed.bulls != attempt_and_feedback.feedback.bulls ||
        //                tempfeed.cows != attempt_and_feedback.feedback.cows) // Same as (bulls == adf_bulls
        //            {

        //                std::cout << "Iteration numero " << i
        //                          << "Found to remove : " << possible_solutions.codes[i].value << "\n";
        //                i++;
        //                return true;
        //            }

        //            else if (i == possible_solutions.codes.size())
        //                return false;

        //            i++;   
        //            return false;
        //        }));
        ////}
    }

} // namespace bulls_and_cows