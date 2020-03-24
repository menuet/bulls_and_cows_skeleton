
#include "board.hpp"

namespace bulls_and_cows {

    // TODO: define the body of the functions declared in board.cpp

    void display_board(const GameOptions& game_options, Board Board)
    {
        //En tete
        //1er ligne;
        std::cout << "-----------";
            for ( unsigned int i = 0; i < game_options.number_of_characters_per_code; i++)
        {
            std::cout << "--";
        }
        std::cout << "-----------------\n";
        //2e ligne                      /!\ a changer pour afficher si réussi /!\ 
        std::cout << "| SECRET   ";
        for (unsigned int i = 0; i < game_options.number_of_characters_per_code; i++)
        {
            std::cout << " *";
        }
        std::cout << " |              |\n";
        //3e ligne
        std::cout << "-----------";
        for (unsigned int i = 0; i < game_options.number_of_characters_per_code; i++)
        {
            std::cout << "--";
        }
        std::cout << "-----------------\n";
        //4e ligne
        std::cout << "| ATTEMPTS ";
        for (unsigned int i = 0; i < game_options.number_of_characters_per_code; i++)
        {
            std::cout << "  ";
        }
        std::cout << " | BULLS | COWS |\n";
        //5e ligne
        std::cout << "-----------";
        for (unsigned int i = 0; i < game_options.number_of_characters_per_code; i++)
        {
            std::cout << "--";
        }
        std::cout << "-----------------\n";
        
            //Lignes evoluant en fonction du nombre d'essais
        for (int i = game_options.max_number_of_attempts ; i > 0; i--)
        {
            std::cout << "| #" << i << "      ";
            if (i < 10) // decalage pour compenser la perte du chiffre des dizaines
            {
                std::cout << " ";
            }
            //affichage d'un essai realise 
            if (Board.attempts_and_feedbacks.size() >= i)
            {
                for (unsigned int j = 0; j < game_options.number_of_characters_per_code; j++)
                {
                    std::cout << " " << Board.attempts_and_feedbacks[i-1].attempt.value[j];
                }
                std::cout << " |   " << Board.attempts_and_feedbacks[i-1].feedback.bulls 
                          << "   |   " << Board.attempts_and_feedbacks[i-1].feedback.cows << "  |\n";
            }
            //cas ou l'essai n'a pas encore ete fait
            else
            {
                for (unsigned int j = 0; j < game_options.number_of_characters_per_code; j++)
                {
                    std::cout << " .";
                }
                std::cout << " |       |      |\n";
            }

        }
        //Bas de page
        std::cout << "-----------";
        for (unsigned int i = 0; i < game_options.number_of_characters_per_code; i++)
        {
            std::cout << "--";
        }
        std::cout << "-----------------\n";


    }

} // namespace bulls_and_cows
