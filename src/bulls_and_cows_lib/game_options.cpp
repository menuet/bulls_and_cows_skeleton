
#include "game_options.hpp"
#include "input.hpp"
#include <iostream>

namespace bulls_and_cows {

void display_current_game_options(const GameOptions& game_options)
    {
        std::cout << "Game options : \n ";
        std::cout << " Number of characters per code : " << game_options.number_of_characters_per_code;
        std::cout << " \n Character min " << game_options.minimum_allowed_character;
        std::cout << "\n Character max " << game_options.maximum_allowed_character;
    }

    // Fonction qui change le nombre de caractere par code 
 
    void change_Number_Characters(GameOptions& game_options)
    {

        std::cout << "nombre de caractere ? ";
        const unsigned int n = ask_int_or_default(std::cin, -1);
        game_options.number_of_characters_per_code = n;

        std::cout << "ok! \n";
    }

    // Fonction qui change la valeur minimal possible
    void change_Char_Min(GameOptions& game_options)
    {

        std::cout << "min caractere ? \n";
        const char min = ask_char_or_default(std::cin, -1);
        game_options.minimum_allowed_character = min;
        std::cout << "ok! \n";
    }

    // Fonction qui change la valeur maximale possible
    void change_Char_Max(GameOptions& game_options)
    {

        std::cout << "max caractere ? \n";
        const char max = ask_char_or_default(std::cin, -1);
        game_options.maximum_allowed_character = max;
        std::cout << "ok ! \n";
    }

    // TODO: define the body of the functions declared in game_options.cpp

} // namespace bulls_and_cows
