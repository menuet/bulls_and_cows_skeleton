
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
#include <windows.h>
#include <tchar.h>
#include <stdio.h>

// Marc Belleperche m'a aid� pour ce TP pour l'impl�mentation de quelques fonctions (dans game.cpp ET game_option.cpp)

namespace bulls_and_cows {

    void user_plays_against_computer(const GameOptions& game_options)
    {
        Board board = bulls_and_cows::create_board(game_options);
        display_board(std::cout, game_options, board);
        
        while (bulls_and_cows::is_end_of_game(game_options, board) == false && bulls_and_cows::is_win(game_options, board) == false)
        {
            
            Code askattempt = bulls_and_cows::ask_attempt(std::cout, std::cin, game_options, board);

            if (bulls_and_cows::validate_attempt(game_options, askattempt))
            {
                AttemptAndFeedback new_askattempt;
                new_askattempt.attempt = askattempt;

                new_askattempt.feedback = bulls_and_cows::compare_attempt_with_secret_code(askattempt, board.secret_code);

                board.attempts_and_feedbacks.push_back(new_askattempt);
            }
            bulls_and_cows::display_board(std::cout, game_options, board);
        }
        
       
    }


    

    void computer_plays_against_computer(const GameOptions& game_options)
    {
        PossibleSolutions possible_solution = generate_all_possible_codes(game_options);
        Board ia_board = create_board(game_options);
        display_board(std::cout, game_options, ia_board);


        while (bulls_and_cows::is_end_of_game(game_options, ia_board) == false &&
               bulls_and_cows::is_win(game_options, ia_board) == false)
        {
            //Cr�ation d'un attempt et d'un feedback
            Code code_ia_attempt = pick_random_attempt(possible_solution);
            AttemptAndFeedback newattemp;
            newattemp.feedback = compare_attempt_with_secret_code(code_ia_attempt, ia_board.secret_code);
            newattemp.attempt = code_ia_attempt,

            //TEXT DISPLAY
            std::cout << "\n";
            for (unsigned a = 0; a < game_options.number_of_characters_per_code; a++)
            {
                std::cout  << "**";
            }
            std::cout << "***************************\n*";
            
            for (unsigned b = 0; b < game_options.number_of_characters_per_code; b++)
            {
                std::cout << " ";
            }
            std::cout << "The secret code is : " << ia_board.secret_code.value << "    *\n*";
            for (unsigned c = 0; c < game_options.number_of_characters_per_code; c++)
            {
                std::cout << " ";
            }
            std::cout << "The attempt is     : " << code_ia_attempt.value << "    *\n";
            //END TEXT DISPLAY


            ia_board.attempts_and_feedbacks.push_back(newattemp);
            display_board(std::cout, game_options, ia_board);
            remove_incompatible_codes_from_possible_solutions(newattemp,possible_solution);

            //Cr�ation d'un thread pour mieux voir les attempts de l'IA
            std::this_thread::sleep_for(std::chrono::seconds(1));

        }

        //LAST TEXT DISPLAY : Selon le r�sultat
        if (bulls_and_cows::is_win(game_options, ia_board)==true)
        {
            for (unsigned d = 0; d < game_options.number_of_characters_per_code; d++)
            {
                std::cout << " ";
            }
            std::cout << "What a smart IA ! \n";
        }
        else
        {
            for (unsigned d = 0; d < game_options.number_of_characters_per_code; d++)
            {
                std::cout << " ";
            }
            std::cout << "The IA may need an improvement :( ! \n";
        }
    }



    

    void configure_game_options(GameOptions& game_options)
    {
        std::ifstream in{"game_options.txt"};

        bool get_out = false;
        while (!get_out)
        {
            display_game_options(std::cout, game_options);
            display_game_options_menu(std::cout);
            std::cin.clear();
            const auto choice = ask_game_options_menu_choice(std::cin);

            switch (choice)
            {
            case GameOptionsMenuChoice::BackToMain:
                get_out = true;
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
