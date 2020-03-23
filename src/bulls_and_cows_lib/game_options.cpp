
#include "game_options.hpp"

namespace bulls_and_cows {

     void display_game_options(std::ostream& output_stream, const GameOptions& game_options)
    {
        output_stream << "Here are the current game_options:\n"
                      << "Maximum number of attempts per game: " << game_options.max_number_of_attempts
                      << "\n Number of characters in a code:" << game_options.number_of_characters_per_code
                      << "\n Range of allowed characters : from '" << game_options.minimum_allowed_character << "' to '"
                      << game_options.maximum_allowed_character << "'";
    }

    void display_game_options_menu(std::ostream& output_stream)
    {
        output_stream << "Configure Options\n"
                      << "0 - Back to main menu\n"
                      << "1 - Modify Maximum number of attempts per game\n"
                      << "2 - Modify Number of characters in a code\n"
                      << "3 - Modify Minimum allowed character\n"
                      << "4 - Modify Maximum allowed character\n"
                      << "5 - Save options\n"
                      << "6 - Load options\n"
                      << "What is your choice ? ";
    }

    // TODO: define the body of the functions declared in game_options.cpp

} // namespace bulls_and_cows
