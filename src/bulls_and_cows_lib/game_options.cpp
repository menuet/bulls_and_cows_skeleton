
#include "game_options.hpp"

namespace bulls_and_cows {

    // TODO: define the body of the functions declared in game_options.cpp

        void display_game_options_menu(std::ostream& output_stream)
    {
        output_stream << "Game options menu\n"
                         "0 - Return to main\n"
                         "1 - Modify number of attempts\n"
                         "2 - Modify number of character per code\n"
                         "3 - Modify minimum character allowed\n"
                         "4 - Modify maximum character allowed\n"
                         "5 - Save your choice\n"
                         "6 - Load options\n"
                         "What is your choice ? ";
    }

    GameOptionsMenuChoice ask_games_options_choice(std::istream& input_stream)
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
} // namespace bulls_and_cows
