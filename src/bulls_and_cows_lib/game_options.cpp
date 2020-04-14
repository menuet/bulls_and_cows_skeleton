
#include "game_options.hpp"
#include "input.hpp"
#include <iostream>
#include <string>
#include <fstream>
using namespace std;

namespace bulls_and_cows {

    void display_game_options(std::ostream& output_stream, const GameOptions& game_options)
    {
        output_stream << "Here are the current game_options:\n"
                         "Maximum number of attempts per game: "
                      << game_options.max_number_of_attempts
                      << "\n"
                         "Number of characters in a code: "
                      << game_options.number_of_characters_per_code
                      << "\n"
                         "Range of allowed characters: from '"
                      << game_options.minimum_allowed_character << "' to '" << game_options.maximum_allowed_character
                      << "'\n";
    }

    void display_game_options_menu(std::ostream& output_stream)
    {
        output_stream << "Configure Options\n"
                         "0 - Back to main menu\n"
                         "1 - Modify Maximum number of attempts per game\n"
                         "2 - Modify Number of characters in a code\n"
                         "3 - Modify Minimum allowed character\n"
                         "4 - Modify Maximum allowed character\n"
                         "5 - Save options\n"
                         "6 - Load options\n"
                         "What is your choice ? ";
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

        bool save_game_options(std::ostream & output_file_stream, const GameOptions& game_options)
        {
            output_file_stream << "max_number_of_attempts=" 
                               << game_options.max_number_of_attempts
                               << "\n"
                                  "number_of_characters_per_code=" 
                               << game_options.number_of_characters_per_code
                               << "\n"
                                  "minimum_allowed_character=" 
                               << game_options.minimum_allowed_character
                               << "\n"
                                  "maximum_allowed_character=" 
                               << game_options.maximum_allowed_character 
                               << "\n";
            return true;
        }

        bool load_game_options(std::istream& input_file_stream, GameOptions& game_options)
        {
            string ligne;
            if (input_file_stream)
            {

                while (std::getline(input_file_stream, ligne))
                {
                    size_t equal_pos=ligne.find("=");
                    string before_equal = ligne.substr(0, equal_pos);
                    string after_equal = ligne.substr(equal_pos+1);

                    if (before_equal == "max_number_of_attempts")
                    {
                        game_options.max_number_of_attempts = std::atoi(after_equal.c_str());
                    }
                    
                    else if (before_equal == "number_of_characters_per_code")
                    {
                        game_options.number_of_characters_per_code = std::atoi(after_equal.c_str());
                    }

                    else if (before_equal == "minimum_allowed_character")
                    {
                        game_options.minimum_allowed_character = after_equal[0];
                    }

                    else if (before_equal == "maximum_allowed_character")
                    {
                        game_options.maximum_allowed_character = after_equal[0];
                    }
                }
                return true;
            }

            else
            {
                return false;
            }
        }
    
    // TODO: define the body of the functions declared in game_options.cpp

} // namespace bulls_and_cows
