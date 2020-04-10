
#pragma once

#include "board.hpp"
#include "game_options.hpp"
#include <vector>

namespace bulls_and_cows {

    struct PossibleSolutions
    {
        std::vector<Code> codes;
    };

    PossibleSolutions generate_all_possible_codes(const GameOptions& game_options);

} // namespace bulls_and_cows
