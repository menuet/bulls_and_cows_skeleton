#pragma once
#include "game_options.hpp"
#include "game.hpp"

namespace bulls_and_cows {

    void boardGame(std::vector<FinalBoard> const& finalBoard, const GameOptions& game_options, unsigned int const& count);

} // namespace bulls_and_cows
