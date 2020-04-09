
#include "game_options.hpp"
#include "input.hpp"

namespace bulls_and_cows {

    // TODO: define the body of the functions declared in game_options.cpp


    //Checked
    void display_game_options(std::ostream& output_stream, const GameOptions& game_options)
    {
        output_stream << "\n#################################\nHere are the current game_options:\n"
                      << "Maximum number of attempts per game: " << game_options.max_number_of_attempts << "\n"
                      << "Number of characters in a code: " << game_options.number_of_characters_per_code << "\n"
                      << "Range of allowed characters: from '" << game_options.minimum_allowed_character << "' to '"
                      << game_options.maximum_allowed_character << "'\n"
                      << "Character unicity: " << ((game_options.unique_characters) ? "Enabled\n" : "Disabled\n");
    }

    //Checked
    void display_game_options_menu(std::ostream& output_stream)
    {
        output_stream << "#################################\n"
                      << "Configure Options\n"
                      << "0 - Back to main menu\n"
                      << "1 - Modify Maximum number of attempts per game\n"
                      << "2 - Modify Number of characters in a code\n"
                      << "3 - Modify Minimum allowed character\n"
                      << "4 - Modify Maximum allowed character\n"
                      << "5 - Save options\n"
                      << "6 - Load options\n"
                      << "7 - Modify character unicity\n";
    }
    //Checked
    GameOptionsMenuChoice ask_game_options_menu_choice(std::istream& input_stream)
    {
        switch (ask_int_or_default(input_stream, -1))
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
            case 7:
                return GameOptionsMenuChoice::UniqueCharacters;
            default:
                return GameOptionsMenuChoice::Error;
        }
    }

    //Checked
    bool save_game_options(std::ostream& output_file_stream, const GameOptions& game_options)
    {
        output_file_stream << "max_number_of_attempts=" << game_options.max_number_of_attempts << "\n"
                           << "number_of_characters_per_code=" << game_options.number_of_characters_per_code << "\n"
                           << "minimum_allowed_character=" << game_options.minimum_allowed_character << "\n"
                           << "maximum_allowed_character=" << game_options.maximum_allowed_character << "\n"
                           << "unique_characters=" << game_options.unique_characters << "\n";
        return true;
    }
    //Checked
    bool load_game_options(std::istream& input_file_stream, GameOptions& game_options)
    {
        std::string line;
        while (std::getline(input_file_stream, line)) // go through each line of the file
        {
            std::size_t delimiter = line.find("="); // will be the separation between name of parameter and new value
            std::string token = line.substr(0, delimiter);  //name
            std::string numb = line.substr(delimiter + 1);  //value
            if (numb != "") // If value not empty
            {
                if (token == "max_number_of_attempts")  // Try to find the parameter to be changed
                    game_options.max_number_of_attempts = std::atoi(numb.c_str());
                else if (token == "number_of_characters_per_code")
                    game_options.number_of_characters_per_code = std::atoi(numb.c_str());

                else if (token == "minimum_allowed_character")
                {
                    game_options.minimum_allowed_character = numb[0];
                }

                else if (token == "maximum_allowed_character")
                {
                    game_options.maximum_allowed_character = numb[0];
                }
                else if (token == "unique_characters")
                {
                    game_options.unique_characters = numb[0];
                }
                else    //someone wrote something, file is corrupted
                {
                    std::cout << "Error, file corrupted\n";
                    break;
                }
            }
            else        // Value is empty, someone wrote in the file
            {
                std::cout << "Error, file corrupted\n";
                break;
            }
        }
        return true;
    }


} // namespace bulls_and_cows
