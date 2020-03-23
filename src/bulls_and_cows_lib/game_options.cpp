
#include "game_options.hpp"
#include "input.hpp"
#include <sstream>


namespace bulls_and_cows {

    // TODO: define the body of the functions declared in game_options.cpp
    void display_game_options(std::ostream& output_stream, const GameOptions& game_options)
    {
        //This function is used to display the saved options for the game

    }

    void display_game_options(std::ostream& output_stream, const GameOptions& game_options)
    {
        output_stream << "Here are the current game_options:\n"
                      << "Maximum number of attempts per game: " << game_options.max_number_of_attempts << "\n"
                      << "Number of characters in a code: " << game_options.number_of_characters_per_code << "\n"
                      << "Range of allowed characters: from '" << game_options.minimum_allowed_character << "' to '"
                      << game_options.maximum_allowed_character << "'\n";
    }

    void display_game_options_menu(std::ostream& output_stream)
    {
        output_stream << "Configure Options\n"
                      << "0 - Back to main menu\n"
                      << "1 - Modify Maximum number of attempts per game\n"
                      << "2 - Modify Number of characters in a code\n"
                      << "3 - Modify Minimum allowed character\n"
                      << "4 - Modify Maximum allowed character\n"
                      << "5 - Save options\n"
                      << "6 - Load options\n"
                      << "What is your choice ? ";
    }

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

    bool save_game_options(std::ostream& output_file_stream, const GameOptions& game_options)
    {
        output_file_stream << "max_number_of_attempts=" << game_options.max_number_of_attempts << "\n"
                           << "number_of_characters_per_code=" << game_options.number_of_characters_per_code << "\n"
                           << "minimum_allowed_character=" << game_options.minimum_allowed_character << "\n"
                           << "maximum_allowed_character=" << game_options.maximum_allowed_character << "\n";
        return true;
    }


    bool load_game_options(std::istream& input_file_stream, GameOptions& game_options)
    {

         std::string line;
        while (std::getline(input_file_stream, line))
        {
            std::string delimiter = "=";
            std::string token = line.substr(0, line.find(delimiter));
            std::string numb = line.substr(1, line.find(delimiter));

            if (token == "max_number_of_attempts")
                game_options.max_number_of_attempts = std::atoi(numb.c_str());

            else if (token == "number_of_characters_per_code")
                game_options.number_of_characters_per_code = std::atoi(numb.c_str());

            else if (token == "minimum_allowed_character")
                game_options.minimum_allowed_character = 
            /*switch (token)
            {
                case "max_number_of_attempts":
                    game_options.max_number_of_attempts = std::atoi(numb.c_str());
                    break;

                case "number_of_characters_per_code":
                    game_options.number_of_characters_per_code = std::atoi(numb.c_str());
                    break;

                case "minimum_allowed_character":

                    break;
                default:
                    break;
            }*/
        }
        return true;
    }
} // namespace bulls_and_cows
