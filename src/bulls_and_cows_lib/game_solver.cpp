
#include "game_solver.hpp"
#include "random.hpp"
#include <random>

namespace bulls_and_cows {
    // TODO: define the body of the functions declared in game_solver.cpp

    // TODO generate_all_possible_codes function :

    // Afficher toutes les combinaisons de k nombres, avec répétition, pris parmi 0..n-1
    // Nombres de combinaisons:  nb = n^k , avec n = (int)game_options.maximum_allowed_character -
    // (int)game_options.minimum_allowed_character) + 1 On calcule dans une boucle for les combinaisons une a une pour
    // numero=0 jusqu'a numero=n^k-1 et on créé un Code c{} On imbrique une autre boucle for pour i allant de 0 à k =
    // game_options.number_of_characters_per_code les élements sont les k restes successifs de la division par n =
    // (nbPossible de characters) on fait la div euclidienne de v par n à laquelle on ajoute the minimum allowed
    // character, qui est en code ascii (65 pour 'A')

    // Exemple pour les game_options suivantes: les lettres vont de A à D
    // => n = 4 = nbPossible de characters = (int)game_options.maximum_allowed_character -
    // (int)game_options.minimum_allowed_character) + 1 et la taille du code k = 3 =
    // game_options.number_of_characters_per_code

    // si l'on fait (v % n), on aurait pour les 1e combinaisons:
    // 1e combinaison :  000
    // 2e             :  100
    // 3e             :  200
    // 4e             :  300
    // 5e             :  010  etc.

    // si l'on fait (v % n) + game_options.minimum_allowed_character:
    // 1e combinaison :  65 65 65
    // 2e             :  66 65 65
    // 3e             :  67 65 65
    // 4e             :  68 65 65
    // 5e             :  65 66 65  etc.

    // Il faut donc caster en caractère l'opération suivante: (v % n)+game_options.minimum_allowed_character) on obtient: 
    // 1e combinaison :  AAA 
    // 2e             :  BAA 
    // 3e             :  CAA 
    // 4e             :  DAA 
    // 5e             :  ABA  etc.

    PossibleSolutions generate_all_possible_codes(const GameOptions& game_options)
    {
        PossibleSolutions possible_solutions{};
        int numero;
        int n = ((int)game_options.maximum_allowed_character - (int)game_options.minimum_allowed_character) + 1; // nombres de lettres possibles
        int k = game_options.number_of_characters_per_code; // sizeCode
        
        // Nombres de combinaisons:  nb = n^k; 
        int nb = 1;
        for (int i = 0; i < k; i++) nb *= n;

        // On calcule ici les combinaisons une a une jusqu'a la n^k combinaison
        for (numero = 0; numero < nb; numero++)
        {   
            // les élements sont les k restes successifs de la division par n = (nbPossible de characters)
            int v = numero;
            Code newCombination{};  //on créé une combinaison
            newCombination.value.resize(k);  //on resize la taille du code à k = (game_options.number_of_characters_per_code)

            for (int i = 0; i < k; i++)
            { 
                int d= (v % n)+game_options.minimum_allowed_character;  // ajout du code ascii du Minimum Allowed character
                newCombination.value[i] = char(d); //ajout du 1e caractères dans la chaine de caractères pour former le code
                v = v / n;
            }
            possible_solutions.codes.push_back(newCombination); //ajout de la i-ième combinaison générée dans le vector possible_solutions.codes
        }
        return possible_solutions;
    }

    Code pick_random_attempt(const PossibleSolutions& possible_solutions)
    {
        Code codeRandom{};
        int codeSize = static_cast<int>(possible_solutions.codes.size() - 1);
        int indexRandom = generate_random_integer(0, codeSize);

        codeRandom = possible_solutions.codes[indexRandom];

        std::cout << "# Code picked randomnly: " << codeRandom.value;

        return codeRandom;
    }

    void remove_incompatible_codes_from_possible_solutions(const AttemptAndFeedback& attempt_and_feedback,PossibleSolutions& possible_solutions)
    {
        possible_solutions.codes.erase(std::remove_if(possible_solutions.codes.begin(), possible_solutions.codes.end(),
                                   [&](Code& code )
                                        {Feedback feed = compare_attempt_with_secret_code(attempt_and_feedback.attempt, code);
                                            if ((feed.bulls != attempt_and_feedback.feedback.bulls) ||
                                                (feed.cows != attempt_and_feedback.feedback.cows))
                                            {
                                                return true;
                                            }
                                            return false; }),possible_solutions.codes.end());
    }
} // namespace bulls_and_cows
