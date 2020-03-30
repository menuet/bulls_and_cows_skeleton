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

        Board myboard{}; // créer un board 
        AttemptAndFeedback my_feedback{};

        myboard = create_board(game_options); // stock le board créer

        do // on fait ca tant que ce n'est pas la fin de partie ou la personne gagne
        {
            std::cout << "\n";
            display_board(std::cout, game_options, myboard); // affiché les tentative
            // std::count <<myboard.secret_code.value<<"\n";

            my_feedback.attempt = ask_attempt(std::cout, std::cin, game_options, myboard); // stock ask attempt dans un feedback

            while (!validate_attempt(game_options, my_feedback.attempt)) // tant que l'attempt est pas valide 
            {
                std::cout << "Your attempt is not valid, try again\n";
                my_feedback.attempt = ask_attempt(std::cout, std::cin, game_options, myboard);
            }

            my_feedback.feedback = compare_attempt_with_secret_code(my_feedback.attempt, myboard.secret_code); // fonction qui comparer l'attempt avec le code secret et qui redonne le nombre de cows et de bulls
            myboard.attempts_and_feedbacks.push_back(my_feedback); // on insère la nouvelle tentative entière avec (bulls and cows) dans attempts and feedback
        } while (!(is_end_of_game(game_options, myboard)) && !(is_win(game_options, myboard)));


        std::cout << "\n";
        display_board(std::cout, game_options, myboard);

        if (is_win(game_options, myboard))
        {
            std::cout << "\n"
                << "Tu as gagne le code secret est " << myboard.secret_code.value << "\n";
        }

        else
        {
            std::cout << "\n"
                << "Tu as perdu le code secret est " << myboard.secret_code.value << "\n";
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