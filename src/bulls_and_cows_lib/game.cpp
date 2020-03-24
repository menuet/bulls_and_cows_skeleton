
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

	/*Validation ask_SecretCodeChoice(std::istream& input_stream, Validation valid)
	{
		const char user_choice = ask_char_or_default(input_stream, -1);
		switch (user_choice)
		{
		case 'A':
			valid.carac = 'A';
			valid.SecretCodechoic;
			return valid;
		case 'B':
			return SecretCodeChoice::Valid;
		case 'C':
			return SecretCodeChoice::Valid;
		case 'D':
			return SecretCodeChoice::Valid;
		case 'E':
			return SecretCodeChoice::Valid;
		case 'F':
			return SecretCodeChoice::Valid;
		case 'G':
			return SecretCodeChoice::Valid;
		case 'H':
			return SecretCodeChoice::Valid;
			/*case 'I':
				return SecretCodeChoice::Valid;
			case 'J':
				return SecretCodeChoice::Valid;
			case 'K':
				return SecretCodeChoice::Valid;
			case 'L':
				return SecretCodeChoice::Valid;
			case 'M':
				return SecretCodeChoice::Valid;
			case 'N':
				return SecretCodeChoice::Valid;
			case 'O':
				return SecretCodeChoice::Valid;
			case 'P':
				return SecretCodeChoice::Valid;
			case 'Q':
				return SecretCodeChoice::Valid;
			case 'R':
				return SecretCodeChoice::Valid;
			case 'S':
				return SecretCodeChoice::Valid;
			case 'T':
				return SecretCodeChoice::Valid;
			case 'U':
				return SecretCodeChoice::Valid;
			case 'V':
				return SecretCodeChoice::Valid;
			case 'W':
				return SecretCodeChoice::Valid;
			case 'X':
				return SecretCodeChoice::Valid;
			case 'Y':
				return SecretCodeChoice::Valid;
			case 'Z':
				return SecretCodeChoice::Valid;
			}
			return SecretCodeChoice::Error;
		}
	}*/

	bool isContainedIn(char rand, const std::vector <char> secretCode)
	{
		bool is_found = false;
		for (const char c : secretCode)
		{
			if (rand == c)
			{
				is_found = true;
			}
		}
	
		return is_found;
	}


	OptionMenuChoice ask_option_menu_choice(std::istream& input_stream)
	{
		const int user_choice = ask_int_or_default(input_stream, -1);
		switch (user_choice)
		{
		case 0:
			return OptionMenuChoice::Quit;
		case 1:
			return OptionMenuChoice::NumberOfCharacters;
		case 2:
			return OptionMenuChoice::CharMin;
		case 3:
			return OptionMenuChoice::CharMax;
		}
		return OptionMenuChoice::Error;
	}

	// L'utilisation de Template est surement une notion utile pour eviter de repeter le meme code 
	ConfigureOptions ask_configuration_menu_choice(std::istream& input_stream)
	{
		const int user_choice = ask_int_or_default(input_stream, -1);
		switch (user_choice)
		{
		case 0:
			return ConfigureOptions::Quit;
		case 1:
			return ConfigureOptions::CurrentGameOptions;
		case 2:
			return ConfigureOptions::GameOptionMenu;
		
		}
		return ConfigureOptions::Error;
	}




	bool checkError(char carac, const GameOptions& game_options)
	{
		bool check = false;
		if (carac > game_options.maximum_allowed_character || carac < game_options.minimum_allowed_character)
		{
			std::cout << "Reselect a letter in the range \n";
			check = true;
		}

		return check;
	}



	// Algorithme standard à tester
	bool isContainedIn_V2(char characterToSearchFor, const std::vector<char> charactersToSearchIn)
	{
		const auto iter = std::find(charactersToSearchIn.begin(), charactersToSearchIn.end(), characterToSearchFor);
		return iter != charactersToSearchIn.end();
	}


	//Function to initialize secre code 
	std::vector<char> secret_code_init(std::vector <char> secretCode, const GameOptions& option)
	{

		
		const char min = option.minimum_allowed_character;
		const char max = option.maximum_allowed_character;
		char rand = generate_random_character(min, max);
		int l = 0;
		
		while (l < secretCode.size())
		{
			
			for (int i = 0; i < secretCode.size(); i++)
			{
				
				while (isContainedIn(rand, secretCode))
				{
					rand = generate_random_character(min, max);
					
				}
				
				secretCode[i] = rand;
			
			}
			l++;
		}
	
		return secretCode;
	}

	vector<char> secret_code_init_V2(vector<char> secretCode, const GameOptions& option)
	{
		
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

	void display_board(vector <FinalBoard>  board)
	{
		
		
		std::cout << "|";
		std::cout << "Attempts" <<"||";
		std::cout << "Code" <<" " << "||";
		std::cout << "Bulls" << "||";
		std::cout << "Cows" << "|";
		
		for (int i = 0; i < board.size(); i++) {
			std::cout << "\n";
			std::cout << "|";
			std::cout << "   " << i << "    " << "||";
			std::cout << " " << board[i].secretCode << "||";
			std::cout << "   " << board[i].bulls << "||";
			std::cout << "   " << board[i].cows << "|";
		}
	}

	std::vector<char> secret_code_player(std::vector <char> playerCode, const GameOptions& game_options)
	{
		std::istream& input_stream = std::cin;
		std::cout << "\n Give a secret code character by character \n";


		
		for (int i = 0; i < playerCode.size(); i++)
		{
			bool check = false;
			do {

				std::cout << "Letter  : ";
				playerCode[i] = ask_char_or_default(input_stream, 'O');
				check = checkError(playerCode[i], game_options);

			} while (check);


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

	string conv_vector_to_string(vector <char> vector_to_convert)
	{
		string chaine; 

		for (const char c : vector_to_convert)
		{
			chaine += c;
		}

		return chaine;
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
		secretCode = secret_code_init(secretCode, option);
		std::vector <char> playerCode(option.number_of_characters_per_code);
		std::vector<int> counter_bowls_cows(3);
		unsigned int player_attempts = 0;
		bool not_win = true;
		
		string secret_code_to_find = conv_vector_to_string(secretCode);

		cout << secret_code_to_find;
		
		
		vector <FinalBoard> board_final;
		board_final.push_back(FinalBoard(secret_code_to_find, 0, 0));


		do
		{

			playerCode = secret_code_player(playerCode, game_options);
			string secret_code_player = conv_vector_to_string(playerCode);
			counter_bowls_cows = count_true_false(secretCode, playerCode, counter_bowls_cows);
			board_final.emplace_back(secret_code_player, counter_bowls_cows[1], counter_bowls_cows[2]);
			player_attempts++;
			cout << "\n";
			display_board(board_final);

			if (counter_bowls_cows[1] == 5)
			{
				not_win = false;
			}


		} while (not_win && player_attempts < option.max_number_of_attempts);


		if (not_win == false)
		{
			cout << "\n" << "\n" << "YOU WIN !";
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


	void display_current_game_options(const GameOptions& game_options)
	{
		cout << "Game options : \n ";
		cout << " Number of characters per code : " << game_options.number_of_characters_per_code;
		cout << " \n Character min " << game_options.minimum_allowed_character;
		cout << "\n Character max " << game_options.maximum_allowed_character;

	}


	GameOptions change_Number_Characters(GameOptions& game_options)
	{
		
		cout << "How many characters do you want ? ";
		const unsigned int numberC = ask_int_or_default(std::cin, -1);
		game_options.number_of_characters_per_code = numberC;

		cout << "Updated ! \n";

		return game_options;
	}

	GameOptions change_Char_Min(GameOptions& game_options)
	{

		cout << "Which characters do you want to have as min character ? \n";
		const char char_min = ask_char_or_default(std::cin, -1);
		game_options.minimum_allowed_character = char_min;
		cout << "Updated ! \n";

		return game_options;
	}

	GameOptions change_Char_Max(GameOptions& game_options)
	{

		cout << "Which characters do you want to have as max character ? \n";
		const char char_max = ask_char_or_default(std::cin, -1);
		game_options.maximum_allowed_character = char_max;
		cout << "Updated ! \n";

		return game_options;
	}



	void  game_options_menu(GameOptions& game_options)
	{
		bool stay = true;
		
		
		do {

			cout << "\n Which game option do you want to change ? ";
			cout << "\n 1) Number of characters per code ? ";
			cout << " \n 2) Character min ? ";
			cout << "\n 3) Character max ? \n ";

			const auto user_choice = ask_option_menu_choice(std::cin);
			switch (user_choice)
			{
			case OptionMenuChoice::Quit:
				cout << "Exit \n";
				stay = false;
				return;
			case OptionMenuChoice::NumberOfCharacters:
				change_Number_Characters(game_options);
				break;
			case OptionMenuChoice::CharMin:
				change_Char_Min(game_options);
				break;
			case OptionMenuChoice::CharMax:
				change_Char_Max(game_options);
				break;
			case OptionMenuChoice::Error:
				std::cout << "\nYou did not enter a valid choice, please try again\n";
				break;
			}


		} while (stay);
		

			
	
	}



    void configure_game_options(GameOptions& game_options)
    {
		bool stay = true;
		do {

			std::cout << "\n TODO:\n"
				"    DO\n"
				"       Display the current game options\n"
				"       Display the game options menu\n"
				"       Ask the user to type its choice\n"
				"       Treat the user's choice\n"
				"    UNTIL user's choice is to go back to main menu\n";
			

			const auto user_choice = ask_configuration_menu_choice(std::cin);
			switch (user_choice)
			{
			case ConfigureOptions::Quit:
				cout << "Exit \n";
				stay = false;
				return;
			case ConfigureOptions::CurrentGameOptions:
				display_current_game_options(game_options);
				break;
			case ConfigureOptions::GameOptionMenu:
				game_options_menu(game_options);
				break;

			case  ConfigureOptions::Error:
				std::cout << "\nYou did not enter a valid choice, please try again\n";
				break;
			}
		} while (stay);
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
