
#include <bulls_and_cows_lib/game_solver.hpp>
#include <catch2/catch.hpp>
#include <algorithm>
#include <numeric>

// Examples of unit tests for the functions declared in game_solver.hpp
// These unit tests are disabled because you first need to define the tested functions in game_solver.cpp



static unsigned int computed_value(const bulls_and_cows::GameOptions game_options, const bulls_and_cows::Code& code)
{
    const unsigned int characters_range_size =
        static_cast<unsigned char>(game_options.maximum_allowed_character - game_options.minimum_allowed_character + 1);
    unsigned int value = 0U;
    unsigned int exp = 1U;
    for (char c : code.value)
    {
        value += static_cast<unsigned int>(c - game_options.minimum_allowed_character) * exp;
        exp *= characters_range_size;
    }
    return value;
}

TEST_CASE("TEST bulls_and_cows::generate_all_possible_codes")
{
    // ARRANGE
    bulls_and_cows::GameOptions game_options;
    game_options.minimum_allowed_character = 'A';
    game_options.maximum_allowed_character = 'C';
    game_options.number_of_characters_per_code = 3;

    // ACT
    const auto possible_solutions = bulls_and_cows::generate_all_possible_codes(game_options);

    // ASSERT
    unsigned int expected_size = game_options.number_of_characters_per_code;
    for (auto c = game_options.minimum_allowed_character; c != game_options.maximum_allowed_character; ++c)
        expected_size *= game_options.number_of_characters_per_code;
    REQUIRE(possible_solutions.codes.size() == expected_size);
    auto iter = possible_solutions.codes.begin();
    auto value = computed_value(game_options, *iter);
    REQUIRE(value == 0);
    for (++iter; iter != possible_solutions.codes.end(); ++iter)
    {
        const auto next_value = computed_value(game_options, *iter);
        REQUIRE(next_value == value + 1);
        value = next_value;
    }
}

TEST_CASE("TEST bulls_and_cows::pick_random_attempt")
{
    // ARRANGE
    bulls_and_cows::PossibleSolutions possible_solutions{{{"ABCDE"}, {"DEFGH"}, {"HABCD"}}};

    // ACT
    const auto code = bulls_and_cows::pick_random_attempt(possible_solutions);

    // ASSERT
    REQUIRE((code.value == "ABCDE" || code.value == "DEFGH" || code.value == "HABCD"));
}

TEST_CASE("TEST bulls_and_cows::remove_incompatible_codes_from_possible_solutions")
{
    // ARRANGE
    bulls_and_cows::PossibleSolutions possible_solutions{{{"ABCDE"}, {"DEFGH"}, {"HABCD"}}};
    const bulls_and_cows::AttemptAndFeedback attempt_and_feedback{{"DABEC"}, {2, 2}};

    // ACT
    bulls_and_cows::remove_incompatible_codes_from_possible_solutions(attempt_and_feedback, possible_solutions);

    // ASSERT
    REQUIRE(possible_solutions.codes.size() == 1);
    REQUIRE(possible_solutions.codes[0].value == "HABCD");
}


