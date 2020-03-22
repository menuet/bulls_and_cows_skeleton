
#include "game_options.hpp"
#include "input.hpp"

namespace bulls_and_cows {

    // TODO: define the body of the functions declared in game_options.cpp
    void display_game_options(std::ostream& output_stream, const GameOptions& game_options)
    {
        //const bulls_and_cows::GameOptions game_options{};
        //bulls_and_cows::display_game_options(output_stream, game_options);
        output_stream << " unsigned int max_number_of_attempts\n"
                         " number_of_characters_per_code \n"
                         " minimum_allowed_character \n"
                         " maximum_allowed_character";
    }
    void display_game_options_menu(std::ostream& output_stream)
    {
        output_stream << "Here are the game options\n"
                         "0 - BackToMain\n"
                         "1 - Modify the maximum number of attempts\n"
                         "2 - Modify the number of characters per code\n"
                         "3 - Modify the minimum allowed of characters\n"
                         "4 - Modify the maximum allowed of characters\n"
                         "5 - Save options\n"
                         "6 - Load options\n"
                         "What is your choice ? ";
    }
    GameOptionsMenuChoice ask_game_options_menu_choice(std::istream& input_stream)
    {
        const int user_choice = ask_int_or_default(input_stream, -1);

        switch (user_choice)
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

    bool save_game_options(std::ostream & output_file_stream, const GameOptions& game_options)
    {
        //const bulls_and_cows::GameOptions game_options{};
        const auto result = GameOptionsMenuChoice::SaveOptions;
        result;
        output_file_stream << 
                         "max_number_of_attempts=12\n"
                         "number_of_characters_per_code=5\n"
                         "minimum_allowed_character=A\n"
                         "maximum_allowed_character=H\n";
    }
    bool load_game_options(std::istream& input_file_stream, GameOptions& game_options)
    {
        //bulls_and_cows::GameOptions game_options{};
        const auto result = GameOptionsMenuChoice::LoadOptions;
        result;
        game_options.max_number_of_attempts == 5;
        game_options.number_of_characters_per_code == 3;
        game_options.minimum_allowed_character == '1';
        game_options.maximum_allowed_character == '8';
    }
       
}// namespace bulls_and_cows
