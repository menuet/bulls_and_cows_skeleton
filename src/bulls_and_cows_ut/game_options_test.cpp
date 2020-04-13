
#include <bulls_and_cows_lib/game_options.hpp>
#include <catch2/catch.hpp>
#include <sstream>

// Examples of unit tests for the functions declared in game_options.hpp
// These unit tests are disabled because you first need to define the tested functions in game_options.cpp

TEST_CASE("TEST bulls_and_cows::printOptions")
{
    // ARRANGE
    const bulls_and_cows::GameOptions game_options{};
    std::stringstream output_stream;

    // ACT
    bulls_and_cows::printOptions(game_options, output_stream);

    // ASSERT
    const std::string output_result = output_stream.str();
    REQUIRE(output_result ==
            "minimum_allowed_character=A\n"
            "maximum_allowed_character=H\n"
            "number_of_characters_per_code=4\n"
            "max_number_of_attempts=12\n"
            "save_game=0\n"
            "accept_doublons=1\n");
}

TEST_CASE("TEST bulls_and_cows::loadGame_options")
{
    // ARRANGE
    bulls_and_cows::GameOptions game_options{};
    // mon fichier possède A / H / 6 / 12 / false / false
    // ACT
    bulls_and_cows::loadGame_options(game_options);

    // ASSERT
    REQUIRE(game_options.minimum_allowed_character == 'A');
    REQUIRE(game_options.maximum_allowed_character == 'H');
    REQUIRE(game_options.number_of_characters_per_code == 6);
    REQUIRE(game_options.max_number_of_attempts == 12);
    REQUIRE(game_options.save_game == false);
    REQUIRE(game_options.accept_doublons == true);
}