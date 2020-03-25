
#include "game_options.hpp"
#include "input.hpp"
#include <sstream>
#include <algorithm>


namespace bulls_and_cows {

    /* TODO: define the body of the functions declared in game_options.cpp
    void display_game_options(std::ostream& output_stream, const GameOptions& game_options)
    {
        //This function is used to display the saved options for the game

    }*/

    void display_game_options(std::ostream& output_stream, const GameOptions& game_options)
    {
		output_stream << "Here are the current game_options:\n" << "\n"
			<< "Maximum number of attempts per game: " << game_options.max_number_of_attempts << "\n"
			<< "Number of characters in a code: " << game_options.number_of_characters_per_code << "\n"
			<< "Range of allowed characters: from '" << game_options.minimum_allowed_character << "' to '"
			<< game_options.maximum_allowed_character << "'\n" << "\n";
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
		auto user_settings = ask_int_or_default(input_stream, -1);
        switch (user_settings)
        {
        case -1:
            return GameOptionsMenuChoice::Error;
            break;
        case 0:
            return GameOptionsMenuChoice::BackToMain;
            break;
        case 1:
            return GameOptionsMenuChoice::ModifyMaximumNumberOfAttempts;
            break;
        case 2:
            return GameOptionsMenuChoice::ModifyNumberOfCharactersPerCode;
            break;
        case 3:
            return GameOptionsMenuChoice::ModifyMinimumAllowedCharacter;
            break;
        case 4:
            return GameOptionsMenuChoice::ModifyMaximumAllowedCharacter;
            break;
        case 5:
            return GameOptionsMenuChoice::SaveOptions;
            break;
        case 6:
            return GameOptionsMenuChoice::LoadOptions;
            break;
		default:
			return GameOptionsMenuChoice::BackToMain;
			break;

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

	//Avoid bugs if wrong manual changes
	std::string remove_spaces_or_alphanum(std::string str, bool b)
	{
		str.erase(remove(str.begin(), str.end(), ' '), str.end());
		if (b == 0) {
			for (int i = 0; i < str.size(); i++) {
				if (!isdigit(str[i])) {
					str.erase(i, 1);
					i--;
				}
			}
		}
		if (b == 1) {
			for (int j = 0; j < str.size(); j++) {
				if (isdigit(str[j])) {
					str.erase(j, 1);
					j--;
				}
			}
			str.erase(1);
		}
		return str;
	}

    bool load_game_options(std::istream& input_file_stream, GameOptions& game_options)
    {

        std::string line; 
        while (std::getline(input_file_stream, line))
        {
			std::size_t delimiter = line.find("=");
			std::string token = line.substr(0, delimiter);
			std::string numb = line.substr(delimiter + 1);

			std::cout << numb;
			if (token == "max_number_of_attempts") {
				numb = remove_spaces_or_alphanum(numb, 0);
				game_options.max_number_of_attempts = std::atoi(numb.c_str());
			}
			else if (token == "number_of_characters_per_code") {
				numb = remove_spaces_or_alphanum(numb, 0);
				game_options.number_of_characters_per_code = std::atoi(numb.c_str());
			}
			else if (token == "minimum_allowed_character") {
				numb = remove_spaces_or_alphanum(numb, 1);
				game_options.minimum_allowed_character = numb[0];
			}
			else if (token == "maximum_allowed_character") {
				numb = remove_spaces_or_alphanum(numb, 1);
				game_options.maximum_allowed_character = numb[0];
			}
        }
        return true;
    }
} // namespace bulls_and_cows
