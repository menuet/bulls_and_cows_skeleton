
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
            Code attempt = ask_attempt(std::cout, std::cin, game_options, boardCreated);

            Feedback feed = compare_attempt_with_secret_code(attempt, boardCreated.secret_code);
            AttemptAndFeedback att_feed;
            att_feed.attempt = attempt;
            att_feed.feedback = feed;
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
            std::this_thread::sleep_until(std::chrono::system_clock::now() + std::chrono::seconds(2));
            Code codeAttempt = pick_random_attempt(possible_solutions); // bien jusque là
            Feedback feed = compare_attempt_with_secret_code(codeAttempt, boardCreated.secret_code);
            AttemptAndFeedback attempt_and_feedback;
            attempt_and_feedback.attempt = codeAttempt;
            attempt_and_feedback.feedback = feed;
            boardCreated.attempts_and_feedbacks.push_back(attempt_and_feedback);

            std::cout << "\n";
            remove_incompatible_codes_from_possible_solutions(attempt_and_feedback,possible_solutions);

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
                break;
            case GameOptionsMenuChoice::ModifyMaximumNumberOfAttempts: {
                std::cout << "Enter the Maximum Number of Attempts (maximum allowed is 12): ";
                const int user_maxAttempts = ask_int_or_default(std::cin, -1);
                if (user_maxAttempts < 1 || user_maxAttempts > 12)
                {
                    std::cout << "\nPlease enter a correct Maximum Number of Attempts (maximum allowed is 12, minimum "
                                 "is 1) \n";
                }
                else
                {
                    game_options.max_number_of_attempts = user_maxAttempts;
                }
                break;
            }
            case GameOptionsMenuChoice::ModifyNumberOfCharactersPerCode: {
                std::cout << "Enter the Number of characters Per Code (maximum allowed is 6): ";
                const int user_nbChara = ask_int_or_default(std::cin, -1);
                if (user_nbChara < 1 || user_nbChara > 6)
                {
                    std::cout << "\nPlease enter a correct Number of characters Per Code (maximum allowed is 6) \n";
                }
                else
                {
                    game_options.number_of_characters_per_code = user_nbChara;
                }
                break;
            }
            case GameOptionsMenuChoice::ModifyMinimumAllowedCharacter: {
                std::cout << "Enter the Minimum allowed character to modify the previous one: ";
                const char user_miniChara = ask_char_or_default(std::cin, 0);
                if (user_miniChara > game_options.maximum_allowed_character)
                {
                    std::cout
                        << "\nPlease enter a correct Minimum allowed character (inferior than the Maximum allowed "
                           "character) \n";
                }
                else
                {
                    game_options.minimum_allowed_character = user_miniChara;
                }
                break;
            }
            case GameOptionsMenuChoice::ModifyMaximumAllowedCharacter: {
                std::cout << "Enter the Maximum allowed character to modify the previous one: ";
                const char user_maxiChara = ask_char_or_default(std::cin, 0);
                if (user_maxiChara < game_options.minimum_allowed_character)
                {
                    std::cout
                        << "\nPlease enter a correct Maximum allowed character (superior than the Minimum allowed "
                           "character) \n";
                }
                else
                {
                    game_options.maximum_allowed_character = user_maxiChara;
                }
                break;
            }
            case GameOptionsMenuChoice::SaveOptions: {
                std::ofstream game_options_file{"game_options.txt", std::ios::app};
                bool saved = save_game_options(game_options_file, game_options);
                if (saved)
                {
                    std::cout << "Success: the game options are saved correctly\n";
                }
                else
                {
                    std::cout << "Error: the game options are not saved correctly\n";
                }
                game_options_file.close();
                break;
            }
            case GameOptionsMenuChoice::LoadOptions: {
                std::ifstream file("game_options.txt");
                bool loaded = false;
                loaded = load_game_options(file, game_options);
                if (loaded)
                {
                    std::cout << "Success: the game options are loaded correctly\n";
                }
                else
                {
                    std::cout << "Error: the game options are not loaded correctly\n";
                }
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
