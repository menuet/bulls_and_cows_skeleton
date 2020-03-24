#pragma once
#include "game_options.hpp"

namespace bulls_and_cows {

    struct FinalBoard
    {
        std::string secretCode{};
        unsigned int bulls{};
        unsigned int cows{};
        FinalBoard(std::string _secretCode, unsigned int _bulls, unsigned int _cows)
            : secretCode(_secretCode), bulls(_bulls), cows(_cows)
        {}
    };

    enum class GameStatus
    {
        Continue = 0,
        Win = 1,
        Lose = 2,
    };

    void play_game();
} // namespace bulls_and_cows
