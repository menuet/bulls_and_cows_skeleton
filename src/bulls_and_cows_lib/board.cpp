#include "board.hpp"
#include "game.hpp"

namespace bulls_and_cows {


    void boardGame(std::vector<FinalBoard> const& finalBoard, const GameOptions& game_options, unsigned int const& count)
    {
        // constexpr unsigned int number_of_chars_taken_by_the_size_of_a_coloum = 18U;

        std::cout << "___________________________________________________________\n";
        std::cout << "| Attemps Nbr |      Attempt code      |  Bulls  |  Cows  |\n";

        for (unsigned int i = 1; i < finalBoard.size(); i++)
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

            std::cout << finalBoard[i].secretCode;

            for (int unsigned k = 0; k < 18U; k++)
            {
                std::cout << " ";
            }
            std::cout << "|  ";

            std::cout << finalBoard[i].bulls;
            std::cout << "      ";
            std::cout << "|  ";
            std::cout << finalBoard[i].cows;
            std::cout << "     ";
            std::cout << "|\n";
        }
        std::cout << "___________________________________________________________\n";

        std::cout << "Attempt(s) remaining:" << game_options.max_number_of_attempts - count << "\n";
    }

} // namespace bulls_and_cows