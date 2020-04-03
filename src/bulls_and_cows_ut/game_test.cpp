
#include <bulls_and_cows_lib/game.hpp>
#include <catch2/catch.hpp>
#include <sstream>

TEST_CASE("TEST bulls_and_cows::generate_secret_code")
{
    for (unsigned int i = 0U; i != 1000; ++i)
    {
	    //ARRANGE
        const bulls_and_cows::GameOptions game_options{};

	    //ACT
        const bulls_and_cows::Code result = bulls_and_cows::generate_secret_code(game_options);

	    //ASSERT
        REQUIRE(result.value.size() == game_options.number_of_characters_per_code);
        for (unsigned int k = 0U; k < result.value.size(); ++k)
        {
            REQUIRE(result.value[k] <= game_options.maximum_allowed_character);
            REQUIRE(result.value[k] >= game_options.minimum_allowed_character);
        }
    }
}

TEST_CASE("TEST bulls_and_cows::count_bull WHEN 2 bulls")
{
    //ARRANGE
    bulls_and_cows::Code attempt;
    bulls_and_cows::Code code;
    attempt.value = "ABCDE";
    code.value = "ACFBE";

    //ACT
    const unsigned int result = bulls_and_cows::count_bull(attempt, code);

    //ASSERT 
    REQUIRE(result == 2);
}

TEST_CASE("TEST bulls_and_cows::count_cow WHEN 3 cows")
{
    // ARRANGE
    bulls_and_cows::Code attempt;
    bulls_and_cows::Code code;
    attempt.value = "ABCDE";
    code.value = "ACFBD";

    // ACT
    const unsigned int result = bulls_and_cows::count_cow(attempt, code);

    // ASSERT
    REQUIRE(result == 3);
}

TEST_CASE("TEST bulls_and_cows::count_cow WHEN 1 cows and duplicates with 2 bulls")
{
    // ARRANGE
    bulls_and_cows::Code attempt;
    bulls_and_cows::Code code;
    attempt.value = "ABCAE";
    code.value = "AABAB";

    // ACT
    const unsigned int result = bulls_and_cows::count_cow(attempt, code);

    // ASSERT
    REQUIRE(result == 1);
}

TEST_CASE("TEST bulls_and_cows::count_cow WHEN 0 cows and duplicates with 3 bulls")
{
    // ARRANGE
    bulls_and_cows::Code attempt;
    bulls_and_cows::Code code;
    attempt.value = "EEDC";
    code.value = "DEDC";

    // ACT
    const unsigned int result = bulls_and_cows::count_cow(attempt, code);

    // ASSERT
    REQUIRE(result == 0);
}

TEST_CASE("TEST bulls_and_cows::check_duplicates WHEN there are duplicates")
{
    //ARRANGE
    const std::string code = "ABACE";

    //ACT
    const bool result = bulls_and_cows::check_duplicates(code);

    //ASSERT
    REQUIRE(result);
}

TEST_CASE("TEST bulls_and_cows::check_duplicates WHEN there is no duplicate")
{
    // ARRANGE
    const std::string code = "ABDCE";

    // ACT
    const bool result = bulls_and_cows::check_duplicates(code);

    // ASSERT
    REQUIRE(!result);
}

TEST_CASE("TEST bulls_and_cows::check_input WHEN the string (the attempt) is too short or too long")
{
    //ARRANGE
    const std::string code1 = "ABC";
    const std::string code2 = "ABCDEF";
    const bulls_and_cows::GameOptions game_options{};

    //ACT
    const bulls_and_cows::CheckInput result1 = bulls_and_cows::check_input(code1, game_options);
    const bulls_and_cows::CheckInput result2 = bulls_and_cows::check_input(code2, game_options);

    //ASSERT
    REQUIRE(result1 == bulls_and_cows::CheckInput::WrongNumberChars);
    REQUIRE(result2 == bulls_and_cows::CheckInput::WrongNumberChars);
}

TEST_CASE("TEST bulls_and_cows::check_input WHEN the string (the attempt) contains a character out of range")
{
    // ARRANGE
    const std::string code = "ABCDZ";
    bulls_and_cows::GameOptions game_options{};

    // ACT
    const bulls_and_cows::CheckInput result = bulls_and_cows::check_input(code, game_options);

    // ASSERT
    REQUIRE(result == bulls_and_cows::CheckInput::CharacterOutOfRange);
}

TEST_CASE("TEST bulls_and_cows::check_input WHEN the string (the attempt) contains duplicates")
{
    // ARRANGE
    const std::string code = "ABCDA";
    bulls_and_cows::GameOptions game_options{};
    game_options.allow_duplicate = false;

    // ACT
    const bulls_and_cows::CheckInput result = bulls_and_cows::check_input(code, game_options);

    // ASSERT
    REQUIRE(result == bulls_and_cows::CheckInput::Duplicate);
}

TEST_CASE("TEST bulls_and_cows::check_input WHEN the string (the attempt) is valid")
{
    // ARRANGE
    const std::string code = "ABCDE";
    bulls_and_cows::GameOptions game_options{};

    // ACT
    const bulls_and_cows::CheckInput result = bulls_and_cows::check_input(code, game_options);

    // ASSERT
    REQUIRE(result == bulls_and_cows::CheckInput::Valid);
}

TEST_CASE("TEST bulls_and_cows::check_attempt WHEN the attempt is not in the historic")
{
    //ARRANGE
    bulls_and_cows::Code attempt;
    attempt.value = "ABCDE";

    //Initialising 2 attempts in historic
    bulls_and_cows::Code historic_attempt1;
    historic_attempt1.value = "ACDEB";

    bulls_and_cows::Code historic_attempt2;
    historic_attempt1.value = "DEBCA";

    bulls_and_cows::AttemptBullsCows att1;
    att1.attempt = historic_attempt1;

    bulls_and_cows::AttemptBullsCows att2;
    att2.attempt = historic_attempt2;

    bulls_and_cows::Historic historic;
    historic.value.push_back(att1);
    historic.value.push_back(att2);

    //ACT
    const bool result = bulls_and_cows::check_attempt(attempt, historic);

    //ASSERT
    REQUIRE(result);
}

TEST_CASE("TEST bulls_and_cows::check_attempt WHEN the attempt is already in the historic")
{
    // ARRANGE
    bulls_and_cows::Code attempt;
    attempt.value = "DEBCA";

    // Initialising 2 attempts in historic
    bulls_and_cows::Code historic_attempt1;
    historic_attempt1.value = "ACDEB";

    bulls_and_cows::Code historic_attempt2;
    historic_attempt1.value = "DEBCA";

    bulls_and_cows::AttemptBullsCows att1;
    att1.attempt = historic_attempt1;

    bulls_and_cows::AttemptBullsCows att2;
    att2.attempt = historic_attempt2;

    bulls_and_cows::Historic historic;
    historic.value.push_back(att1);
    historic.value.push_back(att2);

    // ACT
    const bool result = bulls_and_cows::check_attempt(attempt, historic);

    // ASSERT
    REQUIRE(!result);
}