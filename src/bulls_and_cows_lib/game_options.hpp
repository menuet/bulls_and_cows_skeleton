
#pragma once

#include <iostream>

namespace bulls_and_cows {

    struct GameOptions
    {
        unsigned int max_number_of_attempts{12};
        unsigned int number_of_characters_per_code{5};
        char minimum_allowed_character{'A'};
        char maximum_allowed_character{'H'};
    };

    void display_game_options(const GameOptions& game_options);

    void display_game_options_menu();

    enum class GameOptionsMenuChoice
    {
        Error = -1,
        BackToMain = 0,
        ModifyMaximumNumberOfAttempts = 1,
        ModifyNumberOfCharactersPerCode = 2,
        ModifyMinimumAllowedCharacter = 3,
        ModifyMaximumAllowedCharacter = 4,
        SaveOptions = 5,
        LoadOptions = 6,
    };

    // Ask the user to select an option of the menu
    GameOptionsMenuChoice ask_game_options_menu_choice();

    void manage_game_options(GameOptionsMenuChoice choice, GameOptions& game_options);

    bool save_game_options(std::ostream& output_file_stream, const GameOptions& game_options);

    bool load_game_options(std::istream& input_file_stream, GameOptions& game_options);

} // namespace bulls_and_cows
