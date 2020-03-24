
#include "game_options.hpp"
#include "input.hpp"

namespace bulls_and_cows {

    // TODO: define the body of the functions declared in game_options.cpp
    void display_game_options(std::ostream& output_stream, const GameOptions& game_options)
    {
        output_stream << "These are the game options\n" 
                      << "Maximum number of attempts per game: " << game_options.max_number_of_attempts << "\n" 
                      << "Number of characters in a code: " << game_options.number_of_characters_per_code << "\n" 
                      << "Range of allowed characters: " << game_options.minimum_allowed_character 
                      << "up to "<< game_options.maximum_allowed_character << "\n"; 

    }
    void display_game_options_menu(std::ostream& output_stream)
    {
        output_stream << "Here are the game options\n"
                      << "0 - BackToMain\n"
                      << "1 - Modify the maximum number of attempts\n"
                      << "2 - Modify the number of characters per code\n"
                      << "3 - Modify the minimum allowed of characters\n"
                      << "4 - Modify the maximum allowed of characters\n"
                      << "5 - Save options\n"
                      << "6 - Load options\n"
                      << "What is your choice ? ";
    }
    GameOptionsMenuChoice ask_game_options_menu_choice(std::istream& input_stream)
    {
        int user_choice{};
        GameOptionsMenuChoice input{};
        user_choice = ask_int_or_default(input_stream, -1);

        switch (user_choice)
        {
        case -1:
            input= GameOptionsMenuChoice::Error;
            break;
        case 0:
            input = GameOptionsMenuChoice::BackToMain;
            break;
        case 1:
            input = GameOptionsMenuChoice::ModifyMaximumNumberOfAttempts;
            break;
        case 2:
            input = GameOptionsMenuChoice::ModifyNumberOfCharactersPerCode;
            break;
        case 3:
            input = GameOptionsMenuChoice::ModifyMinimumAllowedCharacter;
            break;
        case 4:
            input = GameOptionsMenuChoice::ModifyMaximumAllowedCharacter;
            break;
        case 5:
            input = GameOptionsMenuChoice::SaveOptions;
            break;
        case 6:
            input = GameOptionsMenuChoice::LoadOptions;
            break;
        }
        return input;
    }

    bool save_game_options(std::ostream & output_file_stream, const GameOptions& game_options)
    {
        output_file_stream << "max_number_of_attempts =" << game_options.max_number_of_attempts
                           << "\n"
                              "number_of_characters_per_code ="
                           << game_options.number_of_characters_per_code
                           << "\n"
                              "minimum_allowed_character ="
                           << game_options.minimum_allowed_character
                           << "\n"
                              "maximum_allowed_character="
                           << game_options.maximum_allowed_character << "\n";
        return true;
    }
    bool load_game_options(std::istream& input_file_stream, GameOptions& game_options)
    {
       std::string result;
       std::getline(input_file_stream, result);
       
        //game_options.max_number_of_attempts == 5;
        //game_options.number_of_characters_per_code == 3;
        //game_options.minimum_allowed_character == '1';
        //game_options.maximum_allowed_character == '8';
        return true;
    }
       
}// namespace bulls_and_cows
