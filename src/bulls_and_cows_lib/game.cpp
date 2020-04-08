
#include "game.hpp"
#include "board.hpp"
#include "game_options.hpp"
#include "game_solver.hpp"
#include "input.hpp"
#include "main_menu.hpp"
#include <chrono>
#include <fstream> //flux vers les fichiers
#include <iostream> //flux entrées/sorties
#include <thread>
using namespace std;

namespace bulls_and_cows {

    void user_plays_against_computer(const GameOptions& game_options)
    {
       
        Board gameboard = bulls_and_cows::create_board(game_options); //Create the board
        while (!is_end_of_game(game_options, gameboard))//As long as the player the game isn't over
        {
            bulls_and_cows::display_board(cout, game_options, gameboard);
            Code result = ask_attempt(cout, cin, game_options, gameboard);// Ask the user's attempt/test
            Feedback f = compare_attempt_with_secret_code(result, gameboard.secret_code);// Compare with the random secret code 
            AttemptAndFeedback a;
            a.attempt = result;
            a.feedback = f;
            gameboard.attempts_and_feedbacks.push_back(a);// insert the value into the vector at the end
          
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
        /*std::cout << "TODO:\n"
                     "    DO\n"
                     "       Display the current game options\n"
                     "       Display the game options menu\n"
                     "       Ask the user to type its choice\n"
                     "       Treat the user's choice\n"
                     "    UNTIL user's choice is to go back to main menu\n";*/
        
        bool flag = false;
        while (!flag)
        {

            display_game_options(cout, game_options);
            display_game_options_menu(cout);
            GameOptionsMenuChoice user_choice = ask_game_options_menu_choice(cin);
            switch ((int)user_choice) // require int type
            {
            case 0:
                flag = true;
                break;
            case 1:

               {
                    cout << "Modify the max number attempt\n";
                    game_options.max_number_of_attempts = ask_int_or_default(cin, game_options.max_number_of_attempts);
                   
                    /*unsigned int modif = ask_int_or_default(cin, game_options.max_number_of_attempts);
                    while (modif < game_options.max_number_of_attempts)
                    {
                        modif = game_options.max_number_of_attempts;
                    }*/
               }
                break;

            case 2:
            {
                    cout << "Modify the number of characters \n";
                    game_options.number_of_characters_per_code = ask_int_or_default(cin, game_options.number_of_characters_per_code);
                  
            }

                break;

            case 3: 
            {
                    cout << "Modify the minimum letter";
                    game_options.minimum_allowed_character = ask_char_or_default(cin, game_options.minimum_allowed_character);
                
            }
            break;

            case 4: 
            {
                    cout << "Modify max allowed \n";
                    game_options.maximum_allowed_character = ask_char_or_default(cin, game_options.maximum_allowed_character);
                
            }
                break;
            case 5: 
            {
                
                //ofstream fileout_stream{"C:/DEVCPP/PROJECTS/bulls_and_cows_skeleton/game_option_save.txt"};
                string const myfile("game_option.txt");
                ofstream fileout_stream(myfile.c_str(), ios::app);// display a string so it's better to use c_str()
                save_game_options(fileout_stream, game_options);
                
            }
                break;
            case 6: {
                ifstream filein_stream{"game_option.txt"};
                load_game_options(filein_stream, game_options);
                break;
            }
            default:
                    cout << " invalid entry " << endl;
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
