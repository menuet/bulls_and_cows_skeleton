#include "game_options.hpp"
#include "game.hpp"
#include <fstream>


namespace bulls_and_cows {

	void printOptions(GameOptions& game_options)
    {
        std::cout << "Caractère min : " << game_options.minimum_allowed_character << "\n";
        std::cout << "Caractère max : " << game_options.maximum_allowed_character << "\n";
        std::cout << "Nbr caractère par code : " << game_options.number_of_characters_per_code << "\n";
        std::cout << "Nbr attemps : " << game_options.max_number_of_attempts << "\n";
        std::cout << "Save Game : " << game_options.save_game << "\n";
        std::cout << "Doublons acceptés : " << game_options.accept_doublons << "\n";
    }

    GameOptions modifOptions(GameOptions gameoption1)
    {
        std::cout << "Caractère min : ";
        std::cin >> gameoption1.minimum_allowed_character;

        std::cout << "Caractère max : ";
        std::cin >> gameoption1.maximum_allowed_character;

        std::cout << "Nbr caractère par code : ";
        std::cin >> gameoption1.number_of_characters_per_code;

        std::cout << "Nbr attemps : ";
        std::cin >> gameoption1.max_number_of_attempts;

        char choice(0);
        std::cout << "Save Game (T / F) : ";
        std::cin >> choice;
        if (choice == 'T')
            gameoption1.save_game = true;
        else
            gameoption1.save_game = false;

        choice = 0;
        std::cout << "Doublons acceptés (T / F) : ";
        std::cin >> choice;
        if (choice == 'T')
            gameoption1.accept_doublons = true;
        else
            gameoption1.accept_doublons = false;
        
        return gameoption1;
    }

    /*void saveGameMethod(std::vector<FinalBoard> const& finalBoard, unsigned int const& win)
    {
        constexpr unsigned int number_of_chars_taken_by_the_size_of_a_coloum = 20U;

        std::string const fichier = "C:/C++/PROJECTS/bulls_and_cows_skeleton/save.txt";
        std::ofstream monFlux(fichier);

        if (monFlux)
        {
            monFlux << "___________________________________________________________\n";
            monFlux << "| Attemps Nbr |      Attempt code      |  Bulls  |  Cows  |\n";

            for (int unsigned i = 1; i < finalBoard.size(); i++)
            {
                monFlux << "| " << i;
                if (i > 9)
                {
                    monFlux << "          | ";
                }
                else
                {
                    monFlux << "           | ";
                }

                monFlux << finalBoard[i].secretCode;

                for (int unsigned k = 0; k < number_of_chars_taken_by_the_size_of_a_coloum - finalBoard.size(); k++)
                {
                    monFlux << " ";
                }
                monFlux << "|  ";

                monFlux << finalBoard[i].bulls;
                monFlux << "      ";
                monFlux << "|  ";
                monFlux << finalBoard[i].cows;
                monFlux << "     ";
                monFlux << "|\n";
            }
            monFlux << "___________________________________________________________\n";

            if (win  == 2)
            {
                monFlux << "You lose ! ";
            }
            else
                monFlux << "You win ! ";
        }
        else
            std::cout << "Erreur, imposible d'ouvrir le fichier";
    }*/

} // namespace bulls_and_cows
