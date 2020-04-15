
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
        
        Board Board;
        std::cout << "    \n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n"
                     "    Prepare yourself for a game against yourself or the computer\n"
                     "    Create a randomly generated secret code\n"
                     "    >Press 1 ...\n"
                     "    If you want to play against a code that you enter yourself\n"
                     "    >Press 2 ...\n"
                     "What is your choice ? \n -> ";
                    
        auto user_choice = ask_main_random_or_typed(std::cin); //proposition de jouer contre un code aleatoire ou soi-même (plus facile pour les tests)
        bool stop = false;
        while (stop == false)
        {
            switch (user_choice)
            {
            case MainMenuChoice1::Quit:
                std::cout << "\nBye bye!\n";
                stop = true;
                return;
            case MainMenuChoice1::RandomGenerator:
                Board.secret_code.value = create_secret_randomly(game_options, std::cin);
                stop = true;
                break;
            case MainMenuChoice1::UserGenerated:
                Board.secret_code.value = create_secret(game_options, std::cin);
                stop = true;
                break;
            case MainMenuChoice1::Error:
                std::cout << "\nYou did not enter a valid choice, please try again\n"
                             "What is your choice ? \n -> ";
                user_choice = ask_main_random_or_typed(std::cin);
                break;
            }
        }

        std ::cout << "Code secret utilise " << Board.secret_code.value << "\n";
        display_board(game_options, Board);
        bool end = false;
        bool win = false;
        Code Code;
        Feedback feedback;
        AttemptAndFeedback test;
        while (!end && !win)        //tant qu'on a pas trouve le bon code ou atteint la limite 
        {
            Code.value = create_attempt(game_options, std::cin); 
            test.attempt = Code;
            test.feedback = compare_attempt_with_secret_code(Code , Board.secret_code);
            Board.attempts_and_feedbacks.push_back(test);
            display_board(game_options, Board);
            win = is_win(game_options, Board);
            end = is_end_of_game(game_options, Board);
        }
        if (win)
        {
            std::cout << "\n '*'*'*'*' Congratulations '*'*'*'*' \n  "
                         "      You found the code with only "
                      << Board.attempts_and_feedbacks.size() 
                      << " attempts\n";
        }
        if (end && !win)
        {
            std::cout << "\n '*'*'*'*' You lost '*'*'*'*' \n  "
                         " Even with "
                      << game_options.max_number_of_attempts << " attempts you can't find this god damn code\n";
        }
    }

    void computer_plays_against_computer(const GameOptions& game_options)
    {
        std::cout   
            << "IA VS IA Qui gagnera ? J'ai mon idee :\n";
        Board Board;
        Board.secret_code.value = create_secret_randomly(game_options, std ::cin); //creation du code secret
        PossibleSolutions Codes = generate_all_possible_codes2(game_options);      //generation de tous les codes possibles
        std ::cout << "Code secret utilise " << Board.secret_code.value << "\n";
        bool end = false;
        bool win = false;
        Code Code;
        Feedback feedback;
        AttemptAndFeedback test;
        int result = 0;             //result stockera le nombre de combinaisons encore possible
        while (!end && !win)
        {   
            Code = pick_random_attempt(Codes);
            std ::cout << "Code test utilise " << Code.value << "\n";
            test.attempt = Code;
            test.feedback = compare_attempt_with_secret_code(Code, Board.secret_code);
            Board.attempts_and_feedbacks.push_back(test);
            display_board(game_options, Board);
            win = is_win(game_options, Board);
            end = is_end_of_game(game_options, Board);
            result = remove_incompatible_codes_from_possible_solutions(test, Codes);
            if (result == 1)
            {
                win = true;
            }
        }
        if (win)
        {
            std::cout << "\n '*'*'*'*' Congratulations '*'*'*'*' \n  "
                         "      You found the code with only "
                      << Board.attempts_and_feedbacks.size() << " attempts\n";
        }
        if (end && !win)
        {
            std::cout << "\n '*'*'*'*' You lost '*'*'*'*' \n  "
                         " Even with "
                      << game_options.max_number_of_attempts << " attempts you can't find this god damn code\n";
        }

    }

    void configure_game_options(GameOptions& game_options)
    {
        std::cout << "\n#################################\n";
        display_game_options_menu(std::cout);
        const auto user_choice = ask_games_options_choice(std::cin);
        switch (user_choice)
        {
        case GameOptionsMenuChoice::BackToMain:
            std::cout << "\nHere we go again\n";
            play_game();
            break;
        case GameOptionsMenuChoice::ModifyMaximumNumberOfAttempts:
            std::cout << "\nWill arrive soon\n";
            play_game();
            break;
        case GameOptionsMenuChoice::ModifyNumberOfCharactersPerCode:
            std::cout << "\nWill arrive soon\n";
            play_game();
            break;
        case GameOptionsMenuChoice::ModifyMinimumAllowedCharacter:
            std::cout << "\nWill arrive soon\n";
            play_game();
            break;
        case GameOptionsMenuChoice::ModifyMaximumAllowedCharacter:
            std::cout << "\nWill arrive soon\n";
            play_game();
            break;
        case GameOptionsMenuChoice::SaveOptions:
            std::cout << "\nWill arrive soon\n";
            play_game();
            break;
        case GameOptionsMenuChoice::LoadOptions:
            std::cout << "\nWill arrive soon\n";
            play_game();
            break;
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
