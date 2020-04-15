
#pragma once

#include "board.hpp"
#include "game_options.hpp"
#include <vector>

namespace bulls_and_cows {

    struct PossibleSolutions
    {
        std::vector<Code> codes;
    };

        PossibleSolutions generate_all_possible_codes(const GameOptions& game_options)
    {
        PossibleSolutions codes;
        Code code;
        std::vector<char> hiddenCode{} // on crée notre vecteur qu'on va alimenter en caractère
        char Test[8] = {'A','B','C','D','E','F','G','H'}; //on fait un test pour générer entre A à H
        int count=0 // on initialise le compteur
        for (unsigned int i=0; i<game_options.characters_per_code; i++)//on indente les caractères selon le nombre de caractères voulu et défini par l'user dans le game option
        {
            hiddenCode.push_back(game_options.characters_per_code)
        }


        for (unsigned int i=0; i<= game_options.maximum_allowed_characters)
        {
            //TODO imbrication de i à n qu'on va utiliser pour iNcrémenté le “count“, le “codes“
            //count++;
            //codes.push_back(code) qui servira à ajouter les codes
                for (unsigned int j=0; j<= game_options.maximum_allowed_characters - game_options.minimum_allowed_characters; j++)
                {
                }
                    for (unsigned int k=0, k<= game_options.maximum_allowed_characters-game.options.minimum_allowed_characters;k++)
                    {}
                        for (unsigned int l=0, l<= game_options.maximum_allowed_characters-game.options.minimum_allowed_characters; l++)
                        {}
                            for (unsigned int m=0, m<= game_options.maximum_allowed_characters-game.options.minimum_allowed_characters; m++)
                            {}
                                for (unsigned int n=0, n<= game_options.maximum_allowed_characters- game.options.minimum_allowed_characters; n++)
                                {}
                                            
        }

    Code pick_random_attempt(const PossibleSolutions& possible_solutions);
        {
            
            
            
        }
        

    void remove_incompatible_codes_from_possible_solutions(const AttemptAndFeedback& attempt_and_feedback, PossibleSolutions& possible_solutions);
        
        {}

} // namespace bulls_and_cows
