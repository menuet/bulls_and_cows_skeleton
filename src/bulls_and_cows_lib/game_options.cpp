
#include "game_options.hpp"

namespace bulls_and_cows {

    void display_game_options(const GameOptions& game_options)
    {
        std::cout << "\nThe number of characters in the code is " << game_options.number_of_characters_per_code
             << "\nThe maximum number of attempts allowed is " << game_options.max_number_of_attempts
             << "\nThere are characters between " << game_options.minimum_allowed_character << " and "
             << game_options.maximum_allowed_character << "\n";
    }

    void display_game_options_menu()
    {
        std::cout << "0> Back to menu\n"
                "1> Modifiy the maximum number of attempts\n"
                "2> Modify the number of characters per code\n"
                "3> Modify the minimum allowed character\n"
                "4> Modify the maximum allowed character\n"
                "5> Save the options\n"
                "6> Load the options\n";
    }

    GameOptionsMenuChoice ask_game_options_menu_choice()
    {
        int choice = 0;
        do
        {
            std::cout << "Enter your choice ";
            std::cin >> choice;
        } while (choice > 6 || choice < 0);
        return GameOptionsMenuChoice(choice);
    }

    void manage_game_options(GameOptionsMenuChoice choice, GameOptions& game_options)
    {
        char input_char;
        unsigned int input_int;
        switch (choice)
        {
        case GameOptionsMenuChoice::BackToMain:
            std::cout << "\nBye bye!\n";
            return;
        case GameOptionsMenuChoice::LoadOptions:
            break;

        case GameOptionsMenuChoice::ModifyMinimumAllowedCharacter:
            std::cout << "\nEnter the new value of the minimum allowed character (between A and "
                      << game_options.maximum_allowed_character << ") ";
            do
            {
                std::cin >> input_char;
            } while (input_char < 'A' || input_char > game_options.maximum_allowed_character);
            game_options.minimum_allowed_character = input_char;
            break;

        case GameOptionsMenuChoice::ModifyMaximumAllowedCharacter:
            std::cout << "\nEnter the new value of the maximum allowed character (between "
                      << game_options.minimum_allowed_character << " and Z) ";
            do
            {
                std::cin >> input_char;
            } while (input_char < game_options.minimum_allowed_character || input_char > 'Z');
            game_options.maximum_allowed_character = input_char;
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
            break;

        case GameOptionsMenuChoice::SaveOptions:
            break;

        default:
            break;
        }
    }

} // namespace bulls_and_cows
