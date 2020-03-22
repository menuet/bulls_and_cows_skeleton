#include "board.hpp"

namespace bulls_and_cows {

    void boardGame(std::vector<std::vector<char>>const& tableauFinal, const GameOptions& game_options, unsigned int count)
    {
        std::cout << "___________________________________________________________\n";
        std::cout << "| Attemps Nbr |      Attempt code      |  Bulls  |  Cows  |\n";

        for (int unsigned i = 1; i < tableauFinal.size(); i++)
        {
            std::cout << "| " << i;
            if (i > 9)
            {
                std::cout << "          | ";
            }
            else
            {
                std::cout << "           | ";
            }

            for (int unsigned j = 0; j < tableauFinal[i].size() - 2; j++)
            {
                std::cout << tableauFinal[i][j];
            }

            for (int unsigned k = 0; k < 25 - tableauFinal[i].size(); k++)
            {
                std::cout << " ";
            }
            std::cout << "|  ";

            std::cout << tableauFinal[i][tableauFinal[i].size()-2];
            std::cout << "      ";
            std::cout << "|  ";
            std::cout << tableauFinal[i][tableauFinal[i].size()-1];
            std::cout << "     ";
            std::cout << "|\n";
        }
        std::cout << "___________________________________________________________\n";

        std::cout << "Attempt(s) remaining:" << game_options.max_number_of_attempts - count << "\n";
    }


} // namespace bulls_and_cows
