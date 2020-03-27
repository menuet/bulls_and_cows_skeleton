
#include "game_options.hpp"
#include "input.hpp"
#include <iostream>
#include <process.h>
#include <sstream>
#include <vector>

namespace bulls_and_cows {

    // TODO: define the body of the functions declared in game_options.cpp

    void display_game_options(std::ostream& output_stream, const GameOptions& game_options)
    {
        output_stream << "Here are the current game_options:\n"
                         "Maximum number of attempts per game: "
                      << game_options.max_number_of_attempts
                      << "\n"
                         "Number of characters in a code: "
                      << game_options.number_of_characters_per_code
                      << "\n"
                         "Range of allowed characters: from '"
                      << game_options.minimum_allowed_character << "' to '" << game_options.maximum_allowed_character
                      << "'\n";
    }

    void display_game_options_menu(std::ostream& output_stream)
    {
        output_stream << "Configure Options\n"
                         "0 - Back to main menu\n"
                         "1 - Modify Maximum number of attempts per game\n"
                         "2 - Modify Number of characters in a code\n"
                         "3 - Modify Minimum allowed character\n"
                         "4 - Modify Maximum allowed character\n"
                         "5 - Save options\n"
                         "6 - Load options\n"
                         "What is your choice ? ";
    }

    void option_ModifyMaximumNumberOfAttempts(GameOptions& game_options)
    {

        std::cout << "Enter the Maximum Number of Attempts (maximum allowed is 12): ";
        const int user_maxAttempts = ask_int_or_default(std::cin, -1);
        if (user_maxAttempts < 1 || user_maxAttempts > 12)
        {
            std::cout << "\nPlease enter a correct Maximum Number of Attempts (maximum allowed is 12, minimum "
                         "is 1) \n";
        }
        else
        {
            game_options.max_number_of_attempts = user_maxAttempts;
        }
    }

    void option_ModifyNumberOfCharactersPerCode(GameOptions& game_options)
    {

        std::cout << "Enter the Number of characters Per Code (maximum allowed is 6): ";
        const int user_nbChara = ask_int_or_default(std::cin, -1);
        if (user_nbChara < 1 || user_nbChara > 6)
        {
            std::cout << "\nPlease enter a correct Number of characters Per Code (maximum allowed is 6) \n";
        }
        else
        {
            game_options.number_of_characters_per_code = user_nbChara;
        }
    }

    void option_ModifyMinimumAllowedCharacter(GameOptions& game_options)
    {
        std::cout << "Enter the Minimum allowed character to modify the previous one: ";
        const char user_miniChara = ask_char_or_default(std::cin, 0);
        if (user_miniChara > game_options.maximum_allowed_character)
        {
            std::cout << "\nPlease enter a correct Minimum allowed character (inferior than the Maximum allowed "
                         "character) \n";
        }
        else
        {
            game_options.minimum_allowed_character = user_miniChara;
        }
    }

    void option_ModifyMaximumAllowedCharacter(GameOptions& game_options)
    {
        std::cout << "Enter the Maximum allowed character to modify the previous one: ";
        const char user_maxiChara = ask_char_or_default(std::cin, 0);
        if (user_maxiChara < game_options.minimum_allowed_character)
        {
            std::cout << "\nPlease enter a correct Maximum allowed character (superior than the Minimum allowed "
                         "character) \n";
        }
        else
        {
            game_options.maximum_allowed_character = user_maxiChara;
        }
    }

    void option_SaveOptions(std::ostream& output_file_stream, const GameOptions& game_options)
    {

        bool saved = save_game_options(output_file_stream, game_options);
        if (saved)
        {
            std::cout << "Success: the game options are saved correctly\n";
        }
        else
        {
            std::cout << "Error: the game options are not saved correctly\n";
        }
    }

    void option_LoadOptions(std::istream& input_file_stream, GameOptions& game_options)
    {

        bool loaded = false;
        loaded = load_game_options(input_file_stream, game_options);
        if (loaded)
        {
            std::cout << "Success: the game options are loaded correctly\n";
        }
        else
        {
            std::cout << "Error: the game options are not loaded correctly\n";
        }
    }

    // Ask the user to select an option of the menu
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

    bool save_game_options(std::ostream& output_file_stream, const GameOptions& game_options)
    {
        if (!output_file_stream)
        {
            std::cerr << "Error: could not create or open the file\n";
            return false;
        }

        // we write in the file the information this way: 12,5,A,H
        output_file_stream << game_options.max_number_of_attempts << "," << game_options.number_of_characters_per_code
                           << "," << game_options.minimum_allowed_character << ","
                           << game_options.maximum_allowed_character << "\n";
        return true;
    }

    // split implementation by using delimiter as a character.
    std::vector<std::string> split(std::string strToSplit, char delimeter)
    {
        std::stringstream ss(strToSplit);
        std::string item;
        std::vector<std::string> splittedStrings;
        while (std::getline(ss, item, delimeter))
        {
            splittedStrings.push_back(item);
        }
        return splittedStrings;
    }

    bool load_game_options(std::istream& input_file_stream, GameOptions& game_options)
    {
        if (input_file_stream)
        {
            std::string sentence = "";
            //EOF it is end of file. We read each line with getline so that the last getline that we will do will put into "sentence" the last ligne in the file with content
            while (input_file_stream.peek() != EOF)
            {
                std::getline(input_file_stream, sentence);
            }

            int i = 0;
            std::string maxAttempts{};

            while (i < sentence.size() && sentence[i] != ',')
            {
                maxAttempts += sentence[i];
                i++;
            }
            game_options.max_number_of_attempts = atoi(maxAttempts.c_str());
            game_options.number_of_characters_per_code = static_cast<unsigned int>(sentence[i + 1])-48;
            game_options.minimum_allowed_character = sentence[i + 3];
            game_options.maximum_allowed_character = sentence[i + 5];

            return true; // load the file
        }
        return false; // Unable to open file
    }

} // namespace bulls_and_cows
