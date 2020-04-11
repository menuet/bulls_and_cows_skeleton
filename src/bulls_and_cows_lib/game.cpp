
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
#include <stdexcept>


namespace bulls_and_cows {

	
	//fonction qui permet de savoir si un char est deja present dans le vector de char 
	bool isContainedIn(char rand, const std::vector <char>& secretCode)
	{
		bool is_found = false;
		for (const char c : secretCode) // on parcourt le vector de char 
		{
			if (rand == c) // si le char est deja present
			{
				is_found = true; // bool devient true
				break;
			}
		}
	
		return is_found; // renvoit un bool 
	}

	// choix pour le menu des options return un choix present dans l'Enum OptionMenuChoice
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
		case 3: 
			return ConfigureOptions::SaveOption;
		case 4:
			return ConfigureOptions::ReadOption;
		case 5:
			return ConfigureOptions::LoadOption;
		
		}
		return ConfigureOptions::Error;
	}

	// Check les users inputs 
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

	// Algorithme standard à tester, pas encore utilisé
	bool isContainedIn_V2(char characterToSearchFor, const std::vector<char>& charactersToSearchIn)
	{
		const auto iter = std::find(charactersToSearchIn.begin(), charactersToSearchIn.end(), characterToSearchFor);
		return iter != charactersToSearchIn.end();
	}


	//Function to initialize secret code 
	std::string secret_code_init_without_double(const GameOptions& option)
	{

		std::vector <char> secretCode(option.number_of_characters_per_code);
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
		std::string secret_code = conv_vector_to_string(secretCode);
		return secret_code;
	}

	std::string secret_code_init_with_double(const GameOptions& option)
	{
		std::string secretCode;
		const char min = option.minimum_allowed_character;
		const char max = option.maximum_allowed_character;
		char rand = generate_random_character(min, max);
		unsigned int l = 0;

		while (l < option.number_of_characters_per_code)
		{
			rand = generate_random_character(min, max);
			secretCode += rand;
			l++;
		}

		return secretCode;
	}

	//fonction qui affiche le tableau d'affichage 
	void display_board(std::vector <FinalBoard>  board)
	{
		
		std::cout << "------------------------------\n";
		std::cout << "|";
		std::cout << "Attempts" <<"||";
		std::cout << "Code" <<" " << "||";
		std::cout << "Bulls" << "||";
		std::cout << "Cows" << "|";

		std::cout << "\n";
		std::cout << "|";
		std::cout << " Secret " << "||";
		std::cout << " " << board[0].secretCode << "||";
		std::cout << "   " << board[0].bulls << "||";
		std::cout << "   " << board[0].cows << "|";
		
		for (int i = 1; i < board.size(); i++) {
			std::cout << "\n";
			std::cout << "|";
			std::cout << "   " << i << "    " << "||";
			std::cout << " " << board[i].secretCode << "||";
			std::cout << "   " << board[i].bulls << "||";
			std::cout << "   " << board[i].cows << "|";
		}

		std::cout << "\n------------------------------\n";
	}

	//fonction qui permet de retourner le code secret qu'a input l'utilisateur
	std::vector<char> secret_code_player(std::vector <char> playerCode, const GameOptions& game_options)
	{
		std::istream& input_stream = std::cin;
		std::cout << "\n Give a secret code character by character in UpperCase \n";


		
		for (int i = 0; i < playerCode.size(); i++)
		{
			bool check = false;
			do {

				std::cout << "Letter  : ";
				playerCode[i] = ask_char_or_default(input_stream, 'O');
				check = checkError(playerCode[i], game_options); // regarde si les criteres de l'input sont bien respectes

			} while (check); //Tant que les criteres ne sont pas respectes


		}

		for (int i = 0; i < playerCode.size(); i++)
		{

			std::cout << playerCode[i];

		}

		return playerCode; //return le code du joueur 

	}

	//fonction qui permet de compter le nombre de bulls and cows pour des codes sans doublon
	FinalBoard count_bulls_cows_without_double(std::string secretCode, std::vector <char> playerCode, FinalBoard& current_attempt)
	{
		int bulls = 0; //nombre de bulls
		int cows = 0; //nombre de cows

		for (int i = 0; i < playerCode.size(); i++)
		{
			if (secretCode[i] == playerCode[i]) // Si les 2 chars sont a la meme position
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

		if (bulls == secretCode.size()) // si il y a le meme nombre de bulls que la longueur du code secret 
		{
			current_attempt.win = true; // alors c'est gagne donc win = true
		}
		else //sinon win = faux 
		{
			current_attempt.win = false; 
		}

		cows = cows - bulls; //evite de compter les bulls comme des cows
		current_attempt.bulls = bulls;
		current_attempt.cows = cows;

		return current_attempt; //return un objet de la Structure FinalBoard 

	}

	//fonction qui permet de compter le nombre de bulls and cows pour des codes avec doublons
	FinalBoard count_bulls_cows_with_double(std::string secretCode, std::string playerCode, FinalBoard& current_attempt)
	{
		int bulls = 0; //nombre de bulls
		int cows = 0; //nombre de cows

		std::string clone_player = playerCode;
		std::string clone_secret_code = secretCode;

		for (int i = 0; i < playerCode.size(); i++)
		{
			if (secretCode[i] == playerCode[i]) // Si les 2 chars sont a la meme position
			{
				bulls = bulls + 1;
				clone_player[i] = '0';
				clone_secret_code[i] = '1';
			}
		}

		for (int i = 0; i < playerCode.size(); i++)
		{


			for (int j = 0; j < playerCode.size(); j++)
			{

				if (clone_secret_code[j] == clone_player[i])
				{
					cows = cows + 1;
					clone_player[i] = '0';
					clone_secret_code[j] = '1';
				}
			}

		}

		if (bulls == secretCode.size()) // si il y a le meme nombre de bulls que la longueur du code secret 
		{
			current_attempt.win = true; // alors c'est gagne donc win = true
		}
		else //sinon win = faux 
		{
			current_attempt.win = false;
		}

		//cows = cows - bulls; //evite de compter les bulls comme des cows
		current_attempt.bulls = bulls;
		current_attempt.cows = cows;
		//current_attempt.secretCode = playerCode;

		return current_attempt; //return un objet de la Structure FinalBoard 

	}

	//fonction qui converti un vector de char en string 
	std::string conv_vector_to_string(std::vector <char> vector_to_convert)
	{
		return std::string{ vector_to_convert.begin(), vector_to_convert.end() };
	}
	std::vector<char> conv_string_to_vector(std::string string_to_convert)
	{
		std::vector<char> new_vector;

		for (int i = 0; i < string_to_convert.size(); i++)
		{
			new_vector.push_back(string_to_convert[i]);
		}
		return new_vector;

	}

	void user_plays_against_computer(const GameOptions& game_options)
	{
		std::cout << " ~~~~~~~~~~~~ USER PLAYS AGAINST COMPUTER ~~~~~~~~~~~~\n";



		std::string secret_code_to_find = secret_code_init_without_double(game_options);
		std::vector <char> playerCode(game_options.number_of_characters_per_code);
		std::vector<int> counter_bowls_cows(3);
		unsigned int player_attempts = 0;
		bool not_win = true;

		std::cout << "Code to find : " << secret_code_to_find;


		std::vector <FinalBoard> board_final;
		board_final.push_back(FinalBoard(secret_code_to_find, 0, 0, false));


		do
		{

			playerCode = secret_code_player(playerCode, game_options);
			FinalBoard current_attempt = count_bulls_cows_without_double(secret_code_to_find, playerCode, current_attempt);
			std::string secret_code_player = conv_vector_to_string(playerCode);
			board_final.emplace_back(secret_code_player, current_attempt.bulls, current_attempt.cows, current_attempt.win);

			player_attempts++;
			std::cout << "\n";
			display_board(board_final);

			if (current_attempt.win == true)
			{
				not_win = false;
			}



		} while (not_win && player_attempts < game_options.max_number_of_attempts);


		if (not_win == false)
		{
			std::cout << "\n" << "\n" << "YOU WON !";
		}
		else
		{
			std::cout << "YOU LOOSE ! ";
		}


	}
	
		
    void computer_plays_against_computer(const GameOptions& game_options)
    {
        std::cout
            << " Computer plays against computer \n";
		PossibleSolutions dico_all_codes{};
		dico_all_codes = bulls_and_cows::generate_all_possible_codes(game_options); // Computer2 creates a collection of all the possible codes

		//Computer1 creates a randomly - generated secret code
		std::string secret_code = secret_code_init_with_double(game_options);
		bool not_win = true;
		unsigned int ai_attempts = 0;
		std::vector <FinalBoard> board_final;
		board_final.push_back(FinalBoard(secret_code, 0, 0, false));

		do 
		{
			int index = generate_random_integer(0, static_cast<int> (dico_all_codes.codes.size()-1)); //Random index pour choisir dans la liste des possibilités
			
			// dico_all_codes.codes[index] est le code choisi par le Computer 2 
			FinalBoard current_attempt = count_bulls_cows_with_double(secret_code, dico_all_codes.codes[index], current_attempt);
			current_attempt.secretCode = dico_all_codes.codes[index];
			board_final.push_back(current_attempt);
			

			display_board(board_final);

			if (current_attempt.win == true)
			{
				not_win = false;
			}
			erase_invalid_solutions(dico_all_codes, current_attempt);
			std::cout << "Number of codes in dico : \n" << dico_all_codes.codes.size() <<"\n";
			
			ai_attempts++;
			std::this_thread::sleep_for(std::chrono::seconds(1));
				

		} while (not_win && ai_attempts < game_options.max_number_of_attempts);
		
		if (not_win == false)
		{
			std::cout << "\n" << "\n" << "Computer 2 WON !";
		}
		else
		{
			std::cout << "IA not enough strong ! " << "\n";
		}

		
    }
	   
	// Menu pour savoir quel attribut changer 
	void  modify_game_options_menu(GameOptions& game_options)
	{
		bool stay = true;
		
		
		do {

			std::cout << "\n Which game option do you want to change ? ";
			std::cout << "\n 0) Exit";
			std::cout << "\n 1) Number of characters per code ? ";
			std::cout << " \n 2) Character min ? ";
			std::cout << "\n 3) Character max ? \n ";

			const auto user_choice = ask_option_menu_choice(std::cin);
			switch (user_choice)
			{
			case OptionMenuChoice::Quit:
				std::cout << "Exit \n";
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

	// Menu des options
    void configure_game_options(GameOptions& game_options)
    {
		bool stay = true;
		do {

			std::cout << "\n"
				"    DO\n"
				"       0) Exit \n"
				"       1) Display the current game options\n"
				"       2) Display the game options menu (Modify Game Options) \n"
				"       3) Save the current game options \n"
				"       4) Display the game options saved \n"
				"       5) Load the game options saved \n"
				"      ";
			

			const auto user_choice = ask_configuration_menu_choice(std::cin);
			switch (user_choice)
			{
			case ConfigureOptions::Quit:
				std::cout << "Exit \n";
				stay = false;
				return;
			case ConfigureOptions::CurrentGameOptions:
				display_current_game_options(game_options);
				break;
			case ConfigureOptions::GameOptionMenu:
				modify_game_options_menu(game_options);
				break;

			case ConfigureOptions::SaveOption:
				save_option_file(game_options);
				std::cout << "Saved ! \n";
				break;

			case ConfigureOptions::ReadOption:
				read_file(game_options);
				break;

			case ConfigureOptions::LoadOption:
				load_option_file(game_options);
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
