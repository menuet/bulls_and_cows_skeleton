#include "game.hpp"
#include "board.hpp"
#include "game_options.hpp"
#include "game_solver.hpp"
#include "input.hpp"
#include "main_menu.hpp"
#include <bulls_and_cows_lib\game_options.cpp>
#include <chrono>
#include <fstream>
#include <iostream>
#include <thread>

namespace bulls_and_cows {

    void user_plays_against_computer(const GameOptions& game_options)
    {
        Board board = create_board(game_options);
        AttemptAndFeedback newAttemptAndFeedback;
        do
        {
            display_board(std::cout, game_options, board);
            newAttemptAndFeedback.attempt = ask_attempt(std::cout, std::cin, game_options, board);
            while (!validate_attempt(game_options, newAttemptAndFeedback.attempt))
            {
                std::cout << "Your attempt is not valid, try again\n";
                newAttemptAndFeedback.attempt = ask_attempt(std::cout, std::cin, game_options, board);
            }

            newAttemptAndFeedback.feedback =
                compare_attempt_with_secret_code(newAttemptAndFeedback.attempt, board.secret_code);
            board.attempts_and_feedbacks.push_back(newAttemptAndFeedback);

        } while (!(is_end_of_game(game_options, board)) && !(is_win(game_options, board)));
        std::cout << "\n\n";
        display_board(std::cout, game_options, board);
        if (is_win(game_options, board))
        {
            std::cout << "Wow you just won  !! The secret code was : " << board.secret_code.value << std::endl;
        }
        else
        {
            std::cout << "Sorry but you lost. The secret combinaison was : " << board.secret_code.value << std::endl;
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
        bool exit = false;
        std::string path = "./save.txt";
        std::ofstream save;
        std::ifstream load(path);

        while (!exit)
        {
            std::cout << "\n";
            std::cout << "#################################"
                      << "\n";
            std::cout << "#################################"
                      << "\n";
            std::cout << "#################################"
                      << "\n";
            std::cout << "\n";

            display_game_options(std::cout, game_options);
            display_game_options_menu(std::cout);
            const auto choice = ask_game_options_menu_choice(std::cin);

            switch (choice)
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
                save_game_options(game_options_file, game_options);
                game_options_file.close();
                break;
            }
            case GameOptionsMenuChoice::LoadOptions: {
                std::ifstream file("game_options.txt");
                load_game_options(file, game_options);
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
            std::cout << "\n#################################\n";
            std::cout << "\n#################################\n";
            display_main_menu(std::cout);

            const auto choice = ask_main_menu_choice(std::cin);
            switch (choice)
            {
            case MainMenuChoice::Quit:
                std::cout << "\nGood bye!\n";
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