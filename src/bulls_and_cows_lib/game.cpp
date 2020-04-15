
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

namespace bulls_and_cows 
{

    void user_plays_against_computer(const GameOptions& game_options)
    {
           std::cout << "TODO:\n"
                     "    Create a board with a randomly generated secret code\n"
                     "    DO\n"
                     "       Display the board and the list of attempts so far\n"
                     "       Ask the user to make another attempt\n"
                     "       Compare the user's attempt with the secret code and deduce the number of bulls and cows\n"
                     "       Add the user's attempt to the list of attempts of the board\n"
                     "    WHILE not end of game\n"
                     "    Display the board and the list of attempts so far\n"
                     "    Display a message telling if the user won or lost\n";
        Board board{};
        AttemptAndFeedback feedback{};

        board = create_board(game_options);

        do
        {
            std::cout << "\n";
            display_board(std::cout, game_options, board);

            feedback.attempt = ask_attempt(std::cout, std::cin, game_options, board);

            while (!validate_attempt(game_options,feedback.attempt))
            {
                std::cout << "Your attempt is not valid, try again\n";
                feedback.attempt = ask_attempt(std::cout, std::cin, game_options, board);
            }

            feedback.feedback = compare_attempt_with_secret_code(feedback.attempt, board.secret_code);

            board.attempts_and_feedbacks.push_back(feedback);
        } while (!(is_end_of_game(game_options, board)) && !(is_win(game_options, board)));

        
        std::cout << "\n";
        display_board(std::cout, game_options, board);

        if (is_win(game_options, board))
        {
            std::cout << "\n"
                      << "You won !the hidden code was: " << board.secret_code.value << "\n";
        }

        else
        {
            std::cout << "\n"
                      << "You've lost, the hidden code was: " << board.secret_code.value << "\n";
        }
        }
    void computer_plays_against_computer(const GameOptions& game_options)
    {
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
    
       // GameOptions game_options{};
       
       //Les std::cin vont aller chercher les entrées au clavier par l'utilisateur pour définir le:
       //nombre de maximum de tentatives , de caractères...
       
        std::cout << "Type a number of attempts: "; 
        std::cin >> game_options.max_number_of_attempts;
       
        std::cout << "Type a number of characters: "; 
        std::cin >> game_options.number_of_characters_per_code; 

        std::cout << "Type the minimum allowed character: "; 
        std::cin >> game_options.minimum_allowed_character; 

        std::cout << "Type the maximum allowed character "; 
        std::cin >> game_options.maximum_allowed_character; 

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
