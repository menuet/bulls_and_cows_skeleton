
#include "game.hpp"
#include "board.hpp"
#include "game_options.hpp"
#include "game_solver.hpp"
#include "input.hpp"
#include "main_menu.hpp"
#include <chrono>
#include <fstream>
#include <iostream>
#include <thread>

namespace bulls_and_cows {

    void user_plays_against_computer(const GameOptions& game_options)
    {
        std::cout << "TODO:\n"
                     "    Create a board with a randomly generated secret code\n"
                     "    DO\n"
                     "       Display the board and the list of attempts so far\n"
                     "       Ask the user to make another attempt\n"
                     "       Compare the user's attempt with the secret code and deduce the number of bulls and cows\n"
                     "       Add the user's attempt to the list of attempts of the board\n"
                     "    WHILE not end of game\n"
                     "    Display the board and the list of attempts so far\n"
                     "    Display a message telling if the user won or lost\n";
    }

    void computer_plays_against_computer(const GameOptions& game_options)
    {
        std::cout
            << "TODO:\n"
               "    Create a board with a randomly generated secret code\n"
               "    Generate the list of all the possible codes\n"
               "    DO\n"
               "       Display the board and the list of attempts so far\n"
               "       Display the number of remaining possible codes so far\n"
               "       Wait for 2 seconds\n"
               "       Pick a random attempt among in the list of remaining possible codes\n"
               "       Compare the computer's attempt with the secret code and deduce the number of bulls and cows\n"
               "       Add the computer's attempt to the list of attempts of the board\n"
               "       Remove all the codes that are incompatible with the attempt's feedback from the list of "
               "possible codes\n"
               "    WHILE not end of game\n"
               "    Display the board and the list of attempts so far\n"
               "    Display a message telling if the computer won or lost\n";
    }

    void configure_game_options(GameOptions& game_options)
    {
        /*std::cout << "TODO:\n"
                     "    DO\n"
                     "       Display the current game options\n"
                     "       Display the game options menu\n"
                     "       Ask the user to type its choice\n"
                     "       Treat the user's choice\n"
                     "    UNTIL user's choice is to go back to main menu\n";*/

        std::cout << "\n#################################\n";

        display_game_options(std::cout, game_options);
        display_game_options_menu(std::cout);
        const auto user_choice = ask_game_options_menu_choice(std::cin);
        switch (user_choice)
        {
        case GameOptionsMenuChoice::BackToMain:
            play_game();
        case GameOptionsMenuChoice::ModifyMaximumNumberOfAttempts: {
            std::cout << "Enter the maximum number of attempts : ";
            int newVal = ask_int_or_default(std::cin, -1);
            if (newVal != -1)
            {
                game_options.max_number_of_attempts = newVal;
                configure_game_options(game_options);
            }
            break;
        }
        case GameOptionsMenuChoice::ModifyNumberOfCharactersPerCode: {
            std::cout << "Enter the number of caracter per code : ";
            int newVal1 = ask_int_or_default(std::cin, -1);
            if (newVal1 != -1)
            {
                game_options.number_of_characters_per_code = newVal1;
                configure_game_options(game_options);
            }
            break;
        }
        case GameOptionsMenuChoice::ModifyMinimumAllowedCharacter: {
            std::cout << "Enter the minimum allowed caracter : ";
            char newVal2 = ask_char_or_default(std::cin, 'x');
            if (!isdigit(newVal2) && newVal2 != 'x')
            {
                game_options.minimum_allowed_character = newVal2;
                configure_game_options(game_options);
            }
            else
            {
                configure_game_options(game_options);
            }
            break;
        }
        case GameOptionsMenuChoice::ModifyMaximumAllowedCharacter: {
            std::cout << "Enter the maximum allowed caracter : ";
            char newVal3 = ask_char_or_default(std::cin, 'x');
            if (!isdigit(newVal3) && newVal3 != 'x')
            {
                game_options.maximum_allowed_character = newVal3;
                configure_game_options(game_options);
            }
            else
            {
                configure_game_options(game_options);
            }
            break;
        }
        case GameOptionsMenuChoice::SaveOptions:
            configure_game_options(game_options);
            break;
        case GameOptionsMenuChoice::LoadOptions:
            configure_game_options(game_options);
            break;
        case GameOptionsMenuChoice::Error:
            std::cout << "\nYou did not enter a valid choice, please try again\n";
            break;
        }
    }

    void play_game()
    {
        GameOptions game_options{};
        std::cout << "\n#################################\n";
        display_main_menu(std::cout);

        while (true)
        {

            const auto user_choice = ask_main_menu_choice(std::cin);
            switch (user_choice)
            {
            case MainMenuChoice::Quit:
                std::cout << "\nBye bye!\n";
                return;
            case MainMenuChoice::UserPlaysAgainstComputer:
                user_plays_against_computer(game_options);
                break;
            case MainMenuChoice::ComputerPlaysAgainstComputer:
                computer_plays_against_computer(game_options);
                break;
            case MainMenuChoice::ConfigureOptions:
                configure_game_options(game_options);
                break;
            case MainMenuChoice::Error:
                std::cout << "\nYou did not enter a valid choice, please try again\n";
                break;
            }
        }
    }

} // namespace bulls_and_cows
