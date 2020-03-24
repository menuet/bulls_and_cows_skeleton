#pragma once
#include "game_options.hpp"
#include <string>

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
        Continue=0,
        Win=1,
        Lose=2,
    };

    bool checkDoublons(std::string const& code, char const& charCode);
    std::string giveCode(const GameOptions& game_options);
    void printCode(std::string const& code);
    bool checkDoublonsString(std::string const& code);
    bool checkErrorAttemps(std::string const& code, const GameOptions& game_options);
    std::string askCodeUser(const GameOptions& game_options);
    unsigned int giveCowsNumber(std::string const& secretCodeComputer, std::string const& code);
    unsigned int giveBullsNumber(std::string const& secretCodeComputer, std::string const& code);
    bool checkWin(std::string const& secretCodeComputer, std::string const& code);
    std::string askCodeComputer(const GameOptions& game_options, std::vector<FinalBoard> const& finalBoard);

    void play_game();
} // namespace bulls_and_cows
