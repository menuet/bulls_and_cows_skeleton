
#include "game.hpp"
#include "board.hpp"
#include "game_options.hpp"
#include "game_solver.hpp"
#include "input.hpp"
#include "main_menu.hpp"
#include "random.hpp"
#include <fstream>
#include <iostream>
#include <thread>
#include <vector>
#include <list>



namespace bulls_and_cows {

    void user_plays_against_computer(const GameOptions& game_options)
    {

        // CREATING BOARD using functions we implemented
        Board myboard = create_board(game_options);

        // While the user didn't win or reach max attempt number, while loop

        while (!is_end_of_game(game_options, myboard) && !is_win(game_options, myboard))
        {
            // First display of the empty board
            display_board(std::cout, game_options, myboard);

            // Asking attemp to the user
            Code tempattemp = ask_attempt(std::cout, std::cin, game_options, myboard);
            if (validate_attempt(game_options, tempattemp))
            {
                AttemptAndFeedback newattemp;
                newattemp.attempt = tempattemp;
                newattemp.feedback = compare_attempt_with_secret_code(tempattemp, myboard.secret_code);
                myboard.attempts_and_feedbacks.push_back(newattemp);
            }
                
        }

        std::cout << (is_win(game_options, myboard) ? "You won !! GG WP\n" : "");
        std::cout << (is_end_of_game(game_options, myboard) ? "You lost, please try again and not cry\n The code was" + myboard.secret_code.value : "");
    }

    void computer_plays_against_computer(const GameOptions& game_options)
    {
        //Generaation of all solutions, and creation of the board
        PossibleSolutions allpos = generate_all_possible_codes(game_options);
        std::cout << "Game has " << allpos.codes.size() << " solutions\n";
        Board cvscboard = create_board(game_options);

        //while the game is not finished
        while (!is_end_of_game(game_options, cvscboard) &&
               !is_win(game_options, cvscboard))
        {
            // Display of the board
            display_board(std::cout, game_options, cvscboard);
            std::cout << "Solutions left: " << allpos.codes.size() << "\n";

            // Asking  computer to pick a random attempt
            Code randatt = pick_random_attempt(allpos);
            std::cout << "Computer picked the code: " << randatt.value << "\n";

            // Creation of an attempt, and normal way of playing goes on
            AttemptAndFeedback newattemp;
            newattemp.attempt = randatt;
            newattemp.feedback = compare_attempt_with_secret_code(randatt, cvscboard.secret_code);
            std::cout << "Bulls : " << newattemp.feedback.bulls << " Cows : " << newattemp.feedback.cows << "\n";
            cvscboard.attempts_and_feedbacks.push_back(newattemp);
            //std::cout << "Secret code is : " << cvscboard.secret_code.value << "\n";

            // Remove the impossible solutions from the vector
            remove_incompatible_codes_from_possible_solutions(newattemp, allpos);
            
            std::this_thread::sleep_for(std::chrono::seconds(2));
        }
        if (is_win(game_options, cvscboard))
        {
            std::cout << "The secret code was : " << allpos.codes[0].value << " \nGG !\n";
        }
        else
        {
            std::cout << "Damn, this computer is so bad, put it in microwave.\n";
        }
    }

    void configure_game_options(GameOptions& game_options)
    {
        bool getout = false;
        while (!getout)
        {

            display_game_options(std::cout, game_options);
            display_game_options_menu(std::cout);
            std::cout << "What is your choice ? ";
            const auto user_choice = ask_game_options_menu_choice(std::cin); // auto in order to take any input of the user


            switch (user_choice) // depending on input
            {
            case GameOptionsMenuChoice::BackToMain:
                getout = true;
                break;
            case GameOptionsMenuChoice::ModifyMaximumAllowedCharacter: {

                std::cout << "Enter the maximum character you want:";
                char newmax = ask_char_or_default(std::cin, game_options.maximum_allowed_character);
                unsigned int range = newmax - game_options.minimum_allowed_character; // number of character available
                if (newmax < game_options.minimum_allowed_character)    // security for maximum
                {
                    std::cout << "Maximum cannot be inferior to minimum\n";
                }
                if (range < game_options.number_of_characters_per_code) // in order to use unicity gamemode, number of allowed character needs to be equal or superior to number of character per code
                {
                    std::cout << "Character range is too short, please first reduce number of character per code";
                }
                else
                    game_options.maximum_allowed_character = newmax;
                break;
            }
            case GameOptionsMenuChoice::ModifyMaximumNumberOfAttempts: {

                std::cout << "Enter the number of attempts you want:";
                unsigned int newmax = ask_uint_or_default(std::cin, game_options.max_number_of_attempts);
                unsigned int range = game_options.maximum_allowed_character - game_options.minimum_allowed_character;
                if (newmax <= 20)
                {
                    if (range > newmax)
                        game_options.max_number_of_attempts = newmax;
                    else
                        std::cout << "Warning: This number of attempts does not allow unicity, please try another "
                                     "value or change allowed characters";
                }
                else // Set of a maximum, in order not to let the user make the game crash on purpose
                    std::cout << "Number of attempts cannot exceed 20 attempts\n";
                break;
            }
            case GameOptionsMenuChoice::ModifyMinimumAllowedCharacter: {
                std::cout << "Enter the minimum character you want:";
                char newmin = ask_char_or_default(std::cin, game_options.minimum_allowed_character);
                unsigned int range = game_options.maximum_allowed_character - newmin;
                if (newmin > game_options.maximum_allowed_character)
                {
                    std::cout << "Minimum cannot be superior to maximum\n";
                }
                if (range < game_options.number_of_characters_per_code)
                {
                    std::cout << "Character range is too short, please first reduce number of character per code";
                }
                else
                    game_options.minimum_allowed_character = newmin;
                break;
            }
            case GameOptionsMenuChoice::ModifyNumberOfCharactersPerCode: {

                std::cout << "Enter the number of characters per code:";
                unsigned int newmax = ask_uint_or_default(std::cin, game_options.number_of_characters_per_code);
                if (newmax <= 10)
                {
                    game_options.number_of_characters_per_code = newmax;
                }
                else
                    std::cout << "Number of characters per code cannot exceed 10\n";
                break;
            }
            case GameOptionsMenuChoice::LoadOptions: {
                std::ifstream in{"game_options.txt"};
                load_game_options(in, game_options);
                break;
            }
            case GameOptionsMenuChoice::SaveOptions: {
                std::ofstream out{"game_options.txt"};
                save_game_options(out, game_options);
                break;
            }
            case GameOptionsMenuChoice::UniqueCharacters: {
                std::cout << "Enter 0/1: ";
                std::string ans;
                std::cin >> ans;
                if (ans == "0")
                    game_options.unique_characters = false;
                else if (ans == "1")
                    game_options.unique_characters = true;
                else
                    std::cout << "Unknown input";
                break;
            }
            default:
                std::cout << "Unknown request, please enter a valid choice\n";
            
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
                std::cout << "\nSee you later, aligator !\n";
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
