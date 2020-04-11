
#include "game.hpp"
#include "board.hpp"
#include "game_options.hpp"
#include "game_solver.hpp"
#include "input.hpp"
#include "main_menu.hpp"
#include <chrono>
#include <windows.h>
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

            my_feedback.attempt = ask_attempt(std::cout, std::cin, game_options, myboard);

            while (!validate_attempt(game_options, my_feedback.attempt))
            {
                std::cout << "Your attempt is not valid, try again\n";
                my_feedback.attempt = ask_attempt(std::cout, std::cin, game_options, myboard);
            }

            my_feedback.feedback = compare_attempt_with_secret_code(my_feedback.attempt, myboard.secret_code);
            myboard.attempts_and_feedbacks.push_back(my_feedback);

        } while (!(is_end_of_game(game_options, myboard)) && !(is_win(game_options, myboard)));

        std::cout << "\n";
        display_board(std::cout, game_options, myboard);

        if (is_win(game_options, myboard))
        {
            std::cout << "\n"
                      << "You won ! The secret code is : " << myboard.secret_code.value << "\n";
        }
        else
        {
            std::cout << "\n"
                      << "You lost ! The secret code is : " << myboard.secret_code.value << "\n";
        }
    }

    void computer_plays_against_computer(const GameOptions& game_options)
    {
        Board IAboard = create_board(game_options); //Create a board with a randomly generated secret code
        PossibleSolutions all_codes = generate_all_possible_codes(game_options); //Generate the list of all the possible codes
        AttemptAndFeedback IA_af{};
        

        do
        {
            std::cout << "\n";
            display_board(std::cout, game_options, IAboard); // Display the board and the list of attempts so far

            std::cout << "\n" << all_codes.codes.size() << " Remaining possible codes :\n";
            for (auto temp : all_codes.codes)
            {
                std::cout <<temp.value <<" "; //Display remaining possible codes so far
            }

            std::cout << "\n";
            Sleep(2000); //Wait for 2 seconds

            IA_af.attempt = pick_random_attempt(all_codes);
            IA_af.feedback = compare_attempt_with_secret_code(IA_af.attempt, IAboard.secret_code);
            IAboard.attempts_and_feedbacks.push_back(IA_af);
            remove_incompatible_codes_from_possible_solutions(IA_af, all_codes, IAboard);

        } while (!(is_end_of_game(game_options, IAboard)) && !(is_win(game_options, IAboard)));



        /* std::cout
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
                "    Display a message telling if the computer won or lost\n";*/
    }

    void configure_game_options(GameOptions& game_options)
    {
        bool back_to_main = false;
        std::string path = "C:/DEVCPP/PROJECTS/bulls_and_cows_skeleton/game_options.txt";
        std::ofstream save;
        std::ifstream load(path);

        while (!back_to_main)
        {

            display_game_options(std::cout, game_options);
            display_game_options_menu(std::cout);
            const auto choice = ask_game_options_menu_choice(std::cin);

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
                save.open(path);
                save_game_options(save, game_options);
                save.close();
                break;
            case GameOptionsMenuChoice::LoadOptions:
                load_game_options(load, game_options);
                break;
            case GameOptionsMenuChoice::Error:
                std::cout << "\nYou did not enter a valid choice, please try again\n";
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
