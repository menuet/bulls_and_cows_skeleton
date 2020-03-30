
#include "game.hpp"
#include "board.hpp"
#include "game_options.hpp"
#include "game_solver.hpp"
#include "input.hpp"
#include "main_menu.hpp"
#include "random.hpp"
#include <chrono>
#include <fstream>
#include <iostream>
#include <thread>

namespace bulls_and_cows {

    void user_plays_against_computer(const GameOptions& game_options)
    {

        /* std::cout << "TODO:\n"
                      "    Create a board with a randomly generated secret code\n"
                      "    DO\n"
                      "       Display the board and the list of attempts so far\n"
                      "       Ask the user to make another attempt\n"
                      "       Compare the user's attempt with the secret code and deduce the number of bulls and cows\n"
                      "       Add the user's attempt to the list of attempts of the board\n"
                      "    WHILE not end of game\n"
                      "    Display the board and the list of attempts so far\n"
                      "    Display a message telling if the user won or lost\n";

        */

        Board board = create_board(game_options);
        bool resultat;

        do
        {
            display_board(std::cout, game_options, board);

            AttemptAndFeedback att;
            att.attempt = ask_attempt(std::cout, std::cin, game_options, board);

            att.feedback = compare_attempt_with_secret_code(att.attempt, board.secret_code);

            board.attempts_and_feedbacks.push_back(att);
        } while (!is_end_of_game(game_options, board) && !is_win(game_options, board));

        display_board(std::cout, game_options, board);

        resultat = is_win(game_options, board);

        if (resultat == true)
            std::cout << "YOU WIN!!!\n";
        else
            std::cout << "YOU LOST!!!\n";

        std::cout << "END OF GAME!!!\n";
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
                "    Display a message telling if the computer won or lost\n";*/

        Board board = create_board(game_options);
        Board compboard;

        do
        {
            display_board(std::cout, game_options, board);

            compboard = create_board(game_options);

            AttemptAndFeedback att;
            att.attempt = compboard.secret_code;
            att.feedback = compare_attempt_with_secret_code(att.attempt, board.secret_code);

            board.attempts_and_feedbacks.push_back(att);

        } while (!is_end_of_game(game_options, board));

        is_end_of_game(game_options, board);
        is_win(game_options, board);
    }

    void configure_game_options(GameOptions& game_options)
    {
        /* std::cout << "TODO:\n"
                      "    DO\n"
                      "       Display the current game options\n"
                      "       Display the game options menu\n"
                      "       Ask the user to type its choice\n"
                      "       Treat the user's choice\n"
                      "    UNTIL user's choice is to go back to main menu\n";*/

        bool verif = false;

        do
        {
            display_game_options(std::cout, game_options);
            display_game_options_menu(std::cout);

            const auto Choice = ask_game_options_menu_choice(std::cin);
           
            std::ifstream in{"C:/DEVCPP/bulls_and_cows_skeleton/game_options.txt"};
            std::ofstream out{"C:/DEVCPP/bulls_and_cows_skeleton/game_options.txt"};


            switch (Choice)
            {
            case GameOptionsMenuChoice::BackToMain:
                verif = true;
                break;

            case GameOptionsMenuChoice::Error:
                break;

            case GameOptionsMenuChoice::ModifyMaximumNumberOfAttempts:
                std::cout << "\nEnter the Maximum number of Attempts: ";
                game_options.max_number_of_attempts =
                    ask_uint_or_default(std::cin, game_options.max_number_of_attempts);
                break;

            case GameOptionsMenuChoice::ModifyNumberOfCharactersPerCode:
                std::cout << "\nEnter the Number of characters per code: ";
                game_options.number_of_characters_per_code =
                    ask_uint_or_default(std::cin, game_options.number_of_characters_per_code);
                break;

            case GameOptionsMenuChoice::ModifyMinimumAllowedCharacter:
                std::cout << "\nEnter the Minimum allowed character: ";
                game_options.minimum_allowed_character =
                    ask_char_or_default(std::cin, game_options.minimum_allowed_character);
                break;

            case GameOptionsMenuChoice::ModifyMaximumAllowedCharacter:
                std::cout << "\nEnter the Maximum allowed character: ";
                game_options.maximum_allowed_character =
                    ask_char_or_default(std::cin, game_options.maximum_allowed_character);
                break;

            case GameOptionsMenuChoice::SaveOptions:
                save_game_options(out, game_options);
                break;

            case GameOptionsMenuChoice::LoadOptions:
                
                load_game_options(in, game_options);
                break;
            }

        } while (!verif);
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
