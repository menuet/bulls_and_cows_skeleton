
#include "game_options.hpp"
#include <fstream>
#include <sstream>
#include <vector>

namespace bulls_and_cows {

    void display_game_options(std::ostream& output_stream, const GameOptions& game_options)
    {
        output_stream << "\nThe number of characters in the code is " << game_options.number_of_characters_per_code
             << "\nThe maximum number of attempts allowed is " << game_options.max_number_of_attempts
             << "\nThere are characters between " << game_options.minimum_allowed_character << " and "
             << game_options.maximum_allowed_character << "\n";
        if (game_options.allow_duplicate)
        {
            output_stream << "Duplicates are allowed\n";
        }
        else
        {
            output_stream << "Duplicates are not allowed\n";
        }
    }

    void display_game_options_menu(std::ostream& output_stream)
    {
        output_stream << "Configure Options\n"
                "0> Back to menu\n"
                "1> Modifiy the maximum number of attempts\n"
                "2> Modify the number of characters per code\n"
                "3> Modify the minimum allowed character\n"
                "4> Modify the maximum allowed character\n"
                "5> Save the options\n"
                "6> Load the options\n"
                "7> Allow duplicates in the code\n"
                "Enter your choice\n";
    }

    GameOptionsMenuChoice ask_game_options_menu_choice(std::istream& input_stream)
    {
        int choice = 0;
        do
        {
            input_stream >> choice;
        } while (choice > 7 || choice < 0);
        return GameOptionsMenuChoice(choice);
    }

    //Function to save the options in a txt file, the return is 0 if the save has failed
    bool save_game_options(const GameOptions& game_options)
    {
        std::string const fileName(
            "C:/Users/AB/Documents/algo M1/Semester 8/C++/PROJECTS/bulls_and_cows_skeleton/game_options.txt");

        std::ofstream stream(fileName.c_str());

        if (stream)
        {
            stream << "max_number_of_attempts=" << game_options.max_number_of_attempts << std::endl;
            stream << "number_of_characters_per_code=" << game_options.number_of_characters_per_code << std::endl;
            stream << "minimum_allowed_character=" << game_options.minimum_allowed_character << std::endl;
            stream << "maximum_allowed_character=" << game_options.maximum_allowed_character << std::endl;
            stream << "duplicates_allowed=" << game_options.allow_duplicate << std::endl;
        }
        else
        {
            return false;
        }
        return true;
    }

    // Function to load the options from a txt file, the return is 0 if the load has failed
    bool load_game_options(GameOptions& game_options)
    {
        std::string const fileName(
            "C:/Users/AB/Documents/algo M1/Semester 8/C++/PROJECTS/bulls_and_cows_skeleton/game_options.txt");

        std::ifstream file(fileName.c_str());

        if (file)
        {
            // Variable to store the current line of the file
            std::string line;

            // While loop until we reach the end of the file
            while (getline(file, line))
            {
                //We need to split the different string to know the name and their value
                
                //This variable will tell if we are iterating in the name or in the value of the content of the line
                unsigned int name_or_value = 0;

                std::string option_name = "";
                std::string option_value = "";
                for (char c : line)
                {
                    if (name_or_value == 0)
                    {
                        option_name.push_back(c);
                    }
                    else
                    {
                        option_value.push_back(c);
                    }

                    //We split after the '='
                    if (c == '=')
                    {
                        name_or_value = 1;
                    }
                }

                //Attribution of the new options
                if (option_name == "max_number_of_attempts=")
                {
                    game_options.max_number_of_attempts = std::stoi(option_value);
                }
                else if (option_name == "number_of_characters_per_code=")
                {
                    game_options.number_of_characters_per_code = std::stoi(option_value);
                }
                else if (option_name == "minimum_allowed_character=")
                {
                    game_options.minimum_allowed_character = option_value[0];
                }
                else if (option_name == "maximum_allowed_character=")
                {
                    game_options.maximum_allowed_character = option_value[0];
                }
                else if (option_name == "duplicates_allowed=")
                {
                    game_options.allow_duplicate = std::stoi(option_value);
                }
            }
        }
        else
        {
            return false;
        }
        return true;
    }

    //Function adjusting the option number of character in the code when there are not enough characters allowed and no duplicates allowed
    //Return true if the length has been adjusted
    bool adjust_char_number(GameOptions& game_options)
    {
        if (game_options.allow_duplicate == 0)
        {
            unsigned int number_possible_char =
                game_options.maximum_allowed_character - game_options.minimum_allowed_character + 1;
            if (game_options.number_of_characters_per_code > number_possible_char)
            {
                game_options.number_of_characters_per_code = number_possible_char;
                return true;
            }
        }
        return false;
    }

    void manage_game_options(GameOptionsMenuChoice choice, GameOptions& game_options)
    {
        char input_char = ' ';
        unsigned int input_int = 0;
        bool input_bool = false;
        switch (choice)
        {
        case GameOptionsMenuChoice::BackToMain:
            std::cout << "\nBye bye!\n";
            return;
        case GameOptionsMenuChoice::LoadOptions:
            if (load_game_options(game_options))
            {
                std::cout << "\nGame options loaded!\n";
            }
            else
            {
                std::cout << "\nFail in loading game options";
            }
            break;

        case GameOptionsMenuChoice::ModifyMinimumAllowedCharacter:
            std::cout << "\nEnter the new value of the minimum allowed character (between A and "
                      << game_options.maximum_allowed_character << ") ";
            do
            {
                std::cin >> input_char;
            } while (input_char < 'A' || input_char > game_options.maximum_allowed_character);
            game_options.minimum_allowed_character = input_char;
            if (adjust_char_number(game_options))
            {
                std::cout << "\nThe number of characters per code has been adjusted according to the number characters "
                             "allowed.\n";
            }
            break;

        case GameOptionsMenuChoice::ModifyMaximumAllowedCharacter:
            std::cout << "\nEnter the new value of the maximum allowed character (between "
                      << game_options.minimum_allowed_character << " and Z) ";
            do
            {
                std::cin >> input_char;
            } while (input_char < game_options.minimum_allowed_character || input_char > 'Z');
            game_options.maximum_allowed_character = input_char;
            if(adjust_char_number(game_options))
            {
                std::cout << "\nThe number of characters per code has been adjusted according to the number characters allowed.\n";
            }
            break;

        case GameOptionsMenuChoice::ModifyMaximumNumberOfAttempts:
            std::cout << "\nEnter the new value of the maximum number of attempts ";
            do
            {
                std::cin >> input_int;
            } while (input_int < 1);
            game_options.max_number_of_attempts = input_int;
            break;

        case GameOptionsMenuChoice::ModifyNumberOfCharactersPerCode:
            std::cout << "\nEnter the new value of the number of characters per code ";
            do
            {
                std::cin >> input_int;
            } while (input_int < 1);
            game_options.number_of_characters_per_code = input_int;
            if (adjust_char_number(game_options))
            {
                std::cout << "\nThe number of characters per code has been adjusted according to the number characters "
                             "allowed.\n";
            }
            break;

        case GameOptionsMenuChoice::SaveOptions:
            if (save_game_options(game_options))
            {
                std::cout << "\nOptions saved!\n";
            }
            else
            {
                std::cout << "\nFail in saving options.\n";
            }
            break;

        case GameOptionsMenuChoice::AllowDuplicate:
            std::cout << "\nDo you want to allow duplicates (1 for Yes, 0 for No) ";
            do
            {
                std::cin >> input_bool;
            } while (input_int != 1 && input_int != 0);
            game_options.allow_duplicate = input_bool;
            if (adjust_char_number(game_options))
            {
                std::cout << "\nThe number of characters per code has been adjusted according to the number characters "
                             "allowed.\n";
            }
            break;

        default:
            std::cout << "Error\n";
            break;
        }
    }

} // namespace bulls_and_cows
