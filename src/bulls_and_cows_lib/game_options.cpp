
#include "game_options.hpp"
#include "input.hpp"
#include <fstream>
#include <iostream>
#include <string>

namespace bulls_and_cows {

    void display_game_options(std::ostream& output_stream, const GameOptions& game_options)
    {

        
        

        output_stream << " le nombre maximum de tentative est " << game_options.max_number_of_attempts << std::endl
                      << "le nombre de lettre maximum est de " << game_options.number_of_characters_per_code
                      << std::endl
                      << "la plus petite lettre authorise est  " << game_options.minimum_allowed_character << std::endl
                      << "la plus grande est  " << game_options.maximum_allowed_character << std::endl;
                     
                       
                     

    }
    void display_game_options_menu(std::ostream& output_stream)
    {
        
        output_stream << "menu configurations" << std::endl
                      << " si vous voulez revenir au menu taper 0" << std::endl
                      << " si vous voulez modifier le nombre de maximum de tentative taper 1" << std::endl
                      << " si vous voulez modifier le nombre de caractere par code taper 2" << std::endl
                      << " si vous voulez modifier la lettre minimum authorise taper 3" << std::endl
                      << " si vous voulez modifier la lettre maximum authorise taper 4" << std::endl
                      << " si vous voulez sauvegarder les options taper 5" << std::endl
                      << " si vous voulez charger les options taper 6" << std::endl;


                      
        
    }

    GameOptionsMenuChoice ask_game_options_menu_choice(std::istream& input_stream)
    {
    
    const int user_choice = ask_int_or_default(input_stream, -1);
        switch (user_choice)
        {
        case 0:
            return GameOptionsMenuChoice :: BackToMain;
        case 1:
            return GameOptionsMenuChoice ::ModifyMaximumNumberOfAttempts;
        case 2:
            return GameOptionsMenuChoice ::ModifyNumberOfCharactersPerCode;
        case 3:
            return GameOptionsMenuChoice ::ModifyMinimumAllowedCharacter;
        case 4:
            return GameOptionsMenuChoice ::ModifyMaximumAllowedCharacter;
        case 5:
            return GameOptionsMenuChoice ::SaveOptions;
        case 6:
            return GameOptionsMenuChoice ::LoadOptions;
        }
        return GameOptionsMenuChoice::Error;
    }

    bool save_game_options(std::ostream& output_file_stream,const GameOptions& game_options)
    {
      
        if (output_file_stream)
        {
            output_file_stream << game_options.max_number_of_attempts << "\n" 
                               << game_options.number_of_characters_per_code << "\n" 
                               << game_options.minimum_allowed_character << "\n" 
                               << game_options.maximum_allowed_character << std::endl;
            return true;
        }
        return false;
    }
    bool load_game_options(std::ifstream& input_file_stream, GameOptions& game_options)
    {
        if (input_file_stream)
        {
            std::string ligne{};

            std::getline(input_file_stream, ligne);
            unsigned int nb_attempt = std::stoi(ligne);
            game_options.max_number_of_attempts = nb_attempt;

            std::getline(input_file_stream, ligne);
            unsigned int nb_character = std::stoi(ligne);
            game_options.number_of_characters_per_code = nb_character;

            std::getline(input_file_stream, ligne);
            game_options.minimum_allowed_character = ligne[0];

            std::getline(input_file_stream, ligne);
            game_options.maximum_allowed_character = ligne[0];

            return true;
        }
        return false;
    }
  } // namespace bulls_and_cows
