
#include <bulls_and_cows_lib/game_options.hpp>
#include <catch2/catch.hpp>
#include <sstream>

// Examples of unit tests for the functions declared in game_options.hpp
// These unit tests are disabled because you first need to define the tested functions in game_options.cpp


/*
TEST_CASE("TEST bulls_and_cows::display_game_options")
{
    // ARRANGE
    const bulls_and_cows::GameOptions game_options{};
    std::stringstream output_stream;

    // ACT
    bulls_and_cows::display_game_options(output_stream, game_options);

    // ASSERT
    const std::string output_result = output_stream.str();
    REQUIRE(output_result ==
            "Here are the current game_options:\n"
            "Maximum number of attempts per game: 12\n"
            "Number of characters in a code: 5\n"
            "Range of allowed characters: from 'A' to 'H'\n");
}

TEST_CASE("TEST bulls_and_cows::display_game_options_menu")
{
    // ARRANGE
    std::stringstream output_stream;

    // ACT
    bulls_and_cows::display_game_options_menu(output_stream);

    // ASSERT
    const std::string output_result = output_stream.str();
    REQUIRE(output_result ==
            "Configure Options\n"
            "0 - Back to main menu\n"
            "1 - Modify Maximum number of attempts per game\n"
            "2 - Modify Number of characters in a code\n"
            "3 - Modify Minimum allowed character\n"
            "4 - Modify Maximum allowed character\n"
            "5 - Save options\n"
            "6 - Load options\n"
            "What is your choice ? ");
}

TEST_CASE("TEST bulls_and_cows::ask_game_options_menu_choice WHEN choice is 2")
{
    // ARRANGE
    std::stringstream input_stream{"2"};

    // ASK
    const bulls_and_cows::GameOptionsMenuChoice choice = bulls_and_cows::ask_game_options_menu_choice(input_stream);

    // ASSERT
    REQUIRE(choice == bulls_and_cows::GameOptionsMenuChoice::ModifyNumberOfCharactersPerCode);
}
*/
/*
TEST_CASE("TEST bulls_and_cows::save_game_options")
{
    // ARRANGE
    const bulls_and_cows::GameOptions game_options{};
    std::stringstream output_stream;

    // ACT
    const bool result = bulls_and_cows::save_game_options(output_stream, game_options);

    // ASSERT
    REQUIRE(result);
    const std::string output_result = output_stream.str();
    REQUIRE(output_result ==
            "max_number_of_attempts=12\n"
            "number_of_characters_per_code=5\n"
            "minimum_allowed_character=A\n"
            "maximum_allowed_character=H\n");
}
*/
TEST_CASE("TEST bulls_and_cows::load_game_options")
{
    // ARRANGE
    bulls_and_cows::GameOptions game_options{};
    std::stringstream input_stream{
        "max_number_of_attempts=5\n"
        "number_of_characters_per_code=3\n"
        "minimum_allowed_character=1\n"
        "maximum_allowed_character=8\n"};

    // ACT
    const bool result = bulls_and_cows::load_game_options(input_stream, game_options);

    // ASSERT
    REQUIRE(result);
    REQUIRE(game_options.max_number_of_attempts == 5);
    REQUIRE(game_options.number_of_characters_per_code == 3);
    REQUIRE(game_options.minimum_allowed_character == '1');
    REQUIRE(game_options.maximum_allowed_character == '8');
}

