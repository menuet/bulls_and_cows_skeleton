
#include "game_options.hpp"
#include "input.hpp"

namespace bulls_and_cows {

    // TODO: define the body of the functions declared in game_options.cpp
    void display_game_options(std::ostream& output_stream, const GameOptions& game_options)
    {
        output_stream << "\nNumber of characters per code : " << game_options.number_of_characters_per_code << "\n";
        output_stream << "Minimum allowed character : " << game_options.minimum_allowed_character << "\n";
        output_stream << "Maximum allowed character : " << game_options.maximum_allowed_character << "\n";
        output_stream << "Maximum number of attemtps : " << game_options.max_number_of_attempts << "\n";
    }

    void display_game_options_menu(std::ostream& output_stream)
    {
        output_stream << "\nConfigure Options\n"
                         "0 - Back to main menu\n"
                         "1 - Modify Maximum number of attempts per game\n"
                         "2 - Modify Number of characters in a code\n"
                         "3 - Modify Minimum allowed character\n"
                         "4 - Modify Maximum allowed character\n"
                         "5 - Save options\n"
                         "6 - Load options\n"
                         "What is your choice ? ";
    }

    GameOptionsMenuChoice ask_game_options_menu_choice(std::istream& input_stream)
    {
        const int choice_menu = ask_int_or_default(input_stream, -1);

        switch (choice_menu)
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

    void modify_maximum_number_of_attempts(GameOptions& game_options, std::ostream& output_stream,
                                           std::istream& input_stream)
    {
        unsigned int new_nb_of_attempts = 0;
        output_stream << "\nEnter the number of attempts (must be > 0) : ";
        new_nb_of_attempts = ask_uint_or_default(input_stream, 0);

        while (new_nb_of_attempts == 0)
        {
            output_stream << "Incorrect number, try again !\n";
            output_stream << "Enter the number of attempts (must be > 0) : ";
            new_nb_of_attempts = ask_uint_or_default(input_stream, 0);
        }

        output_stream << "Number of attempts has been modified succefully\n";
        game_options.max_number_of_attempts = new_nb_of_attempts;
    }

    void modify_number_of_characters_per_code(GameOptions& game_options, std::ostream& output_stream, std::istream& input_stream)
    {
        unsigned int new_nb_of_characters = 0;
        unsigned int diff = (game_options.maximum_allowed_character - game_options.minimum_allowed_character) + 1;
        output_stream << "\nEnter the number of characters ((must be superior to 0) & (inferior or equal to the numerecial difference btwn max_allowed_char and min_allowed_char)) : ";
        new_nb_of_characters = ask_uint_or_default(input_stream, 0);

        while (new_nb_of_characters == 0 || new_nb_of_characters > diff)
        {
            output_stream << "Incorrect number, try again !\n";
            output_stream << "Enter the number of characters ((must be superior to 0) & (inferior or equal to the numerecial difference btwn max_allowed_char and min_allowed_char)) : ";
            new_nb_of_characters = ask_uint_or_default(input_stream, 0);
        }

        output_stream << "Number of characters per code has been modified succefully\n";
        game_options.number_of_characters_per_code = new_nb_of_characters;
    }

} // namespace bulls_and_cows
