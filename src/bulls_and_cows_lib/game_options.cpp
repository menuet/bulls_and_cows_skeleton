
#include "game_options.hpp"
#include "input.hpp"

namespace bulls_and_cows {

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

        game_options.max_number_of_attempts = new_nb_of_attempts;
        output_stream << "Number of attempts has been modified succefully\n";
    }

    void modify_number_of_characters_per_code(GameOptions& game_options, std::ostream& output_stream,
                                              std::istream& input_stream)
    {
        unsigned int new_nb_of_characters = 0;
        output_stream << "\nEnter the number of characters ((must be superior to 0) & (inferior or equal to the "
                         "numerecial difference btwn max_allowed_char and min_allowed_char)) : ";
        new_nb_of_characters = ask_uint_or_default(input_stream, 0);
        unsigned int diff = (game_options.maximum_allowed_character - game_options.minimum_allowed_character) + 1;

        while (new_nb_of_characters == 0 || new_nb_of_characters > diff)
        {
            output_stream << "Incorrect number, try again !\n";
            output_stream << "Enter the number of characters ((must be > to 0) & ( <= to the "
                             "numerecial difference btwn max_allowed_char and min_allowed_char)) : ";
            new_nb_of_characters = ask_uint_or_default(input_stream, 0);
            diff = (game_options.maximum_allowed_character - game_options.minimum_allowed_character) + 1;
        }

        game_options.number_of_characters_per_code = new_nb_of_characters;
        output_stream << "Number of characters per code has been modified succefully\n";
    }

    void modify_minimum_allowed_characters(GameOptions& game_options, std::ostream& output_stream,
                                           std::istream& input_stream)
    {
        char new_minimum{};
        auto max = game_options.maximum_allowed_character;
        auto nb_char = game_options.number_of_characters_per_code;

        output_stream << "\nEnter the minimum allowed character (must be < to maximum allowed charcter & maxi_allowed_char - min_allowed_char must be >= nb character per code) : ";
        new_minimum = ask_char_or_default(input_stream, -1);
        unsigned int diff = max - new_minimum + 1;

        while (new_minimum == -1 || new_minimum >= max || diff < nb_char)
        {
            output_stream << "Incorrect input, try again !\n";
            output_stream << "Enter the minimum allowed character (must be < to maximum allowed charcter & maxi_allowed_char - min_allowed_char must be >= nb character per code) : ";
            new_minimum = ask_char_or_default(input_stream, -1);
            diff = max - new_minimum + 1;
        }

        game_options.minimum_allowed_character = new_minimum;
        output_stream << "Minimum allowed character has been modified succefully\n";
    }

    void modify_maximum_allowed_characters(GameOptions& game_options, std::ostream& output_stream,
                                           std::istream& input_stream)
    {
        char new_maximum{};
        char min = game_options.minimum_allowed_character;
        auto nb_char = game_options.number_of_characters_per_code;

        output_stream << "\nEnter the maximum allowed character (must be > to minimum allowed character & "
                         "maxi_allowed_char - min_allowed_char must be >= nb character per code) : ";
        new_maximum = ask_char_or_default(input_stream, -1);
        unsigned int diff = new_maximum - min + 1;

        while (new_maximum == -1 || ( new_maximum <= min) || (diff < nb_char) )
        {
            output_stream << "Incorrect input, try again !\n";
            output_stream << "Enter the maximum allowed character (must be > to minimum allowed character & "
                             "maxi_allowed_char - min_allowed_char must be >= nb character per code) : ";
            new_maximum = ask_char_or_default(input_stream, -1);
            diff = new_maximum - min + 1;
        }

        game_options.maximum_allowed_character = new_maximum;
        output_stream << "Maximum allowed character has been modified succefully\n";
    }

} // namespace bulls_and_cows
