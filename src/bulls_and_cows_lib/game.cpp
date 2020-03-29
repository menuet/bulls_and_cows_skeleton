
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
	bool isContainedIn(char rand, const std::vector <char> secretCode)
	{
		bool is_found = false;
		for (const char c : secretCode)
		{
			if (rand == c)
			{
				is_found = true;
				break;
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

	// Algorithme standard à tester
	bool isContainedIn_V2(char characterToSearchFor, const std::vector<char> charactersToSearchIn)
	{
		const auto iter = std::find(charactersToSearchIn.begin(), charactersToSearchIn.end(), characterToSearchFor);
		return iter != charactersToSearchIn.end();
	}

	//Function to initialize secret code 
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

	//fonction qui affiche le tableau d'affichage 
	void display_board(std::vector <FinalBoard>  board)
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

	//fonction qui permet de retourner le code secret qu'a input l'utilisateur
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

	//fonction qui permet de compter le nombre de bulls and cows
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

	//fonction qui converti un vector de char en string 
	std::string conv_vector_to_string(std::vector <char> vector_to_convert)
	{
		return std::string{ vector_to_convert.begin(), vector_to_convert.end() };
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


		
		std::vector <char> secretCode(game_options.number_of_characters_per_code);
		secretCode = secret_code_init(secretCode, game_options);
		std::vector <char> playerCode(game_options.number_of_characters_per_code);
		std::vector<int> counter_bowls_cows(3);
		unsigned int player_attempts = 0;
		bool not_win = true;
		
		std::string secret_code_to_find = conv_vector_to_string(secretCode);

		std::cout << secret_code_to_find;
		
		
		std::vector <FinalBoard> board_final;
		board_final.push_back(FinalBoard(secret_code_to_find, 0, 0));


		do
		{

			playerCode = secret_code_player(playerCode, game_options);
			counter_bowls_cows = count_true_false(secretCode, playerCode, counter_bowls_cows);
			std::string secret_code_player = conv_vector_to_string(playerCode);
			board_final.emplace_back(secret_code_player, counter_bowls_cows[1], counter_bowls_cows[2]);
			player_attempts++;
			std::cout << "\n";
			display_board(board_final);

			if (counter_bowls_cows[1] == 5)
			{
				not_win = false;
			}


		} while (not_win && player_attempts < game_options.max_number_of_attempts);


		if (not_win == false)
		{
			std::cout << "\n" << "\n" << "YOU WIN !";
		}

		else
		{
			std::cout << "YOU LOOSE ! ";
		}


    }

	//Pas encore implementer
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

	// Save option functions 
	void save_option_file(const GameOptions& game_options)
	{
		const std::string path = "C:/DEVCPP/PROJECTS/bulls_and_cows_skeleton/out/save_option.txt";
		std::ofstream monFlux(path.c_str());

		if (monFlux)
		{
		
			
			monFlux << game_options.number_of_characters_per_code << std::endl;
			monFlux << game_options.minimum_allowed_character << std::endl;
			monFlux << game_options.maximum_allowed_character << std::endl;
		
		}
		else
		{
			std::cout << "Error \n" << std::endl;
		}

	}

	// Fonction de lecture dans un txt 
	void read_file(const GameOptions& game_options)
	{
		const std::string path = "C:/DEVCPP/PROJECTS/bulls_and_cows_skeleton/out/save_option.txt";

		std::ifstream file(path);
		
		if (file)
		{
			std::string line;
			int count_line = 1;
			std::cout <<"Game options : \n ";
			while (getline(file, line)) 
			{
				
				if (count_line == 1)
				{
					std::cout << "Number of characters per code : " << line << std::endl;
				}

				if (count_line == 2)
				{
					std::cout << "Character min " << line << std::endl;
				}
				
				if (count_line == 3)
				{
					std::cout << "Character max " << line << std::endl;
				}
				count_line++;
			}
		}
		else
		{
			std::cout << "Impossible to open the file" << std::endl;
		}



	}

	//Fonction qui va charger les options sauvergardées à partir d'un fichier txt 
	void load_option_file(GameOptions& game_options)
	{

		const std::string path = "C:/DEVCPP/PROJECTS/bulls_and_cows_skeleton/out/save_option.txt";

		std::ifstream file(path);

		if (file)
		{
			std::string line;
			int count_line = 1;
			
			while (getline(file, line))
			{

				if (count_line == 1)
				{
					std::cout << "Number of characters per code : " << line << std::endl;
					game_options.number_of_characters_per_code = std::abs(atoi(line.c_str())); // sorry for this cast I do not know how to do in other way 
				}

				if (count_line == 2)
				{
					std::cout << "Character min " << line << std::endl;
					game_options.minimum_allowed_character = *line.c_str();
				}

				if (count_line == 3)
				{
					std::cout << "Character max " << line << std::endl;
					game_options.maximum_allowed_character = *line.c_str();
				}
				count_line++;
			}
		}
		else
		{
			std::cout << "Impossible to open the file" << std::endl;
		}


	}

	//Fonction qui va afficher les games options en affichant les attributs de la structure GameOptions
	void display_current_game_options(const GameOptions& game_options)
	{
		std::cout << "Game options : \n ";
		std::cout << " Number of characters per code : " << game_options.number_of_characters_per_code;
		std::cout << " \n Character min " << game_options.minimum_allowed_character;
		std::cout << "\n Character max " << game_options.maximum_allowed_character;

	}

	//Fonction qui va attribuer une nouvelle valeur à l'attribut number_of_characters_per_code de la structure GameOptions
	void change_Number_Characters(GameOptions& game_options)
	{
		
		std::cout << "How many characters do you want ? ";
		const unsigned int numberC = ask_int_or_default(std::cin, -1);
		game_options.number_of_characters_per_code = numberC;

		std::cout << "Updated ! \n";

		
	}

	//Fonction qui va attribuer une nouvelle valeur à l'attribut minimum_allowed_character de la structure GameOptions
	void change_Char_Min(GameOptions& game_options)
	{

		std::cout << "Which characters do you want to have as min character ? \n";
		const char char_min = ask_char_or_default(std::cin, -1);
		game_options.minimum_allowed_character = char_min;
		std::cout << "Updated ! \n";

		
	}

	//Fonction qui va attribuer une nouvelle valeur à l'attribut maximum_allowed_character de la structure GameOptions
	void change_Char_Max(GameOptions& game_options)
	{

		std::cout << "Which characters do you want to have as max character ? \n";
		const char char_max = ask_char_or_default(std::cin, -1);
		game_options.maximum_allowed_character = char_max;
		std::cout << "Updated ! \n";


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
