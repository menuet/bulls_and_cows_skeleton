
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

    void display_game_options(std::ostream& output_stream, const GameOptions& game_options);

    void display_game_options_menu(std::ostream& output_stream);

    GameOptionsMenuChoice ask_option_menu_choice(std::istream& input_stream)
    {
            const int user_choice = ask_int_or_default(input_stream, -1);
            switch (user_choice)
            {
            case 0:
                return MainMenuChoice;
            /*case 1:
                    ModifyMaximumNumberOfAttempts(unsigned int )
                return MainMenuChoice::UserPlaysAgainstComputer;
            case 2:
                return MainMenuChoice::ComputerPlaysAgainstComputer;
            case 3:
                return MainMenuChoice::ConfigureOptions;
            }
            return MainMenuChoice::Error;
            */
    };

    // Ask the user to select an option of the menu
    GameOptionsMenuChoice ask_game_options_menu_choice(std::istream& input_stream);

    bool save_game_options(std::ostream& output_file_stream, const GameOptions& game_options);

    bool load_game_options(std::istream& input_file_stream, GameOptions& game_options);

} // namespace bulls_and_cows
