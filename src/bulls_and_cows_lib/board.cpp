
#include "board.hpp"
#include <vector>

using namespace std;

namespace bulls_and_cows {

    //Display the different components of the board
    void display_board(vector<vector<char>> const& attempt_historic, vector<int> const& bulls_historic,
                       vector<int> const& cows_historic,
                       unsigned int cpt_attempt, const GameOptions& game_options)
    {
        cout << "___________________________________________________________\n";
        cout << "| Attemps Nbr |      Attempt code      |  Bulls  |  Cows  |\n";
        
        //This loop display each attempt made by the player
        for (unsigned int i = 0; i < cpt_attempt; i++)
        {
            //Numbers of attempts
            cout << "| " << i+1;
            //Managing the spaces on the array to make it good to see
            if (i+1 > 9)
            {
                cout << "          | ";
            }
            else
            {
                cout << "           | ";
            }

            //Display the attempts' codes
            print_vector_char(attempt_historic[i]);
            for (int k = 0; k < 23 - attempt_historic[i].size(); k++)
            {
                cout << " ";
            }
            cout << "|  ";

            //Display the bulls
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

            ///Display the cows
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

        //Display the remaining attempts of the player
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
