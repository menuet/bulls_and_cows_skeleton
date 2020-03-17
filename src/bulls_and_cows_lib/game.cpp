
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

#include "random.hpp"
#include <vector>

namespace bulls_and_cows {

  void print_head(std::vector<AttemptAndFeedback> v)
    {
        int anssize = static_cast<int>(v.size());
        std::string espaces = "";
        std::string moins = "--------------------------";
        std::string etoiles = "";
        for (int j = 0; j < anssize; j++)
        {
            etoiles = etoiles + "* ";
            espaces = espaces + "  ";
            moins = moins + "--";
        }
        moins = moins + "\n";

        std::cout << moins << "| SECRET  " << etoiles << "|              |\n"
                  << moins << "| ATTEMPTS" << espaces << "| BULLS | COWS |"
                  << "\n"
                  << moins;
    }

  void print_body(const GameOptions& game_options, std::list<std::string> attempts, bool init)
  {
      if (init)
      {
          std::string defaultt = "";
          for (int i = 0; i < game_options.number_of_characters_per_code; i++)
          {
              defaultt += ". ";
          }

          for (std::string test : attempts)
          {
              test = defaultt;
          }
          init = false;
      }
  }

    void user_plays_against_computer(const GameOptions& game_options)
    {
        int indexans = 0;
        bool init = true;

        std::list<std::string> attempts(game_options.max_number_of_attempts);
        //CREATING BOARD
        Board myboard = bulls_and_cows::create_board(game_options);

        print_head(myboard.attempts_and_feedbacks);
        print_body(game_options, attempts, init);

        
//| SECRET   * * * * * |              |       
//-------------------------------------
//| ATTEMPTS           | BULLS | COWS |
//-------------------------------------
//| #12      . . . . . |       |      |
//| #11      . . . . . |       |      |
//| #10      . . . . . |       |      |
//| #09      . . . . . |       |      |
//| #08      . . . . . |       |      |
//| #07      . . . . . |       |      |
//| #06      . . . . . |       |      |
//| #05      . . . . . |       |      |
//| #04      . . . . . |       |      |
//| #03      . . . . . |       |      |
//| #02      . . . . . |       |      |
//| #01      . . . . . |       |      |
//-------------------------------------

        std::cout <<"\n" <<"TODO:\n"
                     "    Create a board with a randomly generated secret code DONE\n"
                     "    DO\n"
                     "       Display the board and the list of attempts so far\n"
                     "       Ask the user to make another attempt\n"
                     "       Compare the user's attempt with the secret code and deduce the number of bulls and cows\n"
                     "       Add the user's attempt to the list of attempts of the board\n"
                     "    WHILE not end of game\n"
                     "    Display the board and the list of attempts so far\n"
                     "    Display a message telling if the user won or lost\n";
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
