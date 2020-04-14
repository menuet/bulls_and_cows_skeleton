
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
        std::cout << "TODO:\n"
                     "    Create a board with a randomly generated secret code\n"
                     "    DO\n"
                     "       Display the board and the list of attempts so far\n"
                     "       Ask the user to make another attempt\n"
                     "       Compare the user's attempt with the secret code and deduce the number of bulls and cows\n"
                     "        attempt to theAdd the user's list of attempts of the board\n"
                     "    WHILE not end of game\n"
                     "    Display the board and the list of attempts so far\n"
                     "    Display a message telling if the user won or lost\n";


        Board board = create_board(game_options);

         AttemptAndFeedback attempt_and_feedback;
         do
         {
             //Display the board and the list of attempts so far
             display_board(std::cout, game_options, board);

            //Ask the user to make another attempt
             attempt_and_feedback.attempt = ask_attempt(std::cout, std::cin, game_options, board);

            //Compare the user's attempt with the secret code and deduce the number of bulls and cows
             attempt_and_feedback.feedback =
                 compare_attempt_with_secret_code(board.secret_code, attempt_and_feedback.attempt);

            // attempt to theAdd the user's list of attempts of the board
             board.attempts_and_feedbacks.push_back(attempt_and_feedback);

         } while (!is_end_of_game(game_options, board) && !is_win(game_options, board));
        
        //Display the board and the list of attempts so far
         display_board(std::cout, game_options, board);

        //Display a message telling if the user won or lost
         if (is_win(game_options, board))
         {
             std::cout << "You are the winner" << std::endl;
         }

         else
         {
             std::cout << "You are a loser" << std::endl;
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

        std::string path = "./save.txt";
         std::ofstream save_file;
         std::ifstream load_file;
         GameOptionsMenuChoice gomc;
         do
         {
             //Display the current game options
             std::cout << "\n#################################\n";
             display_game_options(std::cout, game_options);

            //Display the game options menu
             std::cout << "\n#################################\n";
             display_game_options_menu(std::cout);
            
            //Ask the user to type its choice
             GameOptionsMenuChoice c = ask_game_options_menu_choice(std::cin);
             gomc = c;
            
             switch (c)
             {

             case GameOptionsMenuChoice ::Error:
                 std::cout << "\nyour choice is not valid, put an other choice\n";
                 break;

             case GameOptionsMenuChoice::ModifyMaximumNumberOfAttempts:
                 std::cout << "\nenter the maximum number of attempts :";
                 game_options.max_number_of_attempts = ask_int_or_default(std::cin, game_options.max_number_of_attempts);
                 break;

             case GameOptionsMenuChoice::ModifyNumberOfCharactersPerCode:
                 std::cout << "\nenter the number of character per code :";
                 game_options.number_of_characters_per_code =
                     ask_int_or_default(std::cin, game_options.number_of_characters_per_code);
                 break;

             case GameOptionsMenuChoice::ModifyMinimumAllowedCharacter:
                 std::cout << "\nenter the minimum of allowed character :";
                 char min;
                 min = ask_char_or_default(std::cin, game_options.minimum_allowed_character);
                 if (min >= game_options.maximum_allowed_character)
                 {
                     std::cout << "minimum character is never superior to maximum character";
                 }
                 else
                     game_options.minimum_allowed_character = min;
                 break;

             case GameOptionsMenuChoice::ModifyMaximumAllowedCharacter:
                 std::cout << "\nenter the maximum of allowed character :";
                 char max;
                 max = ask_char_or_default(std::cin, game_options.maximum_allowed_character);
                 if (max <= game_options.minimum_allowed_character)
                 {
                     std::cout << "maximum character is never inferior to minimum character";
                 }
                 else
                     game_options.maximum_allowed_character = max;
                 break;

             case GameOptionsMenuChoice::SaveOptions:
                 save_file.open(path);
                 if (!save_game_options(save_file, game_options))
                 {
                     std::cout << "writing error";
                 }
                 save_file.close();
                 break;

             case GameOptionsMenuChoice::LoadOptions:
                //on place le curseur en premiere position (beg)
                 load_file.seekg(0, std::ios::beg);
                 if (!load_game_options(load_file, game_options))
                 {
                     std::cout << "reading error";
                 }
                 break;
            
             }
          
         } 
         while (gomc != GameOptionsMenuChoice::BackToMain);
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
