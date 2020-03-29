#include <bulls_and_cows_lib/game.hpp>
#include <catch2/catch.hpp>
#include <algorithm>
#include <numeric>

TEST_CASE("TEST bulls_and_cows::compare_attempt_with_secret_code WHEN 1 bull and 2 cows")
{
	// ARRANGE
	
	const std::vector <char> secretCode = { 'A', 'B', 'C', 'D', 'E' };
	const std::vector <char> playerCode = { 'H', 'F', 'C', 'A', 'B' };


	// ACT
	std::vector<int> counter_bowls_cows(3);
	counter_bowls_cows = bulls_and_cows::count_true_false(secretCode, playerCode, counter_bowls_cows);

	// ASSERT
	REQUIRE(counter_bowls_cows[1] == 1);
	REQUIRE(counter_bowls_cows[2] == 2);
}