#pragma once
#include "board.hpp"
#include "game_options.hpp"
#include "random.hpp"
#include <vector>

namespace bulls_and_cows {

	void returnAllCombination(std::vector<std::string>& allPossibilities, std::string sequence,
                              unsigned int nbrCaractere, unsigned int nbrCaractereCode,
                              const GameOptions& game_options);

    std::vector<std::string> createAllPossibilities(const GameOptions& game_options);

    std::string randomInPossibilities(const std::vector<std::string>& allPossibilities);

        void deleteIncorrectPoissibilities(std::vector<std::string>& allPossibilities, const std::string& codeComputer,
                                       const unsigned int bulls, const unsigned int cows,
                                       const GameOptions& game_options);


} // namespace bulls_and_cows
