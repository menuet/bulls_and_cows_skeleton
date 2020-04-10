
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

    enum class CheckInput
    {
        WrongNumberChars,
        Duplicate,
        CharacterOutOfRange,
        Valid,
    };

    void play_game();
    Code generate_secret_code(const GameOptions& game_options);
    Code do_attempt(std::istream& input_stream, const GameOptions& game_options);
    unsigned int count_bull(Code const& attempt, Code const& code);
    unsigned int count_cow(Code attempt_variable, Code code);
    bool check_duplicates(std::string code);
    CheckInput check_input(std::string const& attempt, const GameOptions& game_options);
    bool check_attempt(Code const& attempt, Historic const& historic);


} // namespace bulls_and_cows
