
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
#include <list>
#include <random>
#include <thread>
#include <vector>


namespace bulls_and_cows {

    void user_plays_against_computer(const GameOptions& game_options)
    {

        // CREATING BOARD using functions we implemented
        Board myboard = bulls_and_cows::create_board(game_options);

        // While the user didn't win or reach max attempt number, while loop

        while (!bulls_and_cows::is_end_of_game(game_options, myboard) && !bulls_and_cows::is_win(game_options, myboard))
        {
            // First display of the empty board

            bulls_and_cows::display_board(std::cout, game_options, myboard);

            // Asking attemp to the user

            Code tempattemp = bulls_and_cows::ask_attempt(std::cout, std::cin, game_options, myboard);
            if (bulls_and_cows::validate_attempt(game_options, tempattemp))
            {
                AttemptAndFeedback newattemp;
                newattemp.attempt = tempattemp;
                newattemp.feedback = bulls_and_cows::compare_attempt_with_secret_code(tempattemp, myboard.secret_code);
                myboard.attempts_and_feedbacks.push_back(newattemp);
            }
        }
        std::cout << (is_win(game_options, myboard) ? "You won !! GG WP\n" : "");
        std::cout << (is_end_of_game(game_options, myboard) ? "You lost, please try again and not cry\n" : "");
    }

    void computer_plays_against_computer(const GameOptions& game_options)
    {
        /*  std::cout
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

        Board computerboard = bulls_and_cows::create_board(game_options);
        std::vector<Code> all_possible{};
        Code origine;
        for (int i = 0; i < game_options.number_of_characters_per_code; i++)
        {
            origine.value.push_back(game_options.minimum_allowed_character);
        }
        while (origine.value[0] <= game_options.maximum_allowed_character)
        {
            all_possible.push_back(origine);
            origine.value[game_options.number_of_characters_per_code - 1]++;
        for (int i = game_options.number_of_characters_per_code - 1; i > 0; i--)
            {
                if (origine.value[i] > game_options.maximum_allowed_character)
                {
                    origine.value[i] = game_options.minimum_allowed_character;
                    int j = i-1;
                    origine.value[j]++;
                }
            }
        }
        
        bulls_and_cows::display_board(std::cout, game_options, computerboard);

        while (all_possible.size() > 0)
        {
            int r = bulls_and_cows::generate_random_integer(0, all_possible.size()-1);
            Code s = all_possible[r];
            AttemptAndFeedback newcomputerattemp;
            newcomputerattemp.attempt = s;
            newcomputerattemp.feedback = bulls_and_cows::compare_attempt_with_secret_code(s, computerboard.secret_code);

            ///////////////////
            /*     important pour gestion d'affichage du tableau et pour les vérifications de réussite/echec   */                                                      computerboard.attempts_and_feedbacks.push_back(newcomputerattemp);

            ///////////////////////////
            /*  ici, juste du visuel, rien d'impératif au bon foncitonnement  */   
            bulls_and_cows::display_board(std::cout, game_options, computerboard);


            if (bulls_and_cows::is_win(game_options, computerboard))
            {
                std::cout << "Bravo Computer\n";
                return;
            }
            if (bulls_and_cows::is_end_of_game(game_options, computerboard))
            {
                std::cout << "Dommage Computer\n";
                return;
            }

            for (int i = all_possible.size()-1; i >= 0; i--)
            {
                Feedback f;
                f = bulls_and_cows::compare_attempt_with_secret_code(s, all_possible[i]);
                if (newcomputerattemp.feedback.bulls != f.bulls || newcomputerattemp.feedback.cows != f.cows)
                {
                    all_possible.erase(all_possible.begin() + i);
                }
            }
            system("pause");
        }


        
        /********************************************************************************************************
         *
         *
         *
         ****************************************************************/
    }

    void configure_game_options(GameOptions& game_options)
    {
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
