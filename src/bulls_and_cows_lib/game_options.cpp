#include "game_options.hpp"
#include "input.hpp"
#include <fstream>
#include <iostream>
#include <string>

namespace bulls_and_cows {

    void display_game_options(std::ostream& output_stream, const GameOptions& game_options)
    {
        output_stream << "Game option: \n";
        output_stream << "Character number allowed" << game_options.number_of_characters_per_code << "\n";
        output_stream << "Attempt number allowed" << game_options.max_number_of_attempts << "\n";
        output_stream << "Characters: " << game_options.minimum_allowed_character << " to "
                      << game_options.maximum_allowed_character << "\n";
    }

    void display_game_options_menu(std::ostream& output_stream)
    {
        output_stream << "Configure Options\n";
        output_stream << "0 - Back to main menu\n";
        output_stream << "1 - Modify Maximum number of attempts per game\n";
        output_stream << "2 - Modify Number of characters in a code\n";
        output_stream << "3 - Modify Minimum allowed character\n";
        output_stream << "4 - Modify Maximum allowed character\n";
        output_stream << "5 - Save options\n";
        output_stream << "6 - Load options\n";
        output_stream << "Choose between these options ";
    }
    GameOptionsMenuChoice ask_game_options_menu_choice(std::istream& input_stream)
    {
        switch (ask_int_or_default(input_stream, -1))
        {
        case -1:
            return GameOptionsMenuChoice::Error;

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
        default:
            return GameOptionsMenuChoice::Error;
        }
    }
    bool save_game_options(std::ostream& output_file_stream, const GameOptions& game_options)
    {
        output_file_stream << "max_number_of_attempts=" << game_options.max_number_of_attempts << "\n"
                           << "number_of_characters_per_code=" << game_options.number_of_characters_per_code << "\n"
                           << "minimum_allowed_character=" << game_options.minimum_allowed_character << "\n"
                           << "maximum_allowed_character=" << game_options.maximum_allowed_character << "\n";
        return true;
    }
    void option_ModifyMaximumNumberOfAttempts(GameOptions& game_options)
    {

        std::cout << "Attempt number allowed:";
        const int attemptNumber = ask_int_or_default(std::cin, -1);
        if (attemptNumber < 1 || attemptNumber > 12)
        {
            std::cout << "The attempt number should be lower or equal to 12";
        }
        else
        {
            game_options.max_number_of_attempts = attemptNumber;
        }
    }

    void option_ModifyNumberOfCharactersPerCode(GameOptions& game_options)
    {

        std::cout << "Characters number allowed ";
        const int charactersNumber = ask_int_or_default(std::cin, -1);
        if (charactersNumber < 1 || charactersNumber > 8)
        {
            std::cout << "The characters number should be equal or lower to 8 \n";
        }
        else
        {
            game_options.number_of_characters_per_code = charactersNumber;
        }
    }

    void option_ModifyMinimumAllowedCharacter(GameOptions& game_options)
    {
        std::cout << "Minimum character allowed ";
        const char characterMinAllowed = ask_char_or_default(std::cin, 0);
        if (characterMinAllowed > game_options.maximum_allowed_character)
        {
            std::cout << "Choose minimum allowed character";
        }
        else
        {
            game_options.minimum_allowed_character = characterMinAllowed;
        }
    }
    void option_ModifyMaximumAllowedCharacter(GameOptions& game_options)
    {
        std::cout << "Maximum character allowed ";
        const char characterMaxAllowed = ask_char_or_default(std::cin, 0);
        if (characterMaxAllowed < game_options.minimum_allowed_character)
        {
            std::cout << "Choose maximum allowed character";
        }
        else
        {
            game_options.maximum_allowed_character = characterMaxAllowed;
        }
    }

    bool load_game_options(std::istream& input_file_stream, GameOptions& game_options)
    {
        std::string line;

        while (std::getline(input_file_stream, line))
        {
            std::size_t board = line.find("=");
            std::string token = line.substr(0, board);
            std::string numb = line.substr(board + 1);

            if (token == "max_number_of_attempts")
                game_options.max_number_of_attempts = std::atoi(numb.c_str());

            else if (token == "number_of_characters_per_code")
                game_options.number_of_characters_per_code = std::atoi(numb.c_str());

            else if (token == "minimum_allowed_character")
                game_options.minimum_allowed_character = numb[0];

            else if (token == "maximum_allowed_character")
                game_options.maximum_allowed_character = numb[0];
            else
            {
                std::cout << "Files problem";
                return false;
            }
        }

        return true;
    }

} // namespace bulls_and_cows