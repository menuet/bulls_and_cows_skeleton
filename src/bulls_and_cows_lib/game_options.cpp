
#include "game_options.hpp"
#include "input.hpp"
#include <fstream>
#include <iostream>
#include <string>

namespace bulls_and_cows {

    void display_game_options(std::ostream& output_stream, const GameOptions& game_options)
    {
        output_stream << " Here are the current game_options : " << std::endl;
        output_stream << "Maximum number of attempt per game " << game_options.max_number_of_attempts << std::endl;
        output_stream << "Number of characters in a code is " << game_options.number_of_characters_per_code
                      << std::endl;
        output_stream << "The characters can take any letter from" << game_options.minimum_allowed_character << " to "
                      << game_options.maximum_allowed_character << std::endl;
    }

    void display_game_options_menu(std::ostream& output_stream)
    {
        output_stream << "Configure Options" << std::endl;
        output_stream << "0 - Back to main menu" << std::endl;
        output_stream << "1 - Modify maximum number of attempts per game" << std::endl;
        output_stream << "2 - Modify number of characters in a code" << std::endl;
        output_stream << "3 - Modify minimum allowed character" << std::endl;
        output_stream << "4 - Modify maximum allowed character" << std::endl;
        output_stream << "5 - Save options" << std::endl;
        output_stream << "6 - Load options" << std::endl;
        output_stream << "What is your choice ? " << std::endl;
    }

    GameOptionsMenuChoice ask_game_options_menu_choice(std::istream& input_stream)
    {
        const int user_choice = ask_int_or_default(input_stream, -1);
        switch (user_choice)
        {
        case 0:
            return GameOptionsMenuChoice::BackToMain;
        case 1:
            return GameOptionsMenuChoice::ModifyMaximumNumberOfAttempts;
        case 2:
            return GameOptionsMenuChoice::ModifyNumberOfCharactersPerCode;
        case 3:
            return GameOptionsMenuChoice::ModifyMinimumAllowedCharacter;
        case 4:
            return GameOptionsMenuChoice::ModifyMaximumAllowedCharacter;
        case 5:
            return GameOptionsMenuChoice::SaveOptions;
        case 6:
            return GameOptionsMenuChoice::LoadOptions;
        }
        return GameOptionsMenuChoice::Error;
    }

    bool save_game_options(std::ostream& output_file_stream, const GameOptions& game_options)
    {
        std::string options{};
        options = std::to_string(game_options.max_number_of_attempts) + "\n" +
                  std::to_string(game_options.number_of_characters_per_code) + "\n" +
                  std::to_string(game_options.minimum_allowed_character) + "\n" +
                  std::to_string(game_options.maximum_allowed_character);
        if (output_file_stream)
        {
            output_file_stream << options;
            return true;
        }

        return false;
    }

    /*
    bool load_game_options(std::ifstream& input_file_stream, GameOptions& game_options)
    {
        if (input_file_stream)
        {
            std::string ligne{};
            game_options.max_number_of_attempts = getline(input_file_stream, ligne);
            game_options.number_of_characters_per_code = std::getline(input_file_stream, ligne);
            game_options.minimum_allowed_character = std::getline(input_file_stream, ligne);
            game_options.maximum_allowed_character = std::getline(input_file_stream, ligne);
            return true;
        }

        return false;
    }*/
} // namespace bulls_and_cows
