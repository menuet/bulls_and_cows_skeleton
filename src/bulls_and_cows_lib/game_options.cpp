
#include "game_options.hpp"
#include "input.hpp"

namespace bulls_and_cows {

    // TODO: define the body of the functions declared in game_options.cpp

    // Display the current game options
    void display_game_options(std::ostream& output_stream, const GameOptions& game_options)
     {
         output_stream << "game options:" << std::endl;
         output_stream << "the maximum number of attempt is :" << game_options.max_number_of_attempts
                       << std::endl;
         output_stream << "the number of characters per code is:" << game_options.number_of_characters_per_code
                       << std ::endl;
         output_stream << "the allowed characters are between '" << game_options.minimum_allowed_character
                       << " ' & '" << game_options.maximum_allowed_character << "' " << std::endl;
     }


     //Display the game options menu
     void display_game_options_menu(std::ostream& output_stream)
     {
         output_stream << "options" << std::endl;
         output_stream << "0 - Back to Main" << std::endl;
         output_stream << "1 - Modify the maximum number of attempts" << std::endl;
         output_stream << "2 - Modify the number of characters in a code" << std::endl;
         output_stream << "3 - Modify the minimum of allowed characters" << std::endl;
         output_stream << "4 - Modify the maximum of allowed characters" << std::endl;
         output_stream << "5 - Save options" << std::endl;
         output_stream << "6 - Load options" << std::endl;
         output_stream << " Make your choice !";
     }

    //Ask the user to type its choice
     GameOptionsMenuChoice ask_game_options_menu_choice(std::istream& input_stream)
     {
        unsigned int c = ask_int_or_default(input_stream, -1);
         switch (c)
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

} // namespace bulls_and_cows
