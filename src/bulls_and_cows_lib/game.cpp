
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
// tyefgkzjdfjenzdjisdlkckzsdnkjcnkdsjnckodsnkosklnkjbjknbkjbj,bjksdmlf,sdkl,fklds,SDCSDCSDCDCDS

namespace bulls_and_cows {
// test
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

        

        // créer une chaine de caractère de 10 lettres aux hasards

        using namespace std;
        char tt[27]; // créer un tableau de chaque lettre

         // crÃ©er une chaine de caractÃ¨re de 10 lettres aux hasards
        tt[0] = 'A';
        tt[1] = 'B';
        tt[2] = 'C';
        tt[3] = 'D';
        tt[4] = 'E';
        tt[5] = 'F';
        tt[6] = 'G';
        tt[7] = 'H';
        tt[8] = 'I';
        tt[9] = 'J';
        tt[10] = 'K';
        tt[11] = 'L';
        tt[12] = 'M';
        tt[13] = 'N';
        tt[14] = 'O';
        tt[15] = 'P';
        tt[16] = 'Q';
        tt[17] = 'R';
        tt[18] = 'S';
        tt[19] = 'T';
        tt[20] = 'U';

        tt[21] = 'V';
        tt[22] = 'W';
        tt[23] = 'X';
        tt[24] = 'Y';
        tt[25] = 'Z';

        char tableauCacher[10];

        for (int i = 0; i < 10; i++) 
        {     
    
            int z = 0;        // initialise un nombre z

            z = (rand()%25); // prendre un nombre z aléatoirement compris entre 1-26

            z = (rand()%25); // prendre un nombre z alÃ©atoirement compris entre 1-26

            // cout << tt[z]; // pour chaque chiffre que prendra z on aura une lettre du tableau cout << tt[z]
            tableauCacher[i] = tt[z];
            //cout << tableauCacher[i];       
        }

        // fonction permettant de compter le nombre de pion bien et mal placé (compteur1 et 2 pacé par reference)

        // si une case de ces deux tableaux passe à vrai, alors elle permettent de ne plus revenir dessus (utilisé pour
        // les éléments deja compté)
        bool tabCacherValide[10]; 
        bool tabChoixValide[10];
        int tabChoix[10];
        int compteur1 = 0; // compteur de pions bien placer

        // compte ne nombre d'éléments bien placé
        for (int i = 0; i < 10; i++)
        {
            if (tableauCacher[i] == tabChoix[i])
            {
                tabChoixValide[i] = true;
                tabCacherValide[i] = true;
                compteur1++;
            }
            else
            {
                tabChoixValide[i] = false;
                tabCacherValide[i] = false;
            }
        }


       // printf("entrer vos valeurs");
        //scanf();
        //char TableauTemp[10];
        //for ( )

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
