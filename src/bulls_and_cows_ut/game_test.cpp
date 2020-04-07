#include <bulls_and_cows_lib/game.hpp>
#include <bulls_and_cows_lib/game_options.hpp>
#include <catch2/catch.hpp>
#include <algorithm>
#include <numeric>
#include <sstream>



TEST_CASE("TEST bulls_and_cows::count_bulls_cows_without_double WHEN 1 bull and 2 cows")
{
	// ARRANGE
	
	const std::vector <char> secretCode = { 'A', 'B', 'C', 'D', 'E' };
	const std::vector <char> playerCode = { 'H', 'F', 'C', 'A', 'B' };

	


	// ACT
	std::vector<int> counter_bowls_cows(3);
	bulls_and_cows::FinalBoard current_attempt = bulls_and_cows::count_bulls_cows_without_double(secretCode, playerCode, current_attempt);

	// ASSERT
	REQUIRE(current_attempt.bulls == 1);
	REQUIRE(current_attempt.cows == 2);
}

TEST_CASE("TEST bulls_and_cows::count_bulls_cows_with_double WHEN 1 bull and 1 cow")
{
	// ARRANGE

	const std::string secretCode = { 'A', 'A', 'A', 'D', 'E' };
	const std::string playerCode = { 'H', 'A', 'C', 'E', 'B' };


	// ACT

	bulls_and_cows::FinalBoard current_attempt = bulls_and_cows::count_bulls_cows_with_double(secretCode, playerCode, current_attempt);

	// ASSERT
	REQUIRE(current_attempt.bulls == 1);
	REQUIRE(current_attempt.cows == 1);
}

TEST_CASE("TEST bulls_and_cows::conv_vector_to_string")
{

	//ARRANGE
	const std::vector <char> vector_to_convert = { 'A', 'B', 'C', 'D', 'E' };
	
	//ACT
	const std::string test = bulls_and_cows::conv_vector_to_string(vector_to_convert);

	//ASSERT
	REQUIRE(test == "ABCDE");


}

TEST_CASE("TEST bulls_and_cows::isContainedIn WHEN Char A is already in SecretCode vector")
{

	//ARRANGE
	const std::vector <char> secretCode = { 'A', 'B', 'C', 'D', 'E' };
	const char rand = 'A';

	//ACT
	const bool test = bulls_and_cows::isContainedIn(rand,secretCode);

	//ASSERT
	REQUIRE(test == true);

}

TEST_CASE("TEST bulls_and_cows::checkError WHEN carac = Z")
{

	//ARRANGE
	bulls_and_cows::GameOptions game_options;
	const char carac = 'Z';

	//ACT
	const bool test = bulls_and_cows::checkError(carac, game_options);
	

	//ASSERT
	REQUIRE(test == true);

}

TEST_CASE("TEST bulls_and_cows::secret_code_init size")
{

	//ARRANGE
	bulls_and_cows::GameOptions game_options;
	const std::vector <char> secretCode (game_options.number_of_characters_per_code);

	//ACT

	const std::vector<char> test = bulls_and_cows::secret_code_init_with_double(game_options);


	//ASSERT
	REQUIRE(test.size() == game_options.number_of_characters_per_code);

}

TEST_CASE("TEST bulls_and_cows::load_option_file")
{
	// ARRANGE
	bulls_and_cows::GameOptions game_options{};
	game_options.max_number_of_attempts = 5 ;
	game_options.number_of_characters_per_code = 3;
	game_options.minimum_allowed_character = 'A';
	game_options.maximum_allowed_character = 'C';
	

	// ACT
	bulls_and_cows::save_option_file(game_options);
	bulls_and_cows::load_option_file(game_options);

	// ASSERT
	
	REQUIRE(game_options.max_number_of_attempts == 5);
	REQUIRE(game_options.number_of_characters_per_code == 3);
	REQUIRE(game_options.minimum_allowed_character == 'A');
	REQUIRE(game_options.maximum_allowed_character == 'C');
}

TEST_CASE("TEST bulls_and_cows::ask_option_menu_choice WHEN choice is 1")
{
	// ARRANGE
	std::stringstream input_stream{ "1" };

	// ASK
	const bulls_and_cows::OptionMenuChoice choice = bulls_and_cows::ask_option_menu_choice(input_stream);

	// ASSERT
	REQUIRE(choice == bulls_and_cows::OptionMenuChoice::NumberOfCharacters);
}

TEST_CASE("TEST bulls_and_cows::ask_main_menu_choice WHEN choice is 3")
{
	// ARRANGE
	std::stringstream input_stream{ "3" };

	// ASK
	const bulls_and_cows::ConfigureOptions choice = bulls_and_cows::ask_configuration_menu_choice(input_stream);

	// ASSERT
	REQUIRE(choice == bulls_and_cows::ConfigureOptions::SaveOption);
}
