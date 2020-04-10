
#include "game_solver.hpp"
#include "random.hpp"
#include <vector>
using namespace std; // lifehack

namespace bulls_and_cows {

    // permet de concatener les valeurs du compteur en un seul string
    string concatenate_compteur(const vector<char>& compteur)
    {
        string result = "";
        for (int i = 0; i < compteur.size(); i++)
        {
            result += compteur[i];
        }
        return result;
    }

    // vérifie qu'il n'y a pas de dépacement de lettre
    // renvoi l'index en partant de la droite s'il y a un déplacement, -1 sinon
    int outbreaker(const vector<char>& compteur, const GameOptions& game_options)
    {
        for (int i = (int)compteur.size() - 1; i >= 0; i--) // cast pas jolijoli
        {
            if (compteur[i] > game_options.maximum_allowed_character)
            {
                return i;
            }
        }

        return -1;
    }

    // TODO: define the body of the functions declared in game_solver.cpp
    PossibleSolutions generate_all_possible_codes(const GameOptions& game_options)
    {

        vector<char> compteur; // compteur qui va contenir les chars et nous permettre de compteur
        for (size_t i = 0; i < game_options.number_of_characters_per_code; i++)
        {
            compteur.push_back(game_options.minimum_allowed_character);
        }
        // on vient d'initialiser le compteur. typiquement compteur = ["A", "A", "A", "A", "A",]

        vector<char> finalState; // représente l'état final du compteur
        for (size_t i = 0; i < game_options.number_of_characters_per_code; i++)
        {
            finalState.push_back(game_options.maximum_allowed_character);
        }
        // on vient d'initialiser le finalState. typiquement finalState = ["H", "H", "H", "H", "H",]

        vector<string> combination; // ensemble des combinaisons possible
        combination.push_back(concatenate_compteur(compteur));
        const size_t indexLastElement = compteur.size() - 1; // pour aider à la lisibiliter
        while (compteur != finalState)
        {
            // on incrémente le compteur de 1
            compteur[indexLastElement] = (char)(((int)compteur[indexLastElement]) + 1);
            // cout << "valeur du compteur" <<concatenate_compteur(compteur) << endl;

            // on vérifie qu'il n'y a pas de dépassement dans le compteur
            int indexDebordeur = outbreaker(compteur, game_options); // on optimise les appels de fonctions
            while (indexDebordeur != -1)
            {
                compteur[indexDebordeur] = game_options.minimum_allowed_character; // on boucle ce compteur
                compteur[indexDebordeur - 1] = (char)(((int)compteur[indexDebordeur - 1]) + 1); // on incrémente le plus important
                indexDebordeur = outbreaker(compteur, game_options);
            }

            // on insere la valeur du compteur dans les combinaisons possibles
            combination.push_back(concatenate_compteur(compteur));
        }

        /*for (size_t i = 0; i < combination.size()-2; i+2)
        {
            cout << "valeur de combination:" << combination[i] << " - numero : " << i << endl;
        }*/

        PossibleSolutions p;
        // on encapsule dans les bonnes donnés
        for (size_t i = 0; i < combination.size(); i++)
        {
            Code c;
            c.value = combination[i];
            p.codes.push_back(c);
        }
        return p;
    }

    Code pick_random_attempt(const PossibleSolutions& possible_solutions)
    {
        int index = generate_random_integer(0, (int)possible_solutions.codes.size()-1);
        return possible_solutions.codes[index];
    }

    void remove_incompatible_codes_from_possible_solutions(const AttemptAndFeedback& attempt_and_feedback, PossibleSolutions& possible_solutions) 
    { 
        int size = (int)possible_solutions.codes.size();
        for (int i = 0; i < size; i++)
        {
           
            Feedback TemporaryFeedback = compare_attempt_with_secret_code(possible_solutions.codes[i], attempt_and_feedback.attempt); //on calcule la feedback avec le vrai attempt
           // cout << " TemporaryFeedback done " << endl;
                                                                                                                                      //si le resultat est différent, on delete du tableau
            if (TemporaryFeedback.bulls != attempt_and_feedback.feedback.bulls || TemporaryFeedback.cows != attempt_and_feedback.feedback.cows) // si c est pas le meme feedback
            {
                //cout << "ON ERASE" << endl;
                possible_solutions.codes.erase(possible_solutions.codes.begin()+i); //on delete la possibilitée car elle donne pas le meme feedback
                                                                                    //au lieu de mettre juste i on doit mettre possible_solutions.codes.begin()+i ?
                i--; // !!!!! lorsque on suprime un élément du tableau dans la boucle for il faut faire attention
                size = (int)possible_solutions.codes.size(); // !!!!! on actualise la taille du tableau
                
            }


        }

    }

} // namespace bulls_and_cows
