
#include "game_options.hpp"
#include "game_solver.hpp"
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
					  << "7 - Play without duplicates\n"
                      << "What is your choice ? ";
    }

    GameOptionsMenuChoice ask_game_options_menu_choice(std::istream& input_stream)
    {
		const auto user_settings = ask_int_or_default(input_stream, -1);
        switch (user_settings)
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
		case 7:
			return GameOptionsMenuChoice::Noduplicates;
		default:
			return GameOptionsMenuChoice::BackToMain;
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
		//INT
		str.erase(remove(str.begin(), str.end(), ' '), str.end());
		if (b == true) {
			for (int i = 0; i < str.size(); i++) {
				if (!isdigit(str[i]-'0')) {
					str.erase(i, 1);
					i--;
				}
			}
			str.erase(2);
		}
		//CHAR
		if (b == false) {
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

			if (token == "max_number_of_attempts") {
				//numb = remove_spaces_or_alphanum(numb, true);
				if (std::atoi(numb.c_str()) < 5 || std::atoi(numb.c_str()) > 20) {
					std::cout << "\nFile isn't in a correct form\n";
					return false;
				}
				game_options.max_number_of_attempts = std::atoi(numb.c_str());
			}
			else if (token == "number_of_characters_per_code") {
				//numb = remove_spaces_or_alphanum(numb, true);
				if (std::atoi(numb.c_str()) < 3 || std::atoi(numb.c_str()) > 10) {
					std::cout << "\nFile isn't in a correct form\n";
					return false;
				}
				game_options.number_of_characters_per_code = std::atoi(numb.c_str());
			}
			else if (token == "minimum_allowed_character") {
				//numb = remove_spaces_or_alphanum(numb, false);
				game_options.minimum_allowed_character = numb[0];
			}
			else if (token == "maximum_allowed_character") {
				//numb = remove_spaces_or_alphanum(numb, false);
				game_options.maximum_allowed_character = numb[0];
			}
			else{
				std::cout << "\nFile isn't in a correct form.\n";
				return false;
			}
        }
        return true;
    }

	void DuplicateChoice(GameOptions& game_options) {
		game_options.isDuplicate = false;
	}

} // namespace bulls_and_cows
