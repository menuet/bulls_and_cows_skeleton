#include "board.hpp"
#include "random.hpp"
#include "input.hpp"
#include <algorithm>
#include <vector>

namespace bulls_and_cows {

	// TODO: define the body of the functions declared in board.cpp
	// Create a board and with a new random secret code composed of allowed characters
	Board create_board(const GameOptions& game_options)
	{
		Board test{}; // creation d'une variable test de type board
		char new_char;
		for (unsigned int i = 0; i < game_options.number_of_characters_per_code; i++)
		{
			new_char = generate_random_character(game_options.minimum_allowed_character, game_options.maximum_allowed_character);
			test.secret_code.value.push_back(new_char);
		}
		return test;
	}

	//taille du code secret et comprise entre le maximum et minimum allowed character
	bool validate_attempt(const GameOptions& game_options, const Code& attempt)
	{
		if (attempt.value.size() != game_options.number_of_characters_per_code)   // test pour voir de la taille du code entré
		{
			return false;
		}
		for (const char attempt_char : attempt.value)  //tester si les caractere de la tentatives sont compris entre les limites
		{
			if (attempt_char > game_options.maximum_allowed_character || attempt_char < game_options.minimum_allowed_character)
			{
				return false; // faux si le nombre de caratere ne correspond pas.
			}
		}
		return true; // vrai si ca correspond bien a la taille du secret code.

	}

	// verifier le nombre de charactere du code du joueur est bon
	Feedback compare_attempt_with_secret_code(Code attempt, Code secret_code) // comparer les 2 codes
	{
		Feedback feedback{};

		for (unsigned i = 0; i < attempt.value.size(); i++)
		{
			if (attempt.value[i] == secret_code.value[i])
			{
				feedback.bulls++;
				secret_code.value.replace(i, 1, "?");
				attempt.value.replace(i, 1, "!");
			}

		}

		for (auto a : attempt.value)

		{
			auto iter = std::find(secret_code.value.begin(), secret_code.value.end(), a);
			if (iter != secret_code.value.end())
			{

				feedback.cows++;
				*iter = '?';
			}
		}

		return feedback;
	}

	//voir si le jeu est fini ou pas, on effectue un test, et si le code est bon, le jeu est fini
	bool is_end_of_game(const GameOptions& game_options, const Board& board)
	{
		// Comparer si le nombre de tentative est egal au nombre max autorisée
		if (game_options.max_number_of_attempts != board.attempts_and_feedbacks.size())
		{
			return false; // si faux renvoie false
		}

		return true; // si oui renvoie true
	}

	//voir si la derniere tentative est vrai
	bool is_win(const GameOptions& game_options, const Board& board)
	{

		for (AttemptAndFeedback tempo : board.attempts_and_feedbacks)
		{
			if (tempo.feedback.bulls == game_options.number_of_characters_per_code)
			{
				return true; // retourne vrai si la derniere tentavie est vrai
			}
		}
		return false; // retourne faux si la tentative est fausse

	}

	// Afficher le code secret + liste des tentatives.
	void display_board(std::ostream& output_stream, const GameOptions& game_options, const Board& board)
	{

		Code secret{};
		const char star = '-';
		if (is_win(game_options, board) || is_end_of_game(game_options, board))
		{
			secret.value = board.secret_code.value;
		}

		else
		{
			for (unsigned int i = 0; i < game_options.number_of_characters_per_code; i++)
			{
				secret.value.push_back(star);
				secret.value.push_back(' ');
			}
		}

		output_stream << "----------------------------\n"
			"| SECRET"
			<< secret.value
			<< "|                        | \n"
			"----------------------------------|\n"
			"| ATTEMPTS       | bulls   |  cows|  \n"
			"-----------------------------------| \n";
		for (auto element : board.attempts_and_feedbacks)
		{
			output_stream << "| " << element.attempt.value << "\t\t | " << element.feedback.bulls << "\t   | "
				<< element.feedback.cows << "\t   | \n";
		}
		output_stream << "-------------------\n";

	}

	Code ask_attempt(std::ostream& output_stream, std::istream& input_stream, const GameOptions& game_options, const Board& board)
	{
		Code attempt{};
		auto nb_attempt = board.attempts_and_feedbacks.size() + 1;
		unsigned int nb_char = game_options.number_of_characters_per_code;
		const char max = game_options.maximum_allowed_character;
		const char min = game_options.minimum_allowed_character;



		output_stream << "Try again \n this is your attempt: " << nb_attempt << "(enter " << nb_char << " different characters between '" << min
			<< "' and '" << max << "'): ";
		attempt.value = ask_string(input_stream);
		return attempt;
	}
}
// namespace bulls_and_cows

