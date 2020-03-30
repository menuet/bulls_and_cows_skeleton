
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
        
        Board Board;
        std::cout << "    \n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n"
                     "    Prepare yourself for a game against yourself or the computer\n"
                     "    Create a randomly generated secret code\n"
                     "    >Press 1 ...\n"
                     "    If you want to play against a code that you enter yourself\n"
                     "    >Press 2 ...\n"
                     "What is your choice ? \n -> ";
                    
        auto user_choice = ask_main_random_or_typed(std::cin);
        bool stop= false;
        while (stop == false)
        {
            switch (user_choice)
            {
            case MainMenuChoice1::Quit:
                std::cout << "\nBye bye!\n";
                stop = true;
                return;
            case MainMenuChoice1::RandomGenerator:
                Board.secret_code.value = create_secret_randomly(game_options, std::cin);
                stop = true;
                break;
            case MainMenuChoice1::UserGenerated:
                Board.secret_code.value = create_secret(game_options, std::cin);
                stop = true;
                break;
            case MainMenuChoice1::Error:
                std::cout << "\nYou did not enter a valid choice, please try again\n"
                             "What is your choice ? \n -> ";
                user_choice = ask_main_random_or_typed(std::cin);
                break;
            }
        }

        //display_board(game_options, Board);
        std ::cout << "Code secret utilise " << Board.secret_code.value << "\n";
        display_board(game_options, Board);
        bool end = false;
        bool win = false;
        Code Code;
        Feedback feedback;
        AttemptAndFeedback test;
        while (!end && !win)
        {
            Code.value = create_attempt(game_options, std::cin);
            test.attempt = Code;
            test.feedback = compare_attempt_with_secret_code(Code , Board.secret_code);
            Board.attempts_and_feedbacks.push_back(test);
            display_board(game_options, Board);
            win = is_win(game_options, Board);
            end = is_end_of_game(game_options, Board);
        }
        if (win)
        {
            std::cout << "\n '*'*'*'*' Congratulations '*'*'*'*' \n  "
                         "      You found the code with only "
                      << Board.attempts_and_feedbacks.size() 
                      << " attempts\n";
        }
        if (end && !win)
        {
            std::cout << "\n '*'*'*'*' You lost '*'*'*'*' \n  "
                         " Even with "
                      << game_options.max_number_of_attempts << " attempts you can't find this god damn code\n";
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
        std::cout << "TODO:\n"
                     "    DO\n"
                     "       Display the current game options\n"
                     "       Display the game options menu\n"
                     "       Ask the user to type its choice\n"
                     "       Treat the user's choice\n"
                     "    UNTIL user's choice is to go back to main menu\n";
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
