
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

    void user_plays_against_computer(const GameOptions& game_options)// Beaucoup de fonction d'affichage donc pas besoin de plus expliquer
    {
        // Create a board with a randomly generated secret code\n"

        Board my_screen{};

        AttemptAndFeedback my_feedback{};

        my_screen = create_board(game_options);

        do

        {

            std::cout << "\n";

            display_board(std::cout, game_options, my_screen);

            my_feedback.attempt = ask_attempt(std::cout, std::cin, game_options, my_screen);

            while (!validate_attempt(game_options, my_feedback.attempt))

            {

                std::cout << "Try again, you're not good yet! \n";

                my_feedback.attempt = ask_attempt(std::cout, std::cin, game_options, my_screen);
            }

            my_feedback.feedback = compare_attempt_with_secret_code(my_feedback.attempt, my_screen.secret_code);

            my_screen.attempts_and_feedbacks.push_back(my_feedback);

        } while (!(is_end_of_game(game_options, my_screen)) && !(is_win(game_options, my_screen)));

        std::cout << "\n";

        display_board(std::cout, game_options, my_screen);

        if (is_win(game_options, my_screen))

        {

            std::cout << "\n"

                      << "You are the best  ! The secret code is : " << my_screen.secret_code.value << "\n";
        }

        else

        {

            std::cout << "\n"

                      << "LOOSER!!!! BOUHHHH! The secret code is : " << my_screen.secret_code.value << "\n";
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
        /*display_game_options_menu(std::cout);*/
        while (true)

        {

            display_game_options(std::cout, game_options);

            display_game_options_menu(std::cout);

            GameOptionsMenuChoice user_choice = ask_game_options_menu_choice(std::cin);

            switch (user_choice) // require int type

            {

            case GameOptionsMenuChoice::BackToMain:

                return;

            case GameOptionsMenuChoice::ModifyMaximumNumberOfAttempts:

                std::cout << " 1 - Modify maximum number of attemps per game\n";

                std::cin >> game_options.max_number_of_attempts;

                break;

            case GameOptionsMenuChoice::ModifyNumberOfCharactersPerCode:

                std::cout << " 2 - Modify number of character in a code \n";

                std::cin >> game_options.number_of_characters_per_code;

                break;

            case GameOptionsMenuChoice::ModifyMinimumAllowedCharacter:

                std::cout << "3 - Modify Minimun allowed character\n";

                std::cin >> game_options.minimum_allowed_character;

                break;

            case GameOptionsMenuChoice::ModifyMaximumAllowedCharacter:

                std::cout << "4 - Modify Maximum allowed character \n";

                std::cin >> game_options.maximum_allowed_character;

                break;

            case GameOptionsMenuChoice::SaveOptions:

                save_game_options(std::cout, game_options);

                break;

            case GameOptionsMenuChoice::LoadOptions:

                load_game_options(std::cin, game_options);

                break;

            default:

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
