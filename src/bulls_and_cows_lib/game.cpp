
#include "game.hpp"
#include "board.hpp"
#include "game_options.hpp"
#include "game_solver.hpp"
#include "input.hpp"
#include "main_menu.hpp"
#include <bulls_and_cows_lib\random.hpp>
#include <chrono>
#include <fstream>
#include <iostream>
#include <thread>
#include <vector>

namespace bulls_and_cows {

    void user_plays_against_computer(const GameOptions& game_options)
    {
        Code code = generate_secret_code(game_options);
        
        AttemptBullsCows attempt_bulls_cows;
        Historic historic;

        do
        {
            attempt_bulls_cows.attempt = do_attempt(game_options);

            attempt_bulls_cows.bulls = count_bull(attempt_bulls_cows.attempt, code);
            attempt_bulls_cows.cows = count_cow(attempt_bulls_cows.attempt, code);

            historic.value.push_back(attempt_bulls_cows);

            display_board(historic, game_options);
        } while (historic.value.size() < game_options.max_number_of_attempts &&
                 !(attempt_bulls_cows.bulls == game_options.number_of_characters_per_code));
        //The game keep going while the user has not reach the maximum number of attempts or has find the good code (bulls = number of characters in the code)

        if (attempt_bulls_cows.bulls == game_options.number_of_characters_per_code)
        {
            std::cout << "You have win! :)";
        }
        else
        {
            std::cout << "You have reach the maximum number of attempts allowed, you have loose :("
                         "\nThe solution was " << code.value;
        }
    }

    // Count and return the number of bulls in the attempt
    unsigned int count_bull(Code const& attempt, Code const& code)
    {
        unsigned int bull = 0;
        for (int i = 0; i < code.value.size(); i++)
        {
            if (attempt.value[i] == code.value[i])
            {
                bull++;
            }
        }
        return bull;
    }

    // Count and return the number of cows in the attempt
    unsigned int count_cow(Code const& attempt, Code const& code)
    {
        unsigned int cow = 0;
        for (int i = 0; i < code.value.size(); i++)
        {
            for (int j = 0; j < attempt.value.size(); j++)
            {
                if (attempt.value[j] == code.value[i] && i != j)
                {
                    cow++;
                }
            }
        }
        return cow;
    }

    // Return true if the is no duplicate in the current code (vector)
    bool check_duplicates(Code const& code, int current_index)
    {
        if (current_index == 0)
        {
            return true;
        }
        for (int i = 0; i < current_index; i++)
        {
            if (code.value[current_index] == code.value[i])
            {
                return false;
            }
        }
        return true;
    }

    // Return a vector of char containing random different char with the length defined in the options
    Code generate_secret_code(const GameOptions& game_options)
    {
        Code code;
        code.value = "";
        for (unsigned int i = 0; i < game_options.number_of_characters_per_code; i++)
        {
            code.value.push_back(generate_random_character(game_options.minimum_allowed_character,
                                                           game_options.maximum_allowed_character));
            while (!check_duplicates(code, i))
            {
                code.value[i] = generate_random_character(game_options.minimum_allowed_character,
                                                    game_options.maximum_allowed_character);
            }
        }
        return code;
    }

    //Ask to the user to write a attempt
    Code do_attempt(const GameOptions& game_options)
    {
        Code code;
        do
        {
            std::cout << "\nEnter your new attempt (length of " << game_options.number_of_characters_per_code
                      << " and character between "
                 << game_options.minimum_allowed_character << " and " << game_options.maximum_allowed_character
                 << ") :";
            std::cin >> code.value;

        } while (!check_input(code.value, game_options));
        
        return code;
    }

    // Function to check if the input of the user for a attempt is right : length, characters allowed, duplicates
    bool check_input(std::string const& attempt, const GameOptions& game_options)
    {
        // Check for the number of characters
        if (attempt.size() != game_options.number_of_characters_per_code)
        {
            std::cout << "Wrong number of characters. Try again\n";
            return false;
        }

        // Check for the duplicates
        for (int i = 0; i < attempt.size(); i++)
        {
            for (int j = i+1; j < attempt.size(); j++)
            {
                if (attempt[i] == attempt[j])
                {
                    std::cout << "There is at least one duplicate in your input. Try again\n";
                    return false;
                }
            }
        }
        
        // Check for characters allowed
        for (char c : attempt)
        {
            if (c < game_options.minimum_allowed_character ||
                c > game_options.maximum_allowed_character)
            {
                std::cout << "Character(s) not allowed in your attempt. Try again\n";
                return false;
            }
        }

        return true;
    }

    bool check_attempt(Code const& attempt, Historic const& historic)
    {
        for (AttemptBullsCows historic_attempt : historic.value)
        {
            if (historic_attempt.attempt.value==attempt.value)
            {
                return false;
            }
        }
        return true;
    }


    void computer_plays_against_computer(const GameOptions& game_options)
    {
        Code code = generate_secret_code(game_options);

        AttemptBullsCows attempt_bulls_cows;
        Historic historic;

        do
        {
            do
            {
                attempt_bulls_cows.attempt = generate_secret_code(game_options);
            } while (!check_attempt(attempt_bulls_cows.attempt, historic));

            attempt_bulls_cows.bulls = count_bull(attempt_bulls_cows.attempt, code);
            attempt_bulls_cows.cows = count_cow(attempt_bulls_cows.attempt, code);

            historic.value.push_back(attempt_bulls_cows);

            display_board(historic, game_options);
            std::this_thread::sleep_for(std::chrono::milliseconds(0));
        } while (historic.value.size() < game_options.max_number_of_attempts &&
                 !(attempt_bulls_cows.bulls == game_options.number_of_characters_per_code));
        // The game keep going while the computer has not reach the maximum number of attempts or has find the good code
        // (bulls = number of characters in the code)

        if (attempt_bulls_cows.bulls == game_options.number_of_characters_per_code)
        {
            std::cout << "You have win! :)";
        }
        else
        {
            std::cout << "You have reach the maximum number of attempts allowed, you have loose :("
                    "\nThe solution was " << code.value;
        }
    }

    void configure_game_options(GameOptions& game_options)
    {
        GameOptionsMenuChoice choice;
        std::cout << "TODO:\n"
                "    DO\n"
                "       Display the current game options\n"
                "       Display the game options menu\n"
                "       Ask the user to type its choice\n"
                "       Treat the user's choice\n"
                "    UNTIL user's choice is to go back to main menu\n";
        do
        {
            display_game_options(game_options);
            display_game_options_menu();
            choice = ask_game_options_menu_choice();
            manage_game_options(choice, game_options);
        } while (choice != GameOptionsMenuChoice::BackToMain);
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
