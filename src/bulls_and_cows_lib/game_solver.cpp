
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

        //FIRST SOLUTION MAIS LOIN D ETRE LA PLUS OPTIMALE

        //for (size_t i = 0; i < possible_solutions.codes.size()-1; i++)
        //{
        //Feedback tempfeed =compare_attempt_with_secret_code(possible_solutions.codes[i],attempt_and_feedback.attempt);
        //    if (tempfeed.bulls != attempt_and_feedback.feedback.bulls || tempfeed.cows != attempt_and_feedback.feedback.cows)
        //    {
        //        possible_solutions.codes.erase(possible_solutions.codes.begin() + i);
        //    }
        //}

        //SECOND SOLUTION, L TULISATION D'UN REMOVE IF EST BIEN SUR LA SOLUTION LA PLUS OPTIMALE APRES "DES HEURES DE RECHERCHE" AVEC MON COLLEGUE GABIN CELA FONCTIONNE ENFIN

        //Plusieurs tuto du web utlisaient un remove if dans un erase, mais cela ne fonctionnait pas pour mon code surement parce qu'il était faux,
        //Pour la petite explication, le remove_if retourne un iterateur, on parcours donc le tableau du begin() a sa end() et pour chaque Code c de celui-ci remplissant la condition,
        //on implémente l'iterateur avec la position du Code dans le vecteur. 
        //Le & permet de faire rérérence et de pointer directement sur l'élement
        //On efface tous les elements pointés avec le erase et voila AMEN... 

        auto it = std::remove_if(possible_solutions.codes.begin(), possible_solutions.codes.end(), 
            [attempt_and_feedback, &possible_solutions](Code &c) -> bool {
                        Feedback tempfeed = compare_attempt_with_secret_code(c, attempt_and_feedback.attempt);
                        //std::cout << "code to compare : " << c.value
                        //          << "and comparason for bulls and cows ares : bulls " << tempfeed.bulls << " cows "
                        //          << tempfeed.cows << "\n";
                        if (tempfeed.bulls != attempt_and_feedback.feedback.bulls || tempfeed.cows != attempt_and_feedback.feedback.cows) // Same as (bulls == adf_bulls
                        {
                            //std::cout << "Iteration numero " << i
                            //std::cout << "Found to remove : " << c.value << "\n";
                            return true;
                        }
                        return false;
                    });

        possible_solutions.codes.erase(it, possible_solutions.codes.end());
    }

} // namespace bulls_and_cows