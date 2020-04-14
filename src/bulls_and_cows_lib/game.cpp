#include "game.hpp"
#include "board.hpp"
#include "game_options.hpp"
#include "game_solver.hpp"
#include "input.hpp"
#include "main_menu.hpp"
#include <bulls_and_cows_lib\random.cpp>
#include <chrono>
#include <fstream>
#include <iostream>
#include <thread>

// test 4
namespace bulls_and_cows {
    // test
    void user_plays_against_computer(const GameOptions& game_options)
    {
        /*std::cout << "TODO:\n"
                     "    Create a board with a randomly generated secret code\n"
                     "    DO\n"
                     "       Display the board and the list of attempts so far\n"
                     "       Ask the user to make another attempt\n"
                     "       Compare the user's attempt with the secret code and deduce the number of bulls and cows\n"
                     "       Add the user's attempt to the list of attempts of the board\n"
                     "    WHILE not end of game\n"
                     "    Display the board and the list of attempts so far\n"
                     "    Display a message telling if the user won or lost\n";*/

        Board myboard{}; // create a board 
        AttemptAndFeedback my_feedback{};

        myboard = create_board(game_options); // store the board

        do // until the game is not done
        {
            std::cout << "\n";
            display_board(std::cout, game_options, myboard); // display attempts
            // std::count <<myboard.secret_code.value<<"\n";

            my_feedback.attempt = ask_attempt(std::cout, std::cin, game_options, myboard); // store ask attempt in a feedback

            while (!validate_attempt(game_options, my_feedback.attempt)) // while attempt is not valid 
            {
                std::cout << "Your attempt is not valid, try again\n";
                my_feedback.attempt = ask_attempt(std::cout, std::cin, game_options, myboard);
            }

            my_feedback.feedback = compare_attempt_with_secret_code(my_feedback.attempt, myboard.secret_code); // function comparing attempt with secret code and returns number of cows et de bulls
            myboard.attempts_and_feedbacks.push_back(my_feedback); // put full attempt (bulls and cows) in   attempts and feedback
        } while (!(is_end_of_game(game_options, myboard)) && !(is_win(game_options, myboard)));


        std::cout << "\n";
        display_board(std::cout, game_options, myboard);

        if (is_win(game_options, myboard))
        {
            std::cout << "\n"
                << "You won, secret code is " << myboard.secret_code.value << "\n";
        }

        else
        {
            std::cout << "\n"
                << "You lost, secret code is " << myboard.secret_code.value << "\n";
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
        // GameOptions game_options{};

        std::cout << "Type a number of attempts: "; // Type a number and press enter
        std::cin >> game_options.max_number_of_attempts; // Get user input from the keyboard

        std::cout << "Type a number of characters: ";
        std::cin >> game_options.number_of_characters_per_code;

        std::cout << "Type the minimum allowed character: ";
        std::cin >> game_options.minimum_allowed_character;

        std::cout << "Type the maximum allowed character ";
        std::cin >> game_options.maximum_allowed_character;

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