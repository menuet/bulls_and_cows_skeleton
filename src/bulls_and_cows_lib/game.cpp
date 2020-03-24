
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
        Board myboard{};
        AttemptAndFeedback my_feedback{};

        myboard = create_board(game_options);

        do
        {
            std::cout << "\n";
            display_board(std::cout, game_options, myboard);
            //std::cout << myboard.secret_code.value << "\n";

            my_feedback.attempt = ask_attempt(std::cout, std::cin, game_options, myboard);

            while (!validate_attempt(game_options, my_feedback.attempt))
            {
                std::cout << "Your attempt is not valid, try again\n";
                my_feedback.attempt = ask_attempt(std::cout, std::cin, game_options, myboard);
            }

           my_feedback.feedback = compare_attempt_with_secret_code(my_feedback.attempt, myboard.secret_code);
           myboard.attempts_and_feedbacks.push_back(my_feedback);

        } while ( !(is_end_of_game(game_options,myboard)) && !(is_win(game_options,myboard)) );

        std::cout << "\n";
        display_board(std::cout, game_options, myboard);

        if (is_win(game_options, myboard))
        {
            std::cout << "\n" << "You won ! The secret code is : " << myboard.secret_code.value << "\n";
        }
        else
        {
            std::cout << "\n" << "You lost ! The secret code is : " << myboard.secret_code.value << "\n";
        }

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

            display_game_options(std::cout, game_options);
            display_game_options_menu(std::cout);
            const auto choice = ask_game_options_menu_choice(std::cin);
            bool back_to_main = false;

            switch (choice)
            {
            case GameOptionsMenuChoice::BackToMain:
                back_to_main = true;
                break;
            case GameOptionsMenuChoice::ModifyMaximumNumberOfAttempts:
                modify_maximum_number_of_attempts(game_options, std::cout, std::cin);
                break;
            case GameOptionsMenuChoice::ModifyNumberOfCharactersPerCode:
                modify_number_of_characters_per_code(game_options, std::cout, std::cin);
                break;
            case GameOptionsMenuChoice::ModifyMinimumAllowedCharacter:
                modify_minimum_allowed_characters(game_options, std::cout, std::cin);
                break;
            case GameOptionsMenuChoice::ModifyMaximumAllowedCharacter:
                 modify_maximum_allowed_characters(game_options, std::cout, std::cin);
                break;
            case GameOptionsMenuChoice::SaveOptions:
                //
                break;
            case GameOptionsMenuChoice::LoadOptions:
                //
                break;
            case GameOptionsMenuChoice::Error:
                std::cout << "\nYou did not enter a valid choice, please try again\n"; //problem
                break;
            }

        /*std::cout << "TODO:\n"
                     "    DO\n"
                     "       Display the current game options\n"
                     "       Display the game options menu\n"
                     "       Ask the user to type its choice\n"
                     "       Treat the user's choice\n"
                     "    UNTIL user's choice is to go back to main menu\n";*/
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
