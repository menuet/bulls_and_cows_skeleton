
#include "input.hpp"
#include <fstream>
#include <iostream>
#include <string>
#include "game_options.hpp"

namespace bulls_and_cows {

    void display_game_options(std::ostream& output_stream, const GameOptions& game_options)
    {
        std::cout << "The number of attempts is :";
        std::cout << game_options.max_number_of_attempts"\n";
        output_stream << "The number of characters in the code is:" << game_options.number_of_characters_per_code"\n";
        output_stream << "The minimal character allowed is : " << game_options.minimum_allowed_character"\n";
        output_stream << "The maximal character allowed is : "<< game_options.maximum_allowed_character "\n" ;

    }
    void display_game_options_menu(std::ostream& output_stream)
    {
        output_stream << "Configure options \n" ;
        output_stream << "0 - Go back to Menu \n" ;
        output_stream << "1 - Modify Maximum number of attempts per code \n" ;
        output_stream << "2 - Modify Number of characters in a code \n" ;
        output_stream << "3 - Modify Maximum allowed characters \n" ;
        output_stream << "4 - Modify Minimum allowed characters \n" ;
        output_stream << "5 - Save  options \n" ;
        output_stream << " 6 - Load  options \n" ;
        output_stream << "Enter your choice \n";

    }
    
      GameOptionsMenuChoice ask_game_options_menu_choice(std::istream& input_stream)
    {
        switch (ask_int_or_default(input_stream,-1))
        {
        case 0:
            return GameOptionsMenuChoice::BackToMain;
        case 1:
            return GameOptionsMenuChoice::ModifyMaximumNumberOfAttempts;
        case 2:
            return GameOptionsMenuChoice::ModifyNumberOfCharactersPerCode;
        case 3:
            return GameOptionsMenuChoice::ModifyMinimumAllowedCharacter;
        case 4:
            return GameOptionsMenuChoice::ModifyMaximumAllowedCharacter;
        case 5:
            return GameOptionsMenuChoice::SaveOptions;
        case 6:
            return GameOptionsMenuChoice::LoadOptions;
        }
        return GameOptionsMenuChoice::Error;
    }

    // TODO: define the body of the functions declared in game_options.cpp

} // namespace bulls_and_cows
