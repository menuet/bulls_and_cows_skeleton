
#pragma once

#include <iostream>

namespace bulls_and_cows {

    struct GameOptions
    {
        unsigned int max_number_of_attempts{12};
        unsigned int number_of_characters_per_code{5};
        char minimum_allowed_character{'A'};
        char maximum_allowed_character{'H'};
        bool allow_duplicate{true};
    };    

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
        AllowDuplicate = 7,
    };

    void display_game_options(std::ostream& output_stream, const GameOptions& game_options);

    void display_game_options_menu(std::ostream& output_stream);

    bool adjust_char_number(GameOptions& game_options);

    // Ask the user to select an option of the menu
    GameOptionsMenuChoice ask_game_options_menu_choice(std::istream& input_stream);

    void manage_game_options(GameOptionsMenuChoice choice, GameOptions& game_options);

    bool save_game_options(const GameOptions& game_options, std::ostream& output_stream);

    bool load_game_options(GameOptions& game_options);

} // namespace bulls_and_cows
