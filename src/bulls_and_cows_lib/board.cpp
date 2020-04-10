
#include "board.hpp"
#include "game.hpp"
#include <vector>

namespace bulls_and_cows {

    //Display the different components of the board
    void display_board(const Historic& historic, const GameOptions& game_options)
    {
        std::cout << "___________________________________________________________\n";
        std::cout << "| Attemps Nbr |      Attempt code      |  Bulls  |  Cows  |\n";
        std::cout << "-----------------------------------------------------------\n";
        
        //This loop display each attempt made by the player
        for (unsigned int i = 0; i < historic.value.size(); i++)
        {
            //Numbers of attempts
            std::cout << "| " << i + 1;
            //Managing the spaces on the array to make it good to see
            if (i+1 > 9)
            {
                std::cout << "          | ";
            }
            else
            {
                std::cout << "           | ";
            }

            //Display the attempts' codes
            std::cout << historic.value[i].attempt.value;
            //Adding spaces according to the length of the code, 23 is the number of spaces taking by the display at the top of the array
            for (int k = 0; k < 23 - historic.value[i].attempt.value.size(); k++)
            {
                std::cout << " ";
            }
            std::cout << "|  ";

            //Display the bulls
            std::cout << historic.value[i].bulls;
            if (historic.value[i].bulls > 9)
            {
                std::cout << "     ";
            }
            else
            {
                std::cout << "      ";
            }
            std::cout << "|  ";

            ///Display the cows
            std::cout << historic.value[i].cows;
            if (historic.value[i].cows > 9)
            {
                std::cout << "    ";
            }
            else
            {
                std::cout << "     ";
            }
            std::cout << "|\n";
        }
        std::cout << "___________________________________________________________\n";

        //Display the remaining attempts of the player
        std::cout << "Attempt(s) remaining:" << game_options.max_number_of_attempts - historic.value.size() << "\n";
    }

} // namespace bulls_and_cows
