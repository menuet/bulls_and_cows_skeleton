
#include "game.hpp"
#include "board.hpp"
#include "game_options.hpp"
#include "game_solver.hpp"
#include "input.hpp"
#include "main_menu.hpp"
#include "random.hpp"
#include <chrono>
#include <fstream>
#include <iostream>
#include <thread>
#include <vector>
#include <list>
namespace bulls_and_cows {

    void user_plays_against_computer(const GameOptions& game_options)
    {

        // CREATING BOARD using functions we implemented
        Board myboard = bulls_and_cows::create_board(game_options);

        // While the user didn't win or reach max attempt number, while loop

        while (!bulls_and_cows::is_end_of_game(game_options, myboard) && !bulls_and_cows::is_win(game_options, myboard))
        {
            // First display of the empty board
            bulls_and_cows::display_board(std::cout, game_options, myboard);

            // Asking attemp to the user
            Code tempattemp = bulls_and_cows::ask_attempt(std::cout, std::cin, game_options, myboard);
            if (bulls_and_cows::validate_attempt(game_options, tempattemp))
            {
                AttemptAndFeedback newattemp;
                newattemp.attempt = tempattemp;
                newattemp.feedback = bulls_and_cows::compare_attempt_with_secret_code(tempattemp, myboard.secret_code);
                myboard.attempts_and_feedbacks.push_back(newattemp);
            }
                
        }

        std::cout << (is_win(game_options, myboard) ? "You won !! GG WP\n" : "");
        std::cout << (is_end_of_game(game_options, myboard) ? "You lost, please try again and not cry\n The code was" + myboard.secret_code.value : "");
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
        bool getout = false;
        while (!getout)
        {

            display_game_options(std::cout, game_options);
            display_game_options_menu(std::cout);
            std::cout << "What is your choice ? ";
            const auto user_choice = ask_game_options_menu_choice(std::cin);


            switch (user_choice)
            {
            case GameOptionsMenuChoice::BackToMain:
                getout = true;
                break;
            case GameOptionsMenuChoice::ModifyMaximumAllowedCharacter: {

                std::cout << "Enter the maximum character you want:";
                char newmax = ask_char_or_default(std::cin, game_options.maximum_allowed_character);
                unsigned int range = newmax - game_options.minimum_allowed_character;
                if (newmax < game_options.minimum_allowed_character)
                {
                    std::cout << "Maximum cannot be inferior to minimum\n";
                }
                if (range < game_options.number_of_characters_per_code)
                {
                    std::cout << "Character range is too short, please first reduce number of character per code";
                }
                else
                    game_options.maximum_allowed_character = newmax;
                break;
            }
            case GameOptionsMenuChoice::ModifyMaximumNumberOfAttempts: {

                std::cout << "Enter the number of attempts you want:";
                unsigned int newmax = ask_uint_or_default(std::cin, game_options.max_number_of_attempts);
                if (newmax <= 20)
                {
                    game_options.max_number_of_attempts = newmax;
                }
                else
                    std::cout << "Number of attempts cannot exceed 20 attempts\n";
                break;
            }
            case GameOptionsMenuChoice::ModifyMinimumAllowedCharacter: {
                std::cout << "Enter the minimum character you want:";
                char newmin = ask_char_or_default(std::cin, game_options.minimum_allowed_character);
                unsigned int range = game_options.maximum_allowed_character - newmin;
                if (newmin > game_options.maximum_allowed_character)
                {
                    std::cout << "Minimum cannot be superior to maximum\n";
                }
                if (range < game_options.number_of_characters_per_code)
                {
                    std::cout << "Character range is too short, please first reduce number of character per code";
                }
                else
                    game_options.minimum_allowed_character = newmin;
                break;
            }
            case GameOptionsMenuChoice::ModifyNumberOfCharactersPerCode: {

                std::cout << "Enter the number of characters per code:";
                unsigned int newmax = ask_uint_or_default(std::cin, game_options.number_of_characters_per_code);
                if (newmax <= 10)
                {
                    game_options.number_of_characters_per_code = newmax;
                }
                else
                    std::cout << "Number of characters per code cannot exceed 10\n";
                break;
            }
            case GameOptionsMenuChoice::LoadOptions: {
                std::ifstream in{"game_options.txt"};
                load_game_options(in, game_options);
                break;
            }
            case GameOptionsMenuChoice::SaveOptions: {
                std::ofstream out{"game_options.txt"};
                save_game_options(out, game_options);
                break;
            }
            case GameOptionsMenuChoice::UniqueCharacters: {
                std::cout << "Enter 0/1: ";
                std::string ans;
                std::cin >> ans;
                if (ans == "0")
                    game_options.unique_characters = false;
                else if (ans == "1")
                    game_options.unique_characters = true;
                else
                    std::cout << "Unknown input";
                break;
            }
            default:
                std::cout << "Unknown request, please enter a valid choice\n";
            
            }
        }
     }
    

    void play_game()
    {
        GameOptions game_options{};
        while (true)
        {
            std::cout << "\n#################################\n";
            display_main_menu(std::cout);
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
