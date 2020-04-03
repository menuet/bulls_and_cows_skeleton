#include <bulls_and_cows_lib/game.hpp>
#include <catch2/catch.hpp>
#include <string>

TEST_CASE("TEST bulls_and_cows::checkSameCharInString when we have duplicates")
{
    // ARRANGE
    const std::string code = "ABCDE";
    const char charCode = 'B';

    // ACT
    const bool resultCheckDoublons = bulls_and_cows::checkSameCharInString(code, charCode);

    // ASSERT
    REQUIRE(resultCheckDoublons == true);
}

TEST_CASE("TEST bulls_and_cows::checkSameCharInString when we have no duplicates")
{
    // ARRANGE
    const std::string code = "ABCDE";
    const char charCode = 'H';

    // ACT
    const bool resultCheckDoublons = bulls_and_cows::checkSameCharInString(code, charCode);

    // ASSERT
    REQUIRE(resultCheckDoublons == false);
}

TEST_CASE("TEST bulls_and_cows::giveCode")
{
    // ARRANGE
    const bulls_and_cows::GameOptions& game_options{};

    // ACT
    const std::string code = bulls_and_cows::giveCode(game_options);

    // ASSERT
    REQUIRE(code.size() == game_options.number_of_characters_per_code);
    for (const char c : code)
    {
        REQUIRE(c >= game_options.minimum_allowed_character);
        REQUIRE(c <= game_options.maximum_allowed_character);
    }
}


TEST_CASE("TEST bulls_and_cows::checkDoublonsString when we have duplicates")
{
    // ARRANGE
    const std::string code = "AABCD";

    // ACT
    const bool resultCheckDoublonsString = bulls_and_cows::checkDoublonsString(code);

    // ASSERT
    REQUIRE(resultCheckDoublonsString == true);
}

TEST_CASE("TEST bulls_and_cows::checkDoublonsString when we have no duplicates")
{
    // ARRANGE
    const std::string code = "ABCDE";

    // ACT
    const bool resultCheckDoublonsString = bulls_and_cows::checkDoublonsString(code);

    // ASSERT
    REQUIRE(resultCheckDoublonsString == false);
}

TEST_CASE("TEST bulls_and_cows::checkErrorAttemps, good code")
{
    // ARRANGE
    const std::string code = "ABCDE";
    const bulls_and_cows::GameOptions& game_options{};

    // ACT
    const bool resultCheckErrorAttemps = bulls_and_cows::checkErrorAttemps(code, game_options);

    // ASSERT
    REQUIRE(resultCheckErrorAttemps == true);
}

TEST_CASE("TEST bulls_and_cows::checkErrorAttemps, too long")
{
    // ARRANGE
    const std::string code = "ABCDEFGH";
    const bulls_and_cows::GameOptions& game_options{};

    // ACT
    const bool resultCheckErrorAttemps = bulls_and_cows::checkErrorAttemps(code, game_options);

    // ASSERT
    REQUIRE(resultCheckErrorAttemps == false);
}

TEST_CASE("TEST bulls_and_cows::checkErrorAttemps, T is a wrong letter")
{
    // ARRANGE
    const std::string code = "ABTCD";
    const bulls_and_cows::GameOptions& game_options{};

    // ACT
    const bool resultCheckErrorAttemps = bulls_and_cows::checkErrorAttemps(code, game_options);

    // ASSERT
    REQUIRE(resultCheckErrorAttemps == false);
}

TEST_CASE("TEST bulls_and_cows::giveCowsNumber")
{
    // ARRANGE
    const std::string secretCodeUser = "ABCDE";
    const std::string code = "DHGAE";

    // ACT
    const int resultCowsNumber = bulls_and_cows::giveCowsNumber(secretCodeUser, code);

    // ASSERT
    REQUIRE(resultCowsNumber == 2);
}

TEST_CASE("TEST bulls_and_cows::giveBullsNumber")
{
    // ARRANGE
    const std::string secretCodeUser = "ABCDE";
    const std::string code = "DHGAE";

    // ACT
    const int resultBullsNumber = bulls_and_cows::giveBullsNumber(secretCodeUser, code);

    // ASSERT
    REQUIRE(resultBullsNumber == 1);
}

TEST_CASE("TEST bulls_and_cows::checkWin, win")
{
    // ARRANGE
    const std::string secretCodeUser = "ABCDE";
    const std::string code = "ABCDE";

    // ACT
    const bool resultCheckWin = bulls_and_cows::checkWin(secretCodeUser, code);

    // ASSERT
    REQUIRE(resultCheckWin == true);
}

TEST_CASE("TEST bulls_and_cows::checkWin, lose")
{
    // ARRANGE
    const std::string secretCodeUser = "ABCDE";
    const std::string code = "DHGAE";

    // ACT
    const bool resultCheckWin = bulls_and_cows::checkWin(secretCodeUser, code);

    // ASSERT
    REQUIRE(resultCheckWin == false);
}