
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
    
    Board board = bulls_and_cows::create_board(game_options);

        AttemptAndFeedback newattemp;

        while (!is_end_of_game(game_options, board) && !is_win(game_options, board))
        {

            display_board(std::cout, game_options, board);

            newattemp.attempt = ask_attempt(std::cout, std::cin, game_options, board);

            newattemp.feedback = compare_attempt_with_secret_code(newattemp.attempt, board.secret_code);

            board.attempts_and_feedbacks.push_back(newattemp);
        }

        if (is_win(game_options, board))
        {

            std::cout << "you won" << std::endl;
        }

        else

            std::cout << "Try again" << std::endl;
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
        std::ifstream in{"game_options.txt"};

        bool getout = false;

        while (!getout)

        {

            display_game_options(std::cout, game_options);

            display_game_options_menu(std::cout);

            const auto user_choice = ask_game_options_menu_choice(std::cin);

            switch (user_choice)

            {

            case GameOptionsMenuChoice::BackToMain:

                getout = true;

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
