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

    // std::ofstream game_options_file{"game_options.txt",std::ios::app};
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

    // std::string split implementation by using delimiter as a character.
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
            // EOF it is end of file.
            while (input_file_stream.peek() != EOF)
            {
                std::getline(input_file_stream, sentence);
                // std::cout << "\n" << sentence;
            }
            // std::cout << "\nthe last :" << sentence << "\n";

            // we split our string with delimiter ','
            std::vector<std::string> splittedStrings = split(sentence, ',');

            // pointer to the first element
            std::string* pos = splittedStrings.data();

            // we attribute the the game options the new options
            game_options.max_number_of_attempts = atoi(pos[0].c_str());
            game_options.number_of_characters_per_code = atoi(pos[1].c_str());
            game_options.minimum_allowed_character = *pos[2].c_str();
            game_options.maximum_allowed_character = *pos[3].c_str();

            // free the memory
            pos = nullptr;
            delete pos;

            return true; // load the file
        }
        return false; // Unable to open file
    }

} // namespace bulls_and_cows
