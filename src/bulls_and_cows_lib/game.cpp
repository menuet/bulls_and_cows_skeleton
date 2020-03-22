
#include "game.hpp"
#include "board.hpp"
#include "game_options.hpp"
#include "game_solver.hpp"
#include "input.hpp"
#include "main_menu.hpp"
#include "random.hpp"
#include <vector> 
#include <chrono>
#include <fstream>
#include <iostream>
#include <thread>
using namespace std;
namespace bulls_and_cows {

	int distinct(char rand, std::vector <char> secretCode)
	{
		int vrai = 0;
		for (int i = 0; i < secretCode.size(); i++)
		{
			if (rand == secretCode[i])
			{
				vrai = 1;
			}
		}
	
		return vrai;
	}

	
	std::vector<char> secret_code_init(std::vector <char> secretCode)
	{

		GameOptions option;
		char min = option.minimum_allowed_character;
		char max = option.maximum_allowed_character;
		char rand = generate_random_character(min, max);
		int l = 0;
		
		while (l < secretCode.size())
		{
			
			for (int i = 0; i < secretCode.size(); i++)
			{
				
				while (distinct(rand, secretCode) == 1)
				{
					rand = generate_random_character(min, max);
					distinct(rand, secretCode);
					
				}
				
				secretCode[i] = rand;
			
			}
			
			std::cout << secretCode[l];
			l++;
		}
	
		return secretCode;
	}

	vector<char> secret_code_init_V2(vector<char> secretCode)
	{
		
		GameOptions option;
		char min = option.minimum_allowed_character;
		char max = option.maximum_allowed_character;
		char rand;

		for (int i = 0; i < secretCode.size(); i++)
		{
			rand = generate_random_character(min, max);
			while (rand == secretCode[0] || rand == secretCode[1] || rand == secretCode[2] || rand == secretCode[3] || rand == secretCode[4])
			{
				rand = generate_random_character(min, max);
			}
			secretCode[i] = rand;
		}

		for (int z = 0; z<secretCode.size(); z++)
		{
			cout << secretCode[z];
		}

		return secretCode;

	}

	void display_board(std::vector <std::vector <std::string>> board)
	{
		for (int i = 0; i < board.size(); i++) {
			std::cout << "\n";
			for (int j = 0; j < board[i].size(); j++)
				std::cout << board[i][j] << " ";

		}
	}

	std::vector<char> secret_code_player(std::vector <char> playerCode)
	{
		std::istream& input_stream = std::cin;
		std::cout << "\n Give a secret code character by character \n";

		for (int i = 0; i < playerCode.size(); i++)
		{
			std::cout << "Letter  : ";
			playerCode[i] = ask_char_or_default(input_stream, 'O');


		}

		for (int i = 0; i < playerCode.size(); i++)
		{

			std::cout << playerCode[i];

		}

		return playerCode;

	}

	std::vector<int> count_true_false(std::vector <char> secretCode, std::vector <char> playerCode, std::vector<int> counter_bulls_cows)
	{
		int bulls = 0;
		int cows = 0; 

		for (int i = 0; i<playerCode.size(); i++)
		{
			if (secretCode[i] == playerCode[i])
			{
				bulls = bulls + 1; 
			}
			
			for (int j = 0; j < playerCode.size(); j++)
			{
				
				if (secretCode[j] == playerCode[i])
				{
					cows = cows + 1; 
				}
			}
			
		}
		
		if (bulls == secretCode.size())
		{
			counter_bulls_cows[0] = 1;
		}
		else
		{
			counter_bulls_cows[0] = 0;
		}

		cows = cows - bulls;
		counter_bulls_cows[1] = bulls;
		counter_bulls_cows[2] = cows;

		return counter_bulls_cows;

	}

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


		GameOptions option;
		std::vector <char> secretCode(option.number_of_characters_per_code);
		secretCode = secret_code_init_V2(secretCode);
		std::vector <std::vector <std::string>> board{ {"--","-------", "---" ,"----", "---" ,"-----", "--", "--", ""}, {"|","Attempts", "||" ,"Code", "||" ,"Bulls", "||", "Cows", "|"}, {"|","  1    ", "||" ,"    ", "||" ,"     ","||", "    ","|"}, {"|","  2    ", "||" ,"    ", "||" ,"     ","||", "    ","|"}, {"|","  3    ", "||" ,"    ", "||" ,"     ","||", "    ","|"}, {"|","  4    ", "||" ,"    ", "||" ,"     ","||", "    ","|"}, {"|","  5    ", "||" ,"    ", "||" ,"     ","||", "    ","|"}, {"|","  6    ", "||" ,"    ", "||" ,"     ","||", "    ","|"}, {"|","  7    ", "||" ,"    ", "||" ,"     ","||", "    ","|"}, {"|","  8    ", "||" ,"    ", "||" ,"     ","||", "    ","|"}, {"|","  9    ", "||" ,"    ", "||" ,"     ","||", "    ","|"} , {"|","  10   ", "||" ,"    ", "||" ,"     ","||", "    ","|"}, {"|","  11   ", "||" ,"    ", "||" ,"     ","||", "    ","|"}, {"|","  12   ", "||" ,"    ", "||" ,"     ","||", "    ","|"}, {" --","-------", "---" ,"----", "---" ,"-----", "--", "--", "" } };
		std::vector <char> playerCode(option.number_of_characters_per_code);
		std::vector<int> counter_bowls_cows(3);
		//std::vector <std::vector <std::string>> board{ {"--","-------", "---" ,"----", "---" ,"-----", "--", "--", ""}, {"|","Attempts", "||" ,"Code", "||" ,"Bulls", "||", "Cows", "|"}};
		
		unsigned int player_attempts = 0;
		int line_table = 0;
		int win = 0;
		
		
		display_board(board);
	
		
		while (player_attempts < option.max_number_of_attempts && win != 1)
		{
			string concat;
			line_table = player_attempts+2;
			playerCode = secret_code_player(playerCode);
			counter_bowls_cows = count_true_false(secretCode, playerCode, counter_bowls_cows);
			//display_board(board);
			concat += playerCode[0];
			concat += playerCode[1];
			concat += playerCode[2];
			concat += playerCode[3];
			concat += playerCode[4];
			//board.push_back({ concat,to_string(counter_bowls_cows[2]),to_string(counter_bowls_cows[3]) });
			board[line_table][3] = concat;
			board[line_table][5] = to_string(counter_bowls_cows[1]);
			board[line_table][7] = to_string(counter_bowls_cows[2]);
			display_board(board);

			if (counter_bowls_cows[1] == 5)
			{
				win = 1;
			}

			player_attempts = player_attempts + 1;

		}

		if (win == 1)
		{
			cout<< "YOU WIN !";
		}
		
		else
		{
			cout << "YOU LOOSE ! ";
		}
		

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
