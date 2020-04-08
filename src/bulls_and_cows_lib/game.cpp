
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
#include <windows.h>
#include "random.hpp"
#include <vector>

namespace bulls_and_cows {

    void user_plays_against_computer(const GameOptions& game_options)
    {
       
        //CREATING BOARD using functions we implemented
        Board myboard = bulls_and_cows::create_board(game_options);

        //While the user didn't win or reached max attempt number, while loop 

        while (!bulls_and_cows::is_end_of_game(game_options, myboard) && !bulls_and_cows::is_win(game_options, myboard))
        {
            // First display of the empty board
            bulls_and_cows::display_board(std::cout, game_options, myboard);

            // Asking attemp to the user
            Code tempattemp = bulls_and_cows::ask_attempt(std::cout, std::cin, game_options, myboard);

            if (bulls_and_cows::validate_attempt(game_options, tempattemp))
            {
                AttemptAndFeedback newattemp;
                newattemp.attempt= tempattemp;

                newattemp.feedback = bulls_and_cows::compare_attempt_with_secret_code(tempattemp, myboard.secret_code);

                myboard.attempts_and_feedbacks.push_back(newattemp);
            }
        }

    }

    void computer_plays_against_computer(const GameOptions& game_options)
    {
        //bulls_and_cows::generate_all_possible_codes(game_options);


        PossibleSolutions myavc = bulls_and_cows::generate_all_possible_codes(game_options);
        std::cout << "Solution generated with " << myavc.codes.size() << " solutions\n";
        Board myavcboard = bulls_and_cows::create_board(game_options);

        while (!bulls_and_cows::is_end_of_game(game_options, myavcboard) && !bulls_and_cows::is_win(game_options, myavcboard))
        {
            // First display of the empty board
            bulls_and_cows::display_board(std::cout, game_options, myavcboard);
            std::cout << "Solutions still are " << myavc.codes.size() << " solutions\n";

            // Asking attemp the computer to choose a random possibilitie
            Code avctemp = bulls_and_cows::pick_random_attempt(myavc);
            std::cout << "Choosen code is " << avctemp.value << "\n";

            AttemptAndFeedback newattemp;
            newattemp.attempt = avctemp;
            newattemp.feedback = bulls_and_cows::compare_attempt_with_secret_code(avctemp, myavcboard.secret_code);
            //std::cout << "Bulls : " << newattemp.feedback.bulls << " Cows : " << newattemp.feedback.cows<<"\n";
            myavcboard.attempts_and_feedbacks.push_back(newattemp);
            std::cout << "Secret code is : " << myavcboard.secret_code.value << "\n";
            if (bulls_and_cows::is_win(game_options, myavcboard))break;
            bulls_and_cows::remove_incompatible_codes_from_possible_solutions(newattemp, myavc);
            Sleep(2000);
        }
    }

    void configure_game_options(GameOptions & game_options)
    {
        std::ifstream in{"game_options.txt"};

        bool get_out = false;
        while (!get_out)
        {
            display_game_options(std::cout, game_options);
            display_game_options_menu(std::cout);
            std::cin.clear();
            const auto user_choice = ask_game_options_menu_choice(std::cin);

                switch (user_choice)
                {
                case GameOptionsMenuChoice::BackToMain:
                    get_out = true;
                    break;
                case GameOptionsMenuChoice::ModifyMaximumAllowedCharacter:
                    std::cout << "Enter the maximum character you want:";
                    game_options.maximum_allowed_character =
                        ask_char_or_default(std::cin, game_options.maximum_allowed_character);
                    break;
                case GameOptionsMenuChoice::ModifyMaximumNumberOfAttempts:
                    std::cout << "Enter the number of attempts you want:";
                    game_options.max_number_of_attempts =
                        ask_uint_or_default(std::cin, game_options.max_number_of_attempts);
                    break;
                case GameOptionsMenuChoice::ModifyMinimumAllowedCharacter:
                    std::cout << "Enter the minimum character you want:";
                    game_options.minimum_allowed_character =
                        ask_char_or_default(std::cin, game_options.minimum_allowed_character);
                    break;
                case GameOptionsMenuChoice::ModifyNumberOfCharactersPerCode:
                    std::cout << "Enter the number of character per code:";
                    game_options.number_of_characters_per_code =
                        ask_uint_or_default(std::cin, game_options.number_of_characters_per_code);
                    break;
                case GameOptionsMenuChoice::LoadOptions:
                    load_game_options(in, game_options);
                    break;
                case GameOptionsMenuChoice::SaveOptions:
                    std::ofstream out{"game_options.txt"};
                    save_game_options(out, game_options);
                    break;
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
