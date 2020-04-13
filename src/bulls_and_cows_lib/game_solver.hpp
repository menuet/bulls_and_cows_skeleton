
#pragma once

#include "board.hpp"
#include "game_options.hpp"
#include "game.hpp"
#include <vector>

namespace bulls_and_cows {

    struct PossibleSolutions
    {
        std::vector<std::string> codes;
    };

    PossibleSolutions generate_all_possible_codes(const GameOptions& game_options);

    Code pick_random_attempt(const PossibleSolutions& possible_solutions);

    void remove_incompatible_codes_from_possible_solutions(const AttemptAndFeedback& attempt_and_feedback,
                                                           PossibleSolutions& possible_solutions);


	void generate_next_code(PossibleSolutions& dico_all_codes, std::string sequence, unsigned int  number_distinct_alphabet_char,
		unsigned int nbrCaractereCode, std::string alphabet);
	//recursif
	PossibleSolutions generate_all_codes(const GameOptions& game_options);
	//non recursif
	PossibleSolutions generate_all_possible_codes(const GameOptions& game_options);
	void erase_invalid_solutions(PossibleSolutions& dico_all_codes, const FinalBoard& current_attempt);

} // namespace bulls_and_cows
