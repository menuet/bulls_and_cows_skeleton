
#include "game_solver.hpp"
#include <algorithm>

namespace bulls_and_cows {
    
    //Fonction recursive, qui permet de trouver toutes les possibilités.
    void returnAllCombination(std::vector<std::string>& allPossibilities, std::string sequence,
                              unsigned int nbrCaractereCode, const GameOptions& game_options,
                              const std::string& allPossibleLetters)
    {
        const unsigned int NOMBRE_DE_CARACTERES =
            game_options.maximum_allowed_character - game_options.minimum_allowed_character + 1;

        if (nbrCaractereCode == 0)
        {
            if (game_options.accept_doublons == false && checkDoublonsString(sequence))
            {
                return;
            }
            else
            {
                allPossibilities.push_back(sequence); 
                return;
            }
        }
        for (unsigned int i = 0; i < NOMBRE_DE_CARACTERES; i++)
        {
            std::string newSequence;
            newSequence = sequence + allPossibleLetters[i];
            returnAllCombination(allPossibilities, newSequence, nbrCaractereCode - 1, game_options, allPossibleLetters);
        }
    }

    //Fonction qui retourne toutes les possibilités afin que l'ia puisse choisir un code.
    std::vector<std::string> createAllPossibilities(const GameOptions& game_options)
    {
        std::string allPossibleLetters;
        std::vector<std::string> allPossibilities;
        for (char i = game_options.minimum_allowed_character; i <= game_options.maximum_allowed_character; i++)
        {
            allPossibleLetters.push_back(i);
        }
        returnAllCombination(allPossibilities, "", game_options.max_number_of_attempts, game_options, 
                             allPossibleLetters);
        std::cout << "terribllelellelele";
        return allPossibilities;
    }

    //Fonction qui retourne un random dans la liste des possibilités.
    std::string randomInPossibilities(const std::vector<std::string>& allPossibilities)
    {
        unsigned int randomIndex =
        generate_random_integer(0, (unsigned int)allPossibilities.size()-1);
        return allPossibilities[randomIndex];
    }

    //Fonction qui supprime toutes les possibilités incorrects
    void deleteIncorrectPoissibilities(std::vector<std::string>& allPossibilities, const std::string& codeComputer,
                                       const unsigned int bulls, const unsigned int cows)
    {
        allPossibilities.erase(std::remove_if(allPossibilities.begin(), allPossibilities.end(),
                                              [codeComputer, bulls, cows](std::string code) 
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
