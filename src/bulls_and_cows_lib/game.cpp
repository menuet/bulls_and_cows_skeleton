
#include "game.hpp"
#include "board.hpp"
#include "game_options.hpp"
#include "game_solver.hpp"
#include "input.hpp"
#include "main_menu.hpp"
#include <chrono>
#include <fstream>
#include <iostream>
#include <sstream>
#include <thread>
#include <windows.h>

using namespace std; // lifehack

namespace bulls_and_cows {

    void configure_game_options(GameOptions& game_options)
    {
        bool wantChange = true;
        while (wantChange)
        {
            display_game_options(cout, game_options);
            display_game_options_menu(cout);

            /*int choice;
            cin >> choice;*/
            GameOptionsMenuChoice choice = ask_game_options_menu_choice(cin);
            switch ((int)choice)
            {
            case 0:
                wantChange = false;
                break;
            case 1:
                cout << "valeur?" << endl;
                cin >> game_options.max_number_of_attempts;
                break;
            case 2:
                cout << "valeur?" << endl;
                cin >> game_options.number_of_characters_per_code;
                break;
            case 3:
                cout << "valeur?" << endl;
                cin >> game_options.minimum_allowed_character;
                break;
            case 4:
                cout << "valeur?" << endl;
                cin >> game_options.maximum_allowed_character;
                break;
            case 5:
                save_game_options(cout, game_options);
                break;
            case 6:
                load_game_options(cin, game_options);
                break;
            default:
                break;
            }

        }

        std::cout << "TODO:\n"
                     "    DO\n"
                     "       Display the current game options\n"
                     "       Display the game options menu\n"
                     "       Ask the user to type its choice\n"
                     "       Treat the user's choice\n"
                     "    UNTIL user's choice is to go back to main menu\n";
    }

    void user_plays_against_computer(const GameOptions& game_options)
    {
        /*
            Pseudo Code:


            Creer le board et les games_options
            Tant que le jeu n'est pas fini
                afficher l'état actuelle du BAILLE
                demander à l'U un attempt
                process l'attempt (en faire un feedback, l'ajouter au board etc...)
            Fin Tant que
            afficher l'état final (réussi ou perdu)
            ptit message sympa
        */

        Board board = create_board(game_options);
        std::cout << " le mot de passe est : " << board.secret_code.value << std::endl;
        while (!is_end_of_game(game_options, board))
        {
            display_board(std::cout, game_options, board); // bug
            Code codex = ask_attempt(std::cout, std::cin, game_options, board);
            Feedback feedback = compare_attempt_with_secret_code(codex, board.secret_code);
            AttemptAndFeedback aaf;
            aaf.attempt = codex;
            aaf.feedback = feedback;
            board.attempts_and_feedbacks.push_back(aaf);
        }
        display_board(std::cout, game_options, board);
        std::cout << "FINI" << std::endl;
        if (is_win(game_options, board))
        {
            std::cout << " bien joue, tu as gagne!" << std::endl;
        }
        else
        {
            std::cout << " dommage, tu as perdu! le bon code est : " << board.secret_code.value << std::endl;
        }
        std::cout << std::endl;
        std::cout << std::endl;
        std::cout << std::endl;
        std::cout << std::endl;
        std::cout << std::endl;
    }

    void computer_plays_against_computer(const GameOptions& game_options)
    {
        /*std::cout
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
        //   Initialisation de toute les combinaisons possible
        PossibleSolutions combination = generate_all_possible_codes(game_options);
        
        

        cout << " le mot de passe est : " << board.secret_code.value << std::endl;
        while (!is_end_of_game(game_options, board))
        {
            display_board(cout, game_options, board); 
            cout << " nombre de possibilités restante = " << combination.codes.size() << endl; // affichage du nombre de possibilitée restante
            Sleep(1000); //on atend 1s
            Code attempt = pick_random_attempt(combination); //on choisit un essai aléatoire
            Feedback feedback = compare_attempt_with_secret_code(attempt, board.secret_code); //on regarde le résultat
            AttemptAndFeedback aaf;
            aaf.attempt = attempt;
            aaf.feedback = feedback;
            board.attempts_and_feedbacks.push_back(aaf); //on ajoute le feedback au board
            remove_incompatible_codes_from_possible_solutions(aaf, combination); //Remove all the codes that are incompatible with the attempt's feedback from the list of possible codes
        }
        display_board(std::cout, game_options, board);
        std::cout << "FINI" << std::endl;
        if (is_win(game_options, board))
        {
            std::cout << " bien joue, l'ordi as gagne!" << std::endl;
        }
        else
        {
            std::cout << " dommage, l'ordi as perdu! le bon code est : " << board.secret_code.value << std::endl;
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
