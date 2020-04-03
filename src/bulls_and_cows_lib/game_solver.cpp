
#include "game_solver.hpp"
#include <algorithm>

namespace bulls_and_cows {
    
    //Fonction recursive, qui permet de trouver toutes les possibilités.
    void returnAllCombination(std::vector<std::string>& allPossibilities, std::string sequence, unsigned int nbrCaractere, unsigned int nbrCaractereCode, const GameOptions& game_options)
    {
        if (nbrCaractereCode == 0)
        {
            if (game_options.accept_doublons == false && checkDoublonsString(sequence))
            {
                return;
            }
            else
                allPossibilities.push_back(sequence);
            return;
        }
        for (unsigned int i = 0; i < nbrCaractere; i++)
        {
            std::string newSequence;
            newSequence = sequence + allPossibilities[0][i];
            returnAllCombination(allPossibilities, newSequence, nbrCaractere, nbrCaractereCode - 1, game_options);
        }
    }

    //retourne toutes les possibilités pour l'ia.
    std::vector<std::string> createAllPossibilities(const GameOptions& game_options)
    {
        const unsigned int NOMBRE_DE_CARACTERES =
            game_options.maximum_allowed_character - game_options.minimum_allowed_character + 1;

        std::string premierCode;
        std::vector<std::string> allPossibilities;
        for (char i = game_options.minimum_allowed_character; i <= game_options.maximum_allowed_character; i++)
        {
            premierCode.push_back(i);
        }
        allPossibilities.push_back(premierCode);
        returnAllCombination(allPossibilities, "", NOMBRE_DE_CARACTERES, game_options.number_of_characters_per_code, game_options);
        allPossibilities.erase(allPossibilities.begin()); //permet de supprimer l'initilisation utile à ma fonction recursive
        return allPossibilities;
    }

    //retourne un random dans la liste des possibilités.
    std::string randomInPossibilities(const std::vector<std::string>& allPossibilities)
    {
        unsigned int PREMIER_INDEX_DU_VECTOR = 0;
        unsigned int randomIndex =
        generate_random_integer(PREMIER_INDEX_DU_VECTOR, (unsigned int)allPossibilities.size()-1);
        return allPossibilities[randomIndex];
    }

    //Supprime toutes les possibilités incorrects
    void deleteIncorrectPoissibilities(std::vector<std::string>& allPossibilities, const std::string& codeComputer,
                                       const unsigned int bulls, const unsigned int cows,
                                       const GameOptions& game_options)
    {
        allPossibilities.erase(std::remove_if(allPossibilities.begin(), allPossibilities.end(),
                                              [codeComputer, bulls, cows, game_options](std::string code) 
                                              {
                                                      if (giveBullsNumber(codeComputer, code) != bulls ||
                                                          giveCowsNumber(codeComputer, code) != cows)
                                                      {
                                                          return true;
                                                      }
                                                      else
                                                      {
                                                          return false;
                                                      }
                                              }), allPossibilities.end());
    }
} // namespace bulls_and_cows
