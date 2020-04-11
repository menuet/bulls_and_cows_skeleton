
#pragma once

#include "board.hpp"
#include "random.hpp"
#include "game_options.hpp"
#include <vector>

namespace bulls_and_cows {

    struct PossibleSolutions
    {
        std::vector<Code> codes{};
    };


    void all_possible_code(int num, int max, const GameOptions& game_options, PossibleSolutions& var_all_possible_codes,
                           Code codes); //fonction récursive qui genere tous les codes possibles (valide ou non)

    PossibleSolutions generate_all_possible_codes(const GameOptions& game_options); //fonction qui genere tous les codes possibles (valide uniquement)

    Code pick_random_attempt(const PossibleSolutions& possible_solutions);

    void remove_incompatible_codes_from_possible_solutions(const AttemptAndFeedback& attempt_and_feedback,
                                                           PossibleSolutions& possible_solutions, const Board& board);

} // namespace bulls_and_cows
