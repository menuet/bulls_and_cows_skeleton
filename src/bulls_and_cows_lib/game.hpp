
#pragma once

#include <vector> 
#include <chrono>
#include <fstream>
#include <iostream>
#include <thread>

namespace bulls_and_cows {

    void play_game();
	/*struct FinalBoard
	{
		string secretCode;
		unsigned int bulls;
		unsigned int cows;
		
		// constructeur
		FinalBoard(string _secretCode, unsigned int _bulls, unsigned int _cows)
		{
			secretCode = _secretCode;
			bulls = _bulls;
			cows = _cows;
		}

	};*/

	struct FinalBoard
	{
		std::string secretCode{};
		unsigned int bulls{};
		unsigned int cows{};
		FinalBoard(std::string _secretCode, unsigned int _bulls, unsigned int _cows)
			: secretCode(_secretCode), bulls(_bulls), cows(_cows)
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

	};



} // namespace bulls_and_cow
