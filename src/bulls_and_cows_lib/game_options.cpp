
#include "game_options.hpp"
#include "input.hpp"
#include <fstream>
#include <iostream>
#include <string>

namespace bulls_and_cows {

    void display_game_options(std::ostream& output_stream, const GameOptions& game_options)
    {
        output_stream << "Here are the current game options:" << std::endl;
        output_stream << "The maximum number of attemptper game is :" << game_options.max_number_of_attempts
                      << std::endl;
        output_stream << "The number of characters per code is:" << game_options.number_of_characters_per_code
                      << std ::endl;
        output_stream << "The range of allowed characters varies from '" << game_options.minimum_allowed_character
                      << " ' to '" << game_options.maximum_allowed_character << "' " << std::endl;
    }
    void display_game_options_menu(std::ostream& output_stream)
    {
        output_stream << "Configure options" << std::endl;
        output_stream << "0 - Go back to Menu" << std::endl;
        output_stream << "1 - Modify Maximum number of attempts per code" << std::endl;
        output_stream << "2 - Modify Number of characters in a code" << std::endl;
        output_stream << "3 - Modify Maximum allowed characters" << std::endl;
        output_stream << "4 - Modify Minimum allowed characters" << std::endl;
        output_stream << "5 - Save  options" << std::endl;
        output_stream << " 6 - Load  options" << std::endl;
        output_stream << " What is your choice ?";
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
    bool save_game_options(std::ofstream& output_file_stream, const GameOptions& game_options)
    {
        if (output_file_stream)
        {
            output_file_stream << game_options.max_number_of_attempts << "\n"
                               << game_options.number_of_characters_per_code << "\n"
                               << game_options.minimum_allowed_character << "\n"
                               << game_options.maximum_allowed_character << std::endl;
            return true;
        }
        return false;
    }
    bool load_game_options(std::ifstream& input_file_stream, GameOptions& game_options)
    {
        if (input_file_stream)
        {
            std::string ligne{};
            std::getline(input_file_stream, ligne);
            unsigned int nb_attempt = std::stoi(ligne);
            game_options.max_number_of_attempts = nb_attempt;

            std::getline(input_file_stream, ligne);
            unsigned int nb_character = std::stoi(ligne);
            game_options.number_of_characters_per_code = nb_character;

            std::getline(input_file_stream, ligne);
            char min_character = ligne[0];
            game_options.minimum_allowed_character = min_character;

            std::getline(input_file_stream, ligne);
            char max_character = ligne[0];
            game_options.maximum_allowed_character = max_character;
            return true;
        }
        return false;
    }

} // namespace bulls_and_cows
