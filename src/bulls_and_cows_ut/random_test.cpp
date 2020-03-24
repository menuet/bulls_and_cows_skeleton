
#include <bulls_and_cows_lib/random.hpp>
#include <catch2/catch.hpp>

// Examples of unit tests for the functions declared in random.hpp

TEST_CASE("TEST bulls_and_cows::generate_random_integer")
{
    for (unsigned int i = 0U; i != 1000; ++i)
    {
        // ACT
        const auto number = bulls_and_cows::generate_random_integer(-15, 42);

        // ASSERT
        REQUIRE(number >= -15);
        REQUIRE(number <= 42);
    }
}

TEST_CASE("TEST bulls_and_cows::generate_random_character")
{
    for (unsigned int i = 0U; i != 1000; ++i)
    {
        // ACT
        const auto character = bulls_and_cows::generate_random_character('A', 'E');

        // ASSERT
        REQUIRE(character >= 'A');
        REQUIRE(character <= 'E');
    }
}
