
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
#include <algorithm>

namespace bulls_and_cows {

    void user_plays_against_computer(const GameOptions& game_options)
    {
        Code code = generate_secret_code(game_options);
        
        AttemptBullsCows attempt_bulls_cows{};
        Historic historic{};
        do
        {
            std::cout << "\nEnter your new attempt (length of " << game_options.number_of_characters_per_code
                      << " and character between " << game_options.minimum_allowed_character << " and "
                      << game_options.maximum_allowed_character << ") :";
            attempt_bulls_cows.attempt = do_attempt(std::cin, game_options);

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
    unsigned int count_cow(Code attempt_variable, Code const& code)
    {
        //We need to retreive the bulls to avoid counting them as cows when there are duplicates
        for (int i = 0; i < code.value.size(); i++)
        {
            if (attempt_variable.value[i] == code.value[i])
            {
                attempt_variable.value[i]='0';
            }
        }

        unsigned int cow = 0;
        for (int i = 0; i < code.value.size(); i++)
        {
            for (int j = 0; j < attempt_variable.value.size(); j++)
            {
                if (attempt_variable.value[j] == code.value[i] && i != j)
                {
                    //To count each character only 1 time, we change their value to a forbidden character
                    attempt_variable.value[j]='0';
                    cow++;
                }

            }
        }
        return cow;
    }

    // Return a vector of char containing random different char with the length defined in the options
    Code generate_secret_code(const GameOptions& game_options)
    {
        Code code;
        code.value = "";
        if (game_options.allow_duplicate)
        {
            for (unsigned int i = 0; i < game_options.number_of_characters_per_code; i++)
            {
                code.value.push_back(generate_random_character(game_options.minimum_allowed_character,game_options.maximum_allowed_character));
            }
        }
        else
        {
            std::string dictionary = "";
            for (char i = game_options.minimum_allowed_character; i < game_options.maximum_allowed_character+1; i++)
            {
                dictionary.push_back(i);
            }

            for (unsigned int i = 0; i < game_options.number_of_characters_per_code; i++)
            {
                int random_integer = generate_random_integer(0,static_cast<int>(std::size(dictionary))-1);
                code.value.push_back(dictionary[random_integer]);
                dictionary.erase(dictionary.begin() + random_integer);
            }
        }
        
        return code;
    }

    //Ask to the user to write a attempt
    Code do_attempt(std::istream& input_stream, const GameOptions& game_options)
    {
        Code code;
        do
        {
            input_stream >> code.value;

            switch (check_input(code.value, game_options))
            {
            case (CheckInput::WrongNumberChars):
                std::cout << "Wrong number of characters. Try again\n";
                std::cout << "\nEnter your new attempt (length of " << game_options.number_of_characters_per_code
                          << " and character between " << game_options.minimum_allowed_character << " and "
                          << game_options.maximum_allowed_character << ") :";
                break;
            case (CheckInput::CharacterOutOfRange):
                std::cout << "Character(s) not allowed in your attempt. Try again\n";
                std::cout << "\nEnter your new attempt (length of " << game_options.number_of_characters_per_code
                          << " and character between " << game_options.minimum_allowed_character << " and "
                          << game_options.maximum_allowed_character << ") :";
                break;
            case (CheckInput::Duplicate):
                std::cout << "There is at least one duplicate in your input. Try again\n";
                std::cout << "\nEnter your new attempt (length of " << game_options.number_of_characters_per_code
                          << " and character between " << game_options.minimum_allowed_character << " and "
                          << game_options.maximum_allowed_character << ") :";
                break;
            default:
                break;
            }

        } while (check_input(code.value, game_options)!=CheckInput::Valid);
        
        return code;
    }

    //Function return true if no duplicate is find
    bool check_duplicates(std::string code)
    {
        //We sort the code
        std::sort(code.begin(), code.end());
        //We check if there is two consecutive elements that are the same (duplicates)
        //Adjacent_find will return the last element if there is no duplicate found
        return std::adjacent_find(code.begin(), code.end()) != code.end();
    }

    // Function to check if the input of the user for a attempt is right : length, characters allowed, duplicates
    CheckInput check_input(std::string const& attempt, const GameOptions& game_options)
    {
        // Check for the number of characters
        if (attempt.size() != game_options.number_of_characters_per_code)
        {
            return CheckInput::WrongNumberChars;
        }

        if (!game_options.allow_duplicate)
        {
            // Check for the duplicates
            if (check_duplicates(attempt))
            {
                return CheckInput::Duplicate;
            }
        }
        
        // Check for characters allowed
        for (char c : attempt)
        {
            if (c < game_options.minimum_allowed_character ||
                c > game_options.maximum_allowed_character)
            {
                return CheckInput::CharacterOutOfRange;
            }
        }

        return CheckInput::Valid;
    }

    //Check if the attempt has already been made, return true if the attempt is new/valid
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

    void erase_invalid_solutions(PossibleSolutions& solutions,const AttemptBullsCows& attempt_bulls_cows)
    {
        solutions.codes.erase(
            std::remove_if(solutions.codes.begin(), solutions.codes.end(),
                           [attempt_bulls_cows](const Code code) {
                               if (count_cow(code, attempt_bulls_cows.attempt) != attempt_bulls_cows.cows)
                               {
                                   return true;
                               }
                               else
                               {
                                   if (count_bull(code, attempt_bulls_cows.attempt) != attempt_bulls_cows.bulls)
                                   {
                                       return true;
                                   }
                               }
                               return false;
                           }),
            solutions.codes.end());
    }

    Code computer_attempt(const GameOptions& game_options,PossibleSolutions& solutions)
    {
        Code attempt{};
        const int random_solution = generate_random_integer(0, static_cast<int> (solutions.codes.size()-1));
        attempt = solutions.codes[random_solution];
        solutions.codes.erase(solutions.codes.begin() + random_solution);
        
        return attempt;
    }

    void computer_plays_against_computer(const GameOptions& game_options)
    {
        PossibleSolutions solutions = generate_all_possible_codes(game_options);

        Code code = generate_secret_code(game_options);

        AttemptBullsCows attempt_bulls_cows;
        Historic historic;

        do
        {
            std::cout << "There are " << solutions.codes.size() << " possible solutions\n";

            attempt_bulls_cows.attempt = computer_attempt(game_options,solutions);

            attempt_bulls_cows.bulls = count_bull(attempt_bulls_cows.attempt, code);
            attempt_bulls_cows.cows = count_cow(attempt_bulls_cows.attempt, code);

            if (attempt_bulls_cows.bulls != game_options.number_of_characters_per_code && solutions.codes.size()!=1)
            {
                erase_invalid_solutions(solutions,attempt_bulls_cows);
            }
            
            historic.value.push_back(attempt_bulls_cows);

            display_board(historic, game_options);
            std::this_thread::sleep_for(std::chrono::milliseconds(2000));
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
        
        do
        {
            display_game_options(std::cout,game_options);
            display_game_options_menu(std::cout);
            choice = ask_game_options_menu_choice(std::cin);
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
