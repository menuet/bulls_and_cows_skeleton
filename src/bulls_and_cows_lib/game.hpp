
#pragma once
#include <vector>
#include "game_options.hpp"


namespace bulls_and_cows {

    struct Code
    {
        std::string value{};
    };

    struct AttemptBullsCows
    {
        Code attempt{};
        unsigned int bulls{};
        unsigned int cows{};
    };

    struct Historic
    {
        std::vector<AttemptBullsCows> value{};
    };

    void play_game();
    bool check_duplicates(Code const& code, int current_index);
    Code generate_secret_code(const GameOptions& game_options);
    Code do_attempt(const GameOptions& game_options);
    unsigned int count_bull(Code const& attempt, Code const& code);
    unsigned int count_cow(Code const& attempt, Code const& code);
    bool check_input(std::string const& attempt, const GameOptions& game_options);
    bool check_attempt(Code const& attempt, Historic const& historic);

} // namespace bulls_and_cows
