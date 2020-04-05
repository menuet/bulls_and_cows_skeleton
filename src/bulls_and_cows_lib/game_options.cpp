
#include "game_options.hpp"
#include "input.hpp"
#include <vector> 
#include <chrono>
#include <fstream>
#include <iostream>
#include <thread>
#include <stdexcept>
#include <sstream>

namespace bulls_and_cows {

    // TODO: define the body of the functions declared in game_options.cpp

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
			std::cout << "Game options : \n ";
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

	

} // namespace bulls_and_cows
