
#include <bulls_and_cows_lib/game_options.hpp>
#include <catch2/catch.hpp>
#include <sstream>

// Unit tests for the functions declared in game_options.hpp

TEST_CASE("TEST bulls_and_cows::display_game_options")
{
    // ARRANGE
    bulls_and_cows::GameOptions game_options{};
    game_options.allow_duplicate = false;
    std::stringstream output_stream;

    // ACT
    bulls_and_cows::display_game_options(output_stream, game_options);

    // ASSERT
    const std::string output_result = output_stream.str();
    REQUIRE(output_result ==
            "\nThe number of characters in the code is 5"
            "\nThe maximum number of attempts allowed is 12"
            "\nThere are characters between A and H\n"
            "Duplicates are not allowed\n");
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
            "0> Back to menu\n"
            "1> Modifiy the maximum number of attempts\n"
            "2> Modify the number of characters per code\n"
            "3> Modify the minimum allowed character\n"
            "4> Modify the maximum allowed character\n"
            "5> Save the options\n"
            "6> Load the options\n"
            "7> Allow duplicates in the code\n"
            "Enter your choice\n");
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

TEST_CASE("TEST bulls_and_cows::adjust_char_number WHEN code length is too long and duplicates not allowed")
{
    //ARRANGE
    bulls_and_cows::GameOptions game_options{};
    game_options.number_of_characters_per_code = 10;
    game_options.allow_duplicate = false;
    //ASK
    const bool result = bulls_and_cows::adjust_char_number(game_options);

    //ASSERT
    REQUIRE(result);
    REQUIRE(game_options.number_of_characters_per_code == 8);
}

TEST_CASE("TEST bulls_and_cows::adjust_char_number WHEN code length is too long and duplicates allowed")
{
    // ARRANGE
    bulls_and_cows::GameOptions game_options{};
    game_options.number_of_characters_per_code = 10;
    game_options.allow_duplicate = 1;

    // ASK
    const bool result = bulls_and_cows::adjust_char_number(game_options);

    // ASSERT
    REQUIRE(!result);
    REQUIRE(game_options.number_of_characters_per_code == 10);
}

TEST_CASE("TEST bulls_and_cows::adjust_char_number WHEN all is good")
{
    // ARRANGE
    bulls_and_cows::GameOptions game_options{};

    // ASK
    const bool result = bulls_and_cows::adjust_char_number(game_options);

    // ASSERT
    REQUIRE(!result);
    REQUIRE(game_options.number_of_characters_per_code == 5);
}

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
}*/


