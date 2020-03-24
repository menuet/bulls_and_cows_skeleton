
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
using namespace std;
namespace bulls_and_cows {

    void user_plays_against_computer(const GameOptions& game_options)
    {
        std::cout << "TODO:\n"
                     "    Create a board with a randomly generated secret code\n"
                     "    DO\n"
                     "       Display the board and the list of attempts so far\n"
                     "       Ask the user to make another attempt\n"
                     "       Compare the user's attempt with the secret code and deduce the number of bulls and cows\n"
                     "       Add the user's attempt to the list of attempts of the board\n"
                     "    WHILE not end of game\n"
                     "    Display the board and the list of attempts so far\n"
                     "    Display a message telling if the user won or lost\n";
        cout << "create your secret code" << endl;
        int secode;
        cin >> secode;
        int A, B, C, D;
        A = secode / 1000;
        B = (secode - A * 1000) / 100;
        C = (secode - A * 1000 - B * 100) / 10;
        D = (secode - A * 1000 - B * 100 - C * 10);

        cout << "||==========|=========|========|========|========|========|" << endl;
        cout << "|| Bulls    |  Cows   |          Guesses                  |" << endl;
        cout << "||==========|=========|========|========|========|========|" << endl;

        int code, bulls = 0, cows = 0;
        int A_, B_, C_, D_;
        cout << "please input your 4 numbers" << endl;
        cin >> code;
        A_ = code / 1000;
        B_ = (code - A_ * 1000) / 100;
        C_ = (code - A_ * 1000 - B_ * 100) / 10;
        D_ = (code - A_ * 1000 - B_ * 100 - C_ * 10);
        int arr[4] = {A, B, C, D};
        int arr_[4] = {A_, B_, C_, D_};
        for (int i = 0; i < 4; i++)
        {
            if (arr[i] = arr_[i])
            {
                bulls++;
            }
        }

        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                if (i != j)
                {
                    if (arr[i] = arr_[j])
                    {
                        cows++;
                    }
                }
            }
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
