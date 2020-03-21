
#include "board.hpp"
#include <vector>

using namespace std;

namespace bulls_and_cows {

    void display_board(vector<vector<char>> attempt_historic, vector<int> bulls_historic, vector<int> cows_historic,
                       unsigned int cpt_attempt, const GameOptions& game_options)
    {
        cout << "___________________________________________________________\n";
        cout << "| Attemps Nbr |      Attempt code      |  Bulls  |  Cows  |\n";
        for (unsigned int i = 0; i < cpt_attempt; i++)
        {
            cout << "| " << i;
            if (cpt_attempt > 9)
            {
                cout << "          | ";
            }
            else
            {
                cout << "           | ";
            }

            print_vector_char(attempt_historic[i]);
            for (int k = 0; k < 23 - attempt_historic[i].size(); k++)
            {
                cout << " ";
            }
            cout << "|  ";
            cout << bulls_historic[i];
            if (bulls_historic[i] > 9)
            {
                cout << "     ";
            }
            else
            {
                cout << "      ";
            }
            cout << "|  ";
            cout << cows_historic[i];
            if (bulls_historic[i] > 9)
            {
                cout << "    ";
            }
            else
            {
                cout << "     ";
            }
            cout << "|\n";
        }
        cout << "___________________________________________________________\n";

        cout << "Attempt(s) remaining:" << game_options.max_number_of_attempts - cpt_attempt << "\n";
    }

    // Display a vector of char
    void print_vector_char(vector<char> const& vector)
    {
        for (int i = 0; i < vector.size(); i++)
        {
            cout << vector[i];
        }
    }

} // namespace bulls_and_cows
