#include "board.hpp"
#include "game.hpp"

namespace bulls_and_cows {

    //La methode boardGame permet d'afficher en console le jeu, si l'utilisateur veut save sa partie, elle permet aussi del'enregistrer dans un save.txt.
    void boardGame(std::vector<FinalBoard> const& finalBoards, const GameOptions& game_options,
                   std::ostream& output_stream)
    {
        constexpr unsigned int number_of_chars_taken_by_the_size_of_a_coloum = 18U;

        output_stream << "___________________________________________________________\n";
        output_stream << "| Attemps Nbr |      Attempt code      |  Bulls  |  Cows  |\n";

        for (unsigned int i = 1; i < finalBoards.size(); i++)
        {
            output_stream << "| " << i;
            if (i > 9)
            {
                output_stream << "          | ";
            }
            else
            {
                output_stream << "           | ";
            }

            output_stream << finalBoards[i].secretCodeUser;

            for (int unsigned k = 0; k < number_of_chars_taken_by_the_size_of_a_coloum; k++)
            {
                output_stream << " ";
            }
            output_stream << "|  ";

            output_stream << finalBoards[i].bulls;
            output_stream << "      ";
            output_stream << "|  ";
            output_stream << finalBoards[i].cows;
            output_stream << "     ";
            output_stream << "|\n";
        }
        output_stream << "___________________________________________________________\n";

        output_stream << "Attempt(s) remaining:" << game_options.max_number_of_attempts - finalBoards.size()+1 << "\n";
    }

} // namespace bulls_and_cows