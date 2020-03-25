
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

        Board boardCreated = create_board(game_options);
        do
        {
            std::cout << "\n";
            display_board(std::cout, game_options, boardCreated);
            AttemptAndFeedback att_feed;
            att_feed.attempt = ask_attempt(std::cout, std::cin, game_options, boardCreated);
            att_feed.feedback = compare_attempt_with_secret_code(att_feed.attempt, boardCreated.secret_code);
            boardCreated.attempts_and_feedbacks.push_back(att_feed);

        } while (!is_end_of_game(game_options, boardCreated));
        display_board(std::cout, game_options, boardCreated);

        if (is_win(game_options, boardCreated))
        {
            std::cout << "\nYou won !! Computer lost\n";
        }
        else
        {
            std::cout << "\nSorry, you lost !! Computer won\n";
        }
    }

    void computer_plays_against_computer(const GameOptions& game_options)
    {
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
                "    Display a message telling if the computer won or lost\n";
                */

        Board boardCreated = create_board(game_options);
        PossibleSolutions possible_solutions = generate_all_possible_codes(game_options);

        do
        {
            std::cout << "\n";
            display_board(std::cout, game_options, boardCreated);
            std::cout << "\nNumber of remaining possibles codes : " << possible_solutions.codes.size() << "\n";
            // wait 2 seconds
            std::this_thread::sleep_for(std::chrono::seconds(2));
            AttemptAndFeedback attempt_and_feedback;
            attempt_and_feedback.attempt = pick_random_attempt(possible_solutions); // bien jusque là
            attempt_and_feedback.feedback =
                compare_attempt_with_secret_code(attempt_and_feedback.attempt, boardCreated.secret_code);
            boardCreated.attempts_and_feedbacks.push_back(attempt_and_feedback);
            std::cout << "\n";
            remove_incompatible_codes_from_possible_solutions(attempt_and_feedback, possible_solutions);

        } while (!is_end_of_game(game_options, boardCreated));

        std::cout << "\n";
        display_board(std::cout, game_options, boardCreated);

        if (is_win(game_options, boardCreated))
        {
            std::cout << "\nComputer IA won!\n";
        }
        else
        {
            std::cout << "\nComputer IA lost!\n";
        }
    }

    void configure_game_options(GameOptions& game_options)
    {
        /*std::cout << "TODO:\n"
                     "    DO\n"
                     "       Display the current game options\n"
                     "       Display the game options menu\n"
                     "       Ask the user to type its choice\n"
                     "       Treat the user's choice\n"
                     "    UNTIL user's choice is to go back to main menu\n  */

        while (true)
        {
            std::cout << "\n\n######################################\n";
            display_game_options(std::cout, game_options);
            std::cout << "######################################\n";
            display_game_options_menu(std::cout);
            const auto user_choice = ask_game_options_menu_choice(std::cin);
            switch (user_choice)
            {
            case GameOptionsMenuChoice::BackToMain:
                return;
            case GameOptionsMenuChoice::ModifyMaximumNumberOfAttempts: {
                option_ModifyMaximumNumberOfAttempts(game_options);
                break;
            }
            case GameOptionsMenuChoice::ModifyNumberOfCharactersPerCode: {
                option_ModifyNumberOfCharactersPerCode(game_options);
                break;
            }
            case GameOptionsMenuChoice::ModifyMinimumAllowedCharacter: {
                option_ModifyMinimumAllowedCharacter(game_options);
                break;
            }
            case GameOptionsMenuChoice::ModifyMaximumAllowedCharacter: {
                option_ModifyMaximumAllowedCharacter(game_options);
                break;
            }
            case GameOptionsMenuChoice::SaveOptions: {
                std::ofstream game_options_file{"game_options.txt", std::ios::app};
                option_SaveOptions(game_options_file,game_options);
                game_options_file.close();
                break;
            }
            case GameOptionsMenuChoice::LoadOptions: {
                std::ifstream file("game_options.txt");
                option_LoadOptions(file,game_options);
                break;
            }
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
            std::cout << "\n######################################\n";

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
