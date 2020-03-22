#pragma once
#include <vector>
#include "game_options.hpp"
namespace bulls_and_cows {

    bool checkDoublons(std::vector<char> const& code, char charCode);
    std::vector<char> secretCodeMethod(const GameOptions& game_options);
    void printCode(std::vector<char> const& code);
    void printTableauFinal(std::vector<std::vector<char>> const& tableauFinal);
    bool checkDoublonsString(std::string const& code);
    bool checkErrorAttemps(std::string const& code, const GameOptions& game_options);
    std::vector<char> attempsMethod(const GameOptions& game_options);
    bool checkWin(std::vector<char> secretCodeComputer, std::vector<char> attemps);
    int cowsMethod(std::vector<char> secretCodeComputer, std::vector<char> attemps);
    int bullsMethod(std::vector<char> secretCodeComputer, std::vector<char> attemps);
    void user_plays_against_computer(const GameOptions& game_options);  
    void computer_plays_against_computer(const GameOptions& game_options);
    GameOptions configure_game_options(GameOptions& game_options);
    void play_game();

} // namespace bulls_and_cows
