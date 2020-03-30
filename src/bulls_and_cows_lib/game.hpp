
#pragma once

#include <vector> 
#include <chrono>
#include <fstream>
#include <iostream>
#include <thread>
#include <vector>
#include <bulls_and_cows_lib/game_options.hpp>

namespace bulls_and_cows {

	struct FinalBoard
	{
		std::string secretCode{};
		unsigned int bulls{};
		unsigned int cows{};
		bool win = false;
		FinalBoard(std::string _secretCode, unsigned int _bulls, unsigned int _cows, bool _win)
			: secretCode(_secretCode), bulls(_bulls), cows(_cows), win(_win)
		{}
	};

	enum class OptionMenuChoice
	{
		Error = -1,
		Quit = 0,
		NumberOfCharacters = 1,
		CharMin = 2,
		CharMax = 3,
	};

	enum class ConfigureOptions
	{
		Error = -1,
		Quit = 0,
		CurrentGameOptions = 1,
		GameOptionMenu = 2,
		SaveOption = 3,
		ReadOption = 4,
		LoadOption = 5,

	};
	
	
	void play_game();
	void save_option_file(const GameOptions& game_options);
	void read_file(const GameOptions& game_options);
	void load_option_file(GameOptions& game_options);
	void display_current_game_options(const GameOptions& game_options);
	void change_Number_Characters(GameOptions& game_options);
	void change_Char_Min(GameOptions& game_options);
	void change_Char_Max(GameOptions& game_options);
	void modify_game_options_menu(GameOptions& game_options);
	void configure_game_options(GameOptions& game_options);
	void display_board(std::vector <FinalBoard>  board);

	bool isContainedIn(char rand, const std::vector <char>& secretCode);
	bool checkError(char carac, const GameOptions& game_options);

	FinalBoard count_true_false(std::vector <char> secretCode, std::vector <char> playerCode, FinalBoard& current_attempt);
	std::vector<char> secret_code_init(const GameOptions& option);
	std::vector<char> secret_code_player(std::vector <char> playerCode, const GameOptions& game_options);
	std::string conv_vector_to_string(std::vector <char> vector_to_convert);
	OptionMenuChoice ask_option_menu_choice(std::istream& input_stream);
	ConfigureOptions ask_configuration_menu_choice(std::istream& input_stream);
	
} // namespace bulls_and_cow
