
#pragma once

#include "board.hpp"
#include "game_options.hpp"
#include <vector>

namespace bulls_and_cows {

    struct PossibleSolutions
    {
        std::vector<Code> codes;
    };

    std::vector<Code> generate_all_possibilities(GameOptions game_options);

    Code pick_random_attempt(std::vector<Code>& all_possible);

     void remove_all_incompatible_codes(const GameOptions& game_options, std::vector<Code>& all_possible,
                                       AttemptAndFeedback newcomputerattemp);

} // namespace bulls_and_cows
