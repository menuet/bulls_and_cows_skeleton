
#pragma once
#include <vector>
#include "game_options.hpp"

using namespace std;


namespace bulls_and_cows {
    void play_game();
    bool check_duplicates(vector<char> const& code, int current_index);
    vector<char> generate_secret_code(const GameOptions& game_options);
    vector<char> do_attempt(const GameOptions& game_options);
    unsigned int count_bull(vector<char> const& attempt, vector<char> const& code);
    unsigned int count_cow(vector<char> const& attempt, vector<char> const& code);
    bool check_input(string const& attempt, const GameOptions& game_options);

} // namespace bulls_and_cows
