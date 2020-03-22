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
#include <iterator>
#include <thread>
#include <vector>

namespace bulls_and_cows {

    bool checkDoublons(std::vector<char> const& code, char charCode)
    {
        for (int unsigned i = 0; i < code.size(); i++)
        {
            if (code[i] == charCode)
            {
                return false;
            }
        }
        return true;
    }

    std::vector<char> secretCodeMethod(const GameOptions& game_options)
    {
        std::vector<char> secretCode;
        char charCode;
        for (int unsigned i = 0; i < game_options.number_of_characters_per_code; i++)
        {
            do
            {
                charCode = generate_random_character(game_options.minimum_allowed_character,
                                                     game_options.maximum_allowed_character);
            } while (!checkDoublons(secretCode, charCode));

            secretCode.push_back(charCode);
        }
        return secretCode;
    }

    void printCode(std::vector<char> const& code)
    {
        for (int unsigned i = 0; i < code.size(); i++)
        {
            std::cout << code[i];
        }
        std::cout << "\n";
    }

    void printTableauFinal(std::vector<std::vector<char>> const& tableauFinal)
    {
        for (int unsigned i = 0; i < tableauFinal.size(); i++)
        {
            std::cout << tableauFinal[0][i];
        }
        std::cout << "\n";
    }

    bool checkDoublonsString(std::string const& code)
    {
        char charCode(0);
        for (int unsigned i = 0; i < code.size(); i++)
        {
            charCode = code[i];
            for (int unsigned j = 0; j < code.size(); j++)
            {
                if (charCode == code[j] && i != j)
                {
                    std::cout << "il y a deux fois la meme lettre \n";
                    return false;
                }
            }
        }
        return true;
    }

    bool checkErrorAttemps(std::string const& code, const GameOptions& game_options)
    {
        if (code.size() != game_options.number_of_characters_per_code)
        {
            std::cout << "La taille ne convient pas \n";
            return false;
        }

        for (unsigned int i = 0; i < code.size(); i++)
        {
            if (code[i] > game_options.maximum_allowed_character || code[i] < game_options.minimum_allowed_character)
            {
                std::cout << "Une lettre n'est pas dans la range demandé dans les options \n";
                return false;
            }
        }
        return true;
    }

    std::vector<char> attempsMethod(const GameOptions& game_options)
    {
        std::vector<char> userCode;
        std::string code;
        do
        {
            std::cout << "Rentrez votre code : ";
            std::cin >> code;
        } while (!checkDoublonsString(code) || !checkErrorAttemps(code, game_options));

        for (int unsigned i = 0; i < game_options.number_of_characters_per_code; i++)
        {
            userCode.push_back(code[i]);
        }
        return userCode;
    }


    std::vector<char> attempsMethodComputer(const GameOptions& game_options,
                                            std::vector<std::vector<char>> const& tableauFinal)
    {
        std::vector<char> userCode;
        bool accept(true);
        do
        {
            userCode = secretCodeMethod(game_options);
            for (unsigned int i = 0; i < tableauFinal.size(); i++)
            {
                if (userCode == tableauFinal[i])
                {
                    accept = false;
                }
            }
        } while (!accept);

        return userCode;
    }

    bool checkWin(std::vector<char> secretCodeComputer, std::vector<char> attemps)
    {
        if (secretCodeComputer == attemps)
        {
            return true;
        }
        return false;
    }

    int cowsMethod(std::vector<char> secretCodeComputer, std::vector<char> attemps)
    {
        int count(0);
        for (int unsigned i = 0; i < attemps.size(); i++)
        {
            for (int unsigned j = 0; j < attemps.size(); j++)
            {
                if (secretCodeComputer[i] == attemps[j] && i != j)
                {
                    count++;
                }
            }
        }
        return count;
    }

    int bullsMethod(std::vector<char> secretCodeComputer, std::vector<char> attemps)
    {
        int count(0);
        for (int unsigned i = 0; i < attemps.size(); i++)
        {
            if (secretCodeComputer[i] == attemps[i])
            {
                count++;
            }
        }
        return count;
    }

    void user_plays_against_computer(const GameOptions& game_options)
    {
        std::vector<char> secretCodeComputer = secretCodeMethod(game_options);
        printCode(secretCodeComputer);
        std::cout << "\n";

        std::vector<std::vector<char>> tableauFinal;
        tableauFinal.push_back(secretCodeComputer);

        std::vector<char> attemps;

        unsigned int count(1);
        int bulls(0);
        int cows(0);
        int win(0);

        do
        {
            attemps = attempsMethod(game_options);
            bulls = bullsMethod(secretCodeComputer, attemps);
            cows = cowsMethod(secretCodeComputer, attemps);
            printCode(attemps);
            std::string bullsCast = std::to_string(bulls);
            std::string cowsCast = std::to_string(cows);

            tableauFinal.push_back(attemps);
            tableauFinal[count].push_back(bullsCast[0]);
            tableauFinal[count].push_back(cowsCast[0]);

            boardGame(tableauFinal, game_options, count);

            if (checkWin(secretCodeComputer, attemps))
            {
                std::cout << "You win \n";
                win = 1;
            }
            if (count == game_options.max_number_of_attempts)
            {
                win = 1;
                std::cout << "you lose \n";
            }
            count++;
        } while (win == 0);
    }

    void computer_plays_against_computer(const GameOptions& game_options)
    {
        std::vector<char> secretCodeComputer = secretCodeMethod(game_options);
        printCode(secretCodeComputer);
        std::cout << "\n";

        std::vector<std::vector<char>> tableauFinal;
        tableauFinal.push_back(secretCodeComputer);

        std::vector<char> attemps;

        unsigned int count(1);
        int bulls(0);
        int cows(0);
        int win(0);

        do
        {
            attemps = attempsMethodComputer(game_options, tableauFinal);
            bulls = bullsMethod(secretCodeComputer, attemps);
            cows = cowsMethod(secretCodeComputer, attemps);
            std::string bullsCast = std::to_string(bulls);
            std::string cowsCast = std::to_string(cows);

            tableauFinal.push_back(attemps);
            tableauFinal[count].push_back(bullsCast[0]);
            tableauFinal[count].push_back(cowsCast[0]);

            boardGame(tableauFinal, game_options, count);

            std::this_thread::sleep_for(std::chrono::milliseconds(1000));

            if (checkWin(secretCodeComputer, attemps))
            {
                std::cout << "You win \n";
                win = 1;
            }
            if (count == game_options.max_number_of_attempts)
            {
                win = 1;
                std::cout << "you lose \n";
            }
            count++;
        } while (win == 0);

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
