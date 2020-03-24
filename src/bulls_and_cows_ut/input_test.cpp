
#include <bulls_and_cows_lib/input.hpp>
#include <catch2/catch.hpp>
#include <sstream>

// Examples of unit tests for the functions declared in input.hpp

TEST_CASE("TEST bulls_and_cows::ask_string")
{
    // ARRANGE
    std::stringstream input_stream{"something that the user has typed"};

    // ACT
    const std::string result = bulls_and_cows::ask_string(input_stream);

    // ASSERT
    REQUIRE(result == "something that the user has typed");
}

TEST_CASE("TEST bulls_and_cows::ask_int_or_default WHEN user does not type an integer number")
{
    // ARRANGE
    std::stringstream input_stream{"something that is not a number"};

    // ACT
    const int result = bulls_and_cows::ask_int_or_default(input_stream, -123);

    // ASSERT
    REQUIRE(result == -123);
}

TEST_CASE("TEST bulls_and_cows::ask_int_or_default WHEN user types an integer number")
{
    // ARRANGE
    std::stringstream input_stream{"42"};

    // ACT
    const int result = bulls_and_cows::ask_int_or_default(input_stream, -123);

    // ASSERT
    REQUIRE(result == 42);
}

TEST_CASE("TEST bulls_and_cows::ask_uint_or_default WHEN user does not type an integer number")
{
    // ARRANGE
    std::stringstream input_stream{"something that is not a number"};

    // ACT
    const unsigned int result = bulls_and_cows::ask_uint_or_default(input_stream, 987654321);

    // ASSERT
    REQUIRE(result == 987654321);
}

TEST_CASE("TEST bulls_and_cows::ask_uint_or_default WHEN user types an integer number")
{
    // ARRANGE
    std::stringstream input_stream{"42"};

    // ACT
    const unsigned int result = bulls_and_cows::ask_uint_or_default(input_stream, 0);

    // ASSERT
    REQUIRE(result == 42);
}

TEST_CASE("TEST bulls_and_cows::ask_char_or_default WHEN user does not type a character")
{
    // ARRANGE
    std::stringstream input_stream{"something that is not a single character"};

    // ACT
    const char result = bulls_and_cows::ask_char_or_default(input_stream, 'X');

    // ASSERT
    REQUIRE(result == 'X');
}

TEST_CASE("TEST bulls_and_cows::ask_char_or_default WHEN user types an integer number")
{
    // ARRANGE
    std::stringstream input_stream{"Z"};

    // ACT
    const char result = bulls_and_cows::ask_char_or_default(input_stream, '1');

    // ASSERT
    REQUIRE(result == 'Z');
}
