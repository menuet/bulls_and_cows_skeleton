#include "game.hpp"
#include "board.hpp"
#include "game_options.hpp"
#include "game_solver.hpp"
#include "input.hpp"
#include "main_menu.hpp"
#include <bulls_and_cows_lib\random.cpp>
#include <iostream>
#include <thread>
#include <chrono>
#include <fstream>




namespace bulls_and_cows {

    void user_plays_against_computer(const GameOptions& game_options)
    {
        Board board{};
        AttemptAndFeedback feedback{};

        board = create_board(game_options);

        do
        {
            std::cout << "\n";
            display_board(std::cout, game_options, board);

            feedback.attempt = ask_attempt(std::cout, std::cin, game_options, board);

            while (!validate_attempt(game_options,feedback.attempt))
            {
                std::cout << "Your attempt is not valid, try again\n";
                feedback.attempt = ask_attempt(std::cout, std::cin, game_options, board);
            }

            feedback.feedback = compare_attempt_with_secret_code(feedback.attempt, board.hiddenCode);

            board.attempts_and_feedbacks.append(feedback);
        } while (!(is_end_of_game(game_options, board)) && !(is_win(game_options, board)));

        
        std::cout << "\n";
        display_board(std::cout, game_options, board);

        if (is_win(game_options, board))
        {
            std::cout << "\n"
                      << "You won !the hidden code was: " << board.hiddenCode.value << "\n";
        }

        else
        {
            std::cout << "\n"
                      << "You've lost, the hidden code was: " << board.hiddenCode.value << "\n";
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
