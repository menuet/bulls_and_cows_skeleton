
#pragma once
#include "board.hpp"
#include <iostream>
#include "game_options.hpp"


namespace bulls_and_cows {

    // Display the main menu of the program
    void display_main_menu(std::ostream& output_stream);


    enum class MainMenuChoice
    {
        Error = -1,
        Quit = 0,
        UserPlaysAgainstComputer = 1,
        ComputerPlaysAgainstComputer = 2,
        ConfigureOptions = 3,
    };

    enum class MainMenuChoice1
    {
        Error = -1,
        Quit = 0,
        RandomGenerator = 1,
        UserGenerated = 2,
    };



    // Ask the user to select an option of the menu
    MainMenuChoice ask_main_menu_choice(std::istream& input_stream);

    // Ask the user to select an option of the menu
    MainMenuChoice1 ask_main_random_or_typed(std::istream& input_stream);



} // namespace bulls_and_cows
