
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
                      << game_options.maximum_allowed_character << "'\n";

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
                      << "What is your choice ? ";
    }
    //Checked
    GameOptionsMenuChoice ask_game_options_menu_choice(std::istream& input_stream)
    {
        int userin{};
        GameOptionsMenuChoice yes{};
        userin = ask_int_or_default(input_stream, -1);
        switch (userin)
        {
            case -1:
                yes = GameOptionsMenuChoice::Error;
                break;
            case 0:
                yes = GameOptionsMenuChoice::BackToMain;
                break;
            case 1:
                yes = GameOptionsMenuChoice::ModifyMaximumNumberOfAttempts;
                break;
            case 2:
                yes = GameOptionsMenuChoice::ModifyNumberOfCharactersPerCode;
                break;
            case 3:
                yes = GameOptionsMenuChoice::ModifyMinimumAllowedCharacter;
                break;
            case 4:
                yes = GameOptionsMenuChoice::ModifyMaximumAllowedCharacter;
                break;
            case 5:
                yes = GameOptionsMenuChoice::SaveOptions;
                break;
            case 6:
                yes = GameOptionsMenuChoice::LoadOptions;
                break;
        }
        return yes;
    }

    //Checked
    bool save_game_options(std::ostream& output_file_stream, const GameOptions& game_options)
    {
        output_file_stream << "max_number_of_attempts=" << game_options.max_number_of_attempts << "\n"
                           << "number_of_characters_per_code=" << game_options.number_of_characters_per_code << "\n"
                           << "minimum_allowed_character=" << game_options.minimum_allowed_character << "\n"
                           << "maximum_allowed_character=" << game_options.maximum_allowed_character << "\n";
        return true;
    }
    //Checked
    bool load_game_options(std::istream& input_file_stream, GameOptions& game_options)
    {

        std::string line;
        while (std::getline(input_file_stream, line))
        {
            // std::string delimiter = "=";
            std::size_t delimiter = line.find("=");
            std::string token = line.substr(0, delimiter);
            std::string numb = line.substr(delimiter + 1);
            char* max_min_allowed_character = const_cast<char*>(numb.c_str());

            if (token == "max_number_of_attempts")
                game_options.max_number_of_attempts = std::atoi(numb.c_str());
            else if (token == "number_of_characters_per_code")
                game_options.number_of_characters_per_code = std::atoi(numb.c_str());

            else if (token == "minimum_allowed_character")
            {
                game_options.minimum_allowed_character = max_min_allowed_character[0];
            }

            else if (token == "maximum_allowed_character")
            {
                game_options.maximum_allowed_character = max_min_allowed_character[0];
            }
        }
        return true;
    }


} // namespace bulls_and_cows
