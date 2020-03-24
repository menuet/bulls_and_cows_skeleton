
#include <bulls_and_cows_lib/main_menu.hpp>
#include <catch2/catch.hpp>
#include <sstream>

// Examples of unit tests for the functions declared in main_menu.hpp

TEST_CASE("TEST bulls_and_cows::display_main_menu")
{
    // ARRANGE
    std::stringstream output_stream;

    // ACT
    bulls_and_cows::display_main_menu(output_stream);

    // ASSERT
    const std::string output_result = output_stream.str();
    REQUIRE(output_result ==
            "Welcome to Bulls And Cows\n"
            "0 - Quit\n"
            "1 - Play against the computer\n"
            "2 - Watch computer playing against itself\n"
            "3 - Configure options\n"
            "What is your choice ? ");
}

TEST_CASE("TEST bulls_and_cows::ask_main_menu_choice WHEN choice is 2")
{
    // ARRANGE
    std::stringstream input_stream{"2"};

    // ASK
    const bulls_and_cows::MainMenuChoice choice = bulls_and_cows::ask_main_menu_choice(input_stream);

    // ASSERT
    REQUIRE(choice == bulls_and_cows::MainMenuChoice::ComputerPlaysAgainstComputer);
}
