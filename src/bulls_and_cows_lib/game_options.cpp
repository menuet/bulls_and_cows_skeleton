
#include "game_options.hpp"
#include "input.hpp"

namespace bulls_and_cows {

    // TODO: define the body of the functions declared in game_options.cpp

    void display_game_options(std::ostream& output_stream, const GameOptions& game_options)
    {
        output_stream << "\n#########################\n";
        output_stream << "Here are the current game_options:\n";
        output_stream << "Maximum number of the attempts per game: " << game_options.max_number_of_attempts << "\n";
        output_stream << "Number of characters in a code: " << game_options.number_of_characters_per_code << "\n";
        output_stream << "Range of allowed characters: from '" << game_options.minimum_allowed_character << "' to '"
                      << game_options.maximum_allowed_character << "'\n";
        output_stream << "#########################\n";
    }

    void display_game_options_menu(std::ostream& output_stream)
    {
        output_stream << "\nConfigure Options\n";
        output_stream << "0 - Back to main menu\n";
        output_stream << "1 - Modify Maximum number of attempts per game\n";
        output_stream << "2 - Modify Number of characters in a code\n";
        output_stream << "3 - Modify Minimum allowed character\n";
        output_stream << "4 - Modify Maximum allowed character\n";
        output_stream << "5 - Save options\n";
        output_stream << "6 - Load options\n";
        output_stream << "What is your choice? ";
    }

    GameOptionsMenuChoice ask_game_options_menu_choice(std::istream& input_stream)
    {
        auto choice = ask_int_or_default(input_stream, -1);

        switch (choice)
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
        output_file_stream << "max_number_of_attempts=" << game_options.max_number_of_attempts << "\n";
        output_file_stream << "number_of_characters_per_code=" << game_options.number_of_characters_per_code << "\n";
        output_file_stream << "minimum_allowed_character=" << game_options.minimum_allowed_character << "\n";
        output_file_stream << "maximum_allowed_character=" << game_options.maximum_allowed_character << "\n";

        return true;
    }

    bool load_game_options(std::istream& input_file_stream, GameOptions& game_options)
    {
        std::string line;

        while (std::getline(input_file_stream, line))
        {
            std::size_t ChercherCaracter = line.find("=");
            std::string ChercherInfo = line.substr(0, ChercherCaracter);
            std::string ChercherValeur = line.substr(ChercherCaracter + 1);

            if (ChercherInfo == "max_number_of_attempts")
                game_options.max_number_of_attempts = std::atoi(ChercherValeur.c_str());

            else if (ChercherInfo == "number_of_characters_per_code")
                game_options.number_of_characters_per_code = std::atoi(ChercherValeur.c_str());

            else if (ChercherInfo == "minimum_allowed_character")
                game_options.minimum_allowed_character = ChercherValeur[0];

            else if (ChercherInfo == "maximum_allowed_character")
                game_options.maximum_allowed_character = ChercherValeur[0];
        }
        return true;
    }
} // namespace bulls_and_cows
