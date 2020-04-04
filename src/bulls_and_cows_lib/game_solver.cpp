
#include "game_solver.hpp"

namespace bulls_and_cows {

    PossibleSolutions generate_all_possible_codes(const GameOptions& game_options)
    {
        PossibleSolutions codes;
        Code code;
        std::vector<char> C{};
        char Test[8] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H'};
        int compteur = 0;
        for (unsigned int i = 0; i < game_options.number_of_characters_per_code; i++)
        {
            C.push_back(game_options.minimum_allowed_character);
        }
        
        for (int i = 0; i <= game_options.maximum_allowed_character - game_options.minimum_allowed_character; i++)
        {
            for (int j = 0; j <= game_options.maximum_allowed_character - game_options.minimum_allowed_character; j++)
            {
                for (int k = 0; k <= game_options.maximum_allowed_character - game_options.minimum_allowed_character;
                     k++)
                {
                    for (int l = 0; l <= game_options.maximum_allowed_character - game_options.minimum_allowed_character;
                         l++)
                    {
                        for (int m= 0 ; m <= game_options.maximum_allowed_character - game_options.minimum_allowed_character; 
                            m++)
                        {
                            for (unsigned int n = 0; n < game_options.number_of_characters_per_code;  n++)
                            {
                                code.value = code.value+C[n];
                            }
                            std ::cout << "Test :" << code.value << "\n";
                            codes.codes.push_back(code);
                            compteur++;
                            code.value = "";
                            C[4] =Test[m] ;
                        }
                        C[3] = Test[l];
                    }
                    C[2] = Test[k];
                }
                C[1] = Test[j];
            }
            C[0] = Test[i];
        }
        std::cout << "Total : " << compteur;
        return codes;
    }
    PossibleSolutions generate_all_possible_codes2(const GameOptions& game_options)
    {
        PossibleSolutions codes; //liste des possibilites que l'on retournera
        Code code;              //Code utilise et change a chaque tour de boucle
        std::vector<int> C{};   //Voir plus loin pour explications
        std::vector<char> convert{};        //liste des caracteres possible ex: si char min: 'B' et char max = 'E' alors la liste contient {'B','C','D','E'}
        int nbr_char = game_options.maximum_allowed_character - game_options.minimum_allowed_character +1;
        int nbr_case = 1;
        //std::cout << "nbr case:" << nbr_case;

        for (unsigned int i = 0; i < game_options.number_of_characters_per_code; i++)
        {
            nbr_case = nbr_case * nbr_char ;        //probleme avec la fonction pow() donc puissance code a la dur
        }
        //std::cout << "nbr possibilities:" << nbr_case << "\n";
        for (unsigned int i = 0; i <= game_options.number_of_characters_per_code; i++)
        {                   //La liste C va etre utilise comme un entier dans la base de valeur égale à notre nombre de solutions
            C.push_back(0); // Si char min = 'A' et char max = 'H' alors les valeurs iront de 0 à 7 ainsi on nos solutions iront de 00000 à 77777 (si 5 lettres/code)
                            // Ainsi 77777 - 00000 (base 8) = 32 768 (base 10) et cela permet d'eviter d'utiliser des boucles imbriqué ou de la recursivité 
                            // Car on peut traiter tous les cas dans une seule et grosse boucle for 
        } //Il y a une case en plus dans le tableau pour eviter un overflow a la derniere iteration ou 77777 devient 100000 et sortirait du tableau

        
        for ( int i = 0 ; i <= game_options.maximum_allowed_character - game_options.minimum_allowed_character ; i++)
        {
            convert.push_back(static_cast<char>(game_options.minimum_allowed_character + i)); // initialisation de la liste de caractere possibles
            //convert[i] = static_cast<char>(game_options.minimum_allowed_character + i);
        }
        

        for (int i = 0; i < nbr_case ; i++) //On effectue un nombre d'iteration egale au nombre de cas
        {
            for (unsigned int j = 0; j < game_options.number_of_characters_per_code ; j++)      //On parcours notre nombre en base(char max - char min)
            {
                if (C[j] == game_options.maximum_allowed_character - game_options.minimum_allowed_character + 1)     
                {                                   //Si un element passe une "dizaine" on repercute la hausse 
                    C[j + 1]++;                     //sur le suivant et on le reinitialise
                    C[j] = 0;                 
                }
            }
            for (unsigned int k = 0; k < game_options.number_of_characters_per_code; k++)
            {
                code.value = code.value + convert[C[k]]; //En fonction du nombre C[] on assigne les lettres correspondantes et on les enregistre dans la liste 
            }                                            //de toutes les combinaisons
            
            codes.codes.push_back(code);
            //std ::cout << "Test :" << code.value << "\n";
            code.value = "";                            //reset de la valeur de la variable pour eviter les superpositions de codes
            C[0] = C[0]+1 ;     //passage a la combinaison suivante

        }
    
        return codes;
    }

    Code pick_random_attempt(const PossibleSolutions& possible_solutions)
    {
        return possible_solutions.codes[generate_random_integer(0, static_cast<int>(possible_solutions.codes.size())-1)]; 
    
    }

    int remove_incompatible_codes_from_possible_solutions(const AttemptAndFeedback& attempt_and_feedback,
                                                           PossibleSolutions& possible_solutions)
    {
        int size = static_cast<int>(possible_solutions.codes.size());  //on parcours toute la liste des combinaisons
        Feedback attempt;
        for (int i = 0; i < size; i++)
        {
            //std ::cout << "Nieme tour:" << i << "\n";
            attempt = compare_attempt_with_secret_code(attempt_and_feedback.attempt,possible_solutions.codes[i]);   //On compare les resultats d'une combinaison choisi au hasard
            if (attempt.bulls != attempt_and_feedback.feedback.bulls ||                                             //avec le code secret, puis on teste tous les codes avec cette meme combinasion
                attempt.cows != attempt_and_feedback.feedback.cows)                                                 //Si on trouve un resultat (feedback) different que celui obtenu avec le Code secret
            {                                                                                                       //on sait que la combinaison n'est pas le code secret on peut donc la supprimer
                possible_solutions.codes.erase(possible_solutions.codes.begin() + i);
                size = size - 1;    //on reduit la taille du tableau car en supprimant la case il faut retrancher un iteration a la boucle for
                i = i - 1;          //on doit faire cela sinon les cases suivant celles supprimées ne seraient pas étudiées.
            }
            else
            {
                std::cout << possible_solutions.codes[i].value << "\n";
            }
        }
        std::cout << "Nbr de combinaison restantes" << size << "\n";
        return size;
    }
} // namespace bulls_and_cows
