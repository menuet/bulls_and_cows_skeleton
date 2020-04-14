
#include "game_solver.hpp"
#include "random.hpp"


namespace bulls_and_cows {

    PossibleSolutions generate_all_possible_codes(const GameOptions& game_options)
    {
        PossibleSolutions possible_solution;
        Code first_code;

        // Cr�ation du premier code "AAAA..." n�cessaire � la r�currence
        possible_solution.codes.push_back(
            Code{std::string(game_options.number_of_characters_per_code, game_options.minimum_allowed_character)});

        // Calcul de du nombre total de possibilit� de codes
        const int ecart_lettre = game_options.maximum_allowed_character - game_options.minimum_allowed_character + 1;
        const double tot_nb_code = pow(ecart_lettre, game_options.number_of_characters_per_code);

        // Cr�ation des premi�res variables n�cessaires � la r�currence
        size_t totnb_createdcode = possible_solution.codes.size();
        Code next_code;

        // It�ration jusqu'� remplir tous les codes possibles
        // Cr�ation du next_code en fonction du dernier du vecteur
        while (totnb_createdcode < tot_nb_code)
        {
            // On clear le code � chaque it�ration pour entrer le nouveau code
            next_code.value.clear();
            int nbchar_missingpercode = game_options.number_of_characters_per_code;

            // Si la derni�re lettre n'est pas le "maximum_allowed_character"
            // ON cr�e un le code suivant en incr�mentant la derni�re lettre
            if (possible_solution.codes[totnb_createdcode - 1].value.back() != game_options.maximum_allowed_character)
            {
                // On incr�mente la derni�re lettre de 1
                next_code.value.push_back(char(possible_solution.codes[totnb_createdcode - 1].value.back()) + 1);

                // On ajout les lettres manquantes
                std::string sub2 =
                    possible_solution.codes[totnb_createdcode - 1].value.substr(0, (__int64)nbchar_missingpercode - 1);
                std::reverse(sub2.begin(), sub2.end());

                next_code.value.append(sub2);
                std::reverse(next_code.value.begin(), next_code.value.end());
            }

            // Sinon, on regarde toutes les lettres en partant de la fin
            else
            {
                int q = game_options.number_of_characters_per_code;
                // Tant que la lettre = "maximum_allowed_character"
                // On lui attribue la valeur "minimum_allowed-character"
                while (possible_solution.codes[totnb_createdcode - 1].value[(__int64)q - 1] ==
                       game_options.maximum_allowed_character)
                {
                    next_code.value.push_back(char(game_options.minimum_allowed_character));
                    q--;
                }

                // FIN Tant que
                // On incremente la premi�re lettre diff�rent de "maximum_allowed_character" de 1
                next_code.value.push_back(
                    char(possible_solution.codes[totnb_createdcode - 1].value[(__int64)q - 1] + 1));
                std::string sub3 = possible_solution.codes[totnb_createdcode - 1].value.substr(0, (__int64)q - 1);
                std::reverse(sub3.begin(), sub3.end());

                // On ajoute les lettres pr�c�dentes manquantes
                next_code.value.append(sub3);
                std::reverse(next_code.value.begin(), next_code.value.end());
            }
            // On rajoute le code � la liste en derniere �l�ment et on recontinue la r�currence
            possible_solution.codes.push_back(next_code);
            totnb_createdcode++;
        }
        // std::cout << possible_solution.codes.size() << "\n";
        // for (int o = 0; o < possible_solution.codes.size(); o++)
        //{
        //   std::cout << possible_solution.codes[o].value << "\n";
        //}
        return possible_solution;
    }

    Code pick_random_attempt(const PossibleSolutions& possible_solutions)
    {
        int x = generate_random_integer(0, static_cast<int>(possible_solutions.codes.size() - 1));
        return possible_solutions.codes[x];
    }

    void remove_incompatible_codes_from_possible_solutions(const AttemptAndFeedback& attempt_and_feedback,
                                                           PossibleSolutions& possible_solution)
    {
        PossibleSolutions next;
        for (int i = 0; i < possible_solution.codes.size(); i++)
        {
            if (attempt_and_feedback.feedback.bulls ==
                    compare_attempt_with_secret_code(attempt_and_feedback.attempt, possible_solution.codes[i]).bulls &&
                attempt_and_feedback.feedback.cows ==
                    compare_attempt_with_secret_code(attempt_and_feedback.attempt, possible_solution.codes[i]).cows)
            {
                next.codes.push_back(possible_solution.codes[i]);
            }
        }

        possible_solution = next;
        // for (int o = 0; o < possible_solution.codes.size(); o++)
        //{
        //   std::cout << possible_solution.codes[o].value << "\n";
        //}
        // std::cout << possible_solution.codes.size() << "\n";
        
    }

} // namespace bulls_and_cows
