
#include "board.hpp"

namespace bulls_and_cows {

	// TODO: define the body of the functions declared in board.cpp
	Board create_board(const GameOptions& game_options)
	{
		//std::vector<char> answer{};
		Board myboard{};

		for (unsigned int i = 0U; i < game_options.number_of_characters_per_code; i++)
		{
			//myboard.secret_code.value = myboard.secret_code.value + bulls_and_cows::generate_random_character(0, 9);
			myboard.secret_code.value = myboard.secret_code.value + static_cast<char>(bulls_and_cows::generate_random_character(game_options.minimum_allowed_character, game_options.maximum_allowed_character));
		}

		return myboard;
	}


	bool validate_attempt(const GameOptions& game_options, const Code& attempt)
	{
		if (game_options.number_of_characters_per_code == attempt.value.size())
		{
			for (const char& c : attempt.value)
			{
				//From A to D for example
				if ((c < game_options.minimum_allowed_character) | (c > game_options.maximum_allowed_character))
				{
					return false;
				}
			}
			return attempt.value.size() == game_options.number_of_characters_per_code;
		}
		return attempt.value.size() == game_options.number_of_characters_per_code;
	}

	Feedback compare_attempt_with_secret_code(const Code& attempt, const Code& secret_code)
	{
		Feedback myfeed{};
		std::string tmp_secret_code = secret_code.value;
		std::string tmp_attempt = attempt.value;
		std::size_t found;
		//bulls managing
		for (int i = 0; i < tmp_secret_code.size(); i++)
		{
			if (tmp_secret_code[i] == tmp_attempt[i])
			{
				tmp_attempt.erase(i, 1);
				tmp_secret_code.erase(i, 1);
				//std::cout << secret_code.value[i] << "Secret code chars";
				//std::cout << attempt.value[i] << "Attemps chars";
				myfeed.bulls++;
				i--;
			}
		}

		//cows managing
		for (int j = 0; j < tmp_attempt.size(); j++)
		{
			found = tmp_secret_code.find(tmp_attempt[j]);
			if (found != std::string::npos)
			{
				tmp_secret_code.erase(tmp_secret_code.find(tmp_attempt[j]), 1);
				myfeed.cows++;
			}
		}

		return myfeed;
	}

	bool is_end_of_game(const GameOptions& game_options, const Board& board)
	{
		if (game_options.max_number_of_attempts == board.attempts_and_feedbacks.size())
		{
			std::cout << "You lost, snif !";
			return true;
		}
		else return false;
	}


	bool is_win(const GameOptions& game_options, const Board& board)
	{

		if ((board.attempts_and_feedbacks.empty()))
			return false;

		else if (board.attempts_and_feedbacks.back().attempt.value == board.secret_code.value)
		{
			if (board.attempts_and_feedbacks.size() < (game_options.max_number_of_attempts - 3))
				std::cout << "You won on your " << board.attempts_and_feedbacks.size() << " attempt. Well played !";
			else if (board.attempts_and_feedbacks.size() > (game_options.max_number_of_attempts - 3))
				std::cout << "You won on your " << board.attempts_and_feedbacks.size() << " attempt. Close one !";
			return true;
		}

		else return false;
	}

	Code ask_attempt(std::ostream& output_stream, std::istream& input_stream, const GameOptions& game_options,
		const Board& board)
	{
		// Max number of attemps and max number of character ...
		Code incode;
		auto current_attempt = board.attempts_and_feedbacks.size() + 1;

		bool valueformat = false;
		while (!valueformat)
		{
			output_stream << "What is your guess #" << current_attempt << " ("
				<< game_options.number_of_characters_per_code << " characters between '"
				<< game_options.minimum_allowed_character << "' and '"
				<< game_options.maximum_allowed_character << "')\n? ";

			valueformat = true;

			input_stream >> incode.value;
			if (incode.value.size() != game_options.number_of_characters_per_code)
			{
				valueformat = false;
				output_stream
					<< "Your guess has an invalid length or contains non-allowed characters, please try again\n";
				break;
			}

			else
			{
				for (char& c : incode.value)
				{
					if ((c < game_options.minimum_allowed_character) | (c > game_options.maximum_allowed_character))
					{
						valueformat = false;

						output_stream << "Your guess has an invalid length or contains non-allowed characters, "
							"please try again\n";
						break;
					}
				}
			}
		}
		return incode;
	}

	std::string moins_function(int number, std::string loopadd)
	{
		std::string moins = "";
		for (int i = 0; i < number; i++)
		{
			moins += loopadd;
		}
		return moins;
	}

	std::string print_code(std::string atpt)
	{
		std::string atpt_spaces = "";
		for (int i = 0; i < atpt.size(); i++)
		{
			atpt_spaces += atpt[i] + " ";
		}

		return atpt_spaces;
	}


	void display_board(std::ostream& output_stream, const GameOptions& game_options, const Board& board)
	{
		//HEAD ...
		output_stream << "-----------" << moins_function(game_options.number_of_characters_per_code, "--") << "--" << "---------------\n";
		//output_stream << "| SECRET   " << moins_function(game_options.number_of_characters_per_code, "* ") << "| " << "              |\n";
		output_stream << "| SECRET   " << board.secret_code.value << "| " << "              |\n";
		output_stream << "-----------" << moins_function(game_options.number_of_characters_per_code, "--") << "--" << "---------------\n";
		output_stream << "| ATTEMPTS " << moins_function(game_options.number_of_characters_per_code, "  ") << "| " << " BULLS | COWS |\n";
		output_stream << "-----------" << moins_function(game_options.number_of_characters_per_code, "--") << "--" << "---------------\n";
		//...

		//BODY ...
		int number_of_attemps = game_options.max_number_of_attempts;
		for (unsigned int i = number_of_attemps; i > board.attempts_and_feedbacks.size(); i--)
		{
			if (i >= 10)
			{
				output_stream << "| #" << i << "      "
					<< moins_function(game_options.number_of_characters_per_code, ". ")
					<< "|       |       |\n";
			}
			else
			{
				output_stream << "| #0" << i << "      "
					<< moins_function(game_options.number_of_characters_per_code, ". ")
					<< "|       |       |\n";
			}

		}
		if (!board.attempts_and_feedbacks.empty())
		{
			for (size_t index = board.attempts_and_feedbacks.size(); index > 0; --index)
			{
				const auto& attempt_and_feedback = board.attempts_and_feedbacks[index - 1];
				const auto& attempt = attempt_and_feedback.attempt;
				const auto& feedback = attempt_and_feedback.feedback;
				if (index > 10)
				{
					//WHY ???
					output_stream << "| #" << index << "      " << print_code(attempt.value)
						<< "|   " << feedback.bulls << "   |   " << feedback.cows << "   |\n";
				}
				else
				{
					output_stream << "| #0" << index << "      " << print_code(attempt.value)
						<< "|   " << feedback.bulls << "   |   " << feedback.cows << "   |\n";
				}

			}
		}
		//...

		//FOOTER ...
		output_stream << "-----------" << moins_function(game_options.number_of_characters_per_code, "--") << "-" << "----------------\n";
		//...

	} // namespace bulls_and_cows


	//void display_board(std::ostream& output_stream, const GameOptions& game_options, const Board& board)
	//{
	//	////SIMPLE TEST
	//	//output_stream << "Secret code (for debugging and cheating) = " << board.secret_code.value << "\n";
	//	//for (unsigned int index = 0; index < board.attempts_and_feedbacks.size(); ++index)
	//	//{
	//	//	const auto& attempt_and_feedback = board.attempts_and_feedbacks[index];
	//	//	const auto& attempt = attempt_and_feedback.attempt;
	//	//	const auto& feedback = attempt_and_feedback.feedback;
	//	//	output_stream << "Attempt #" << (index + 1) << " = " << attempt.value << " | Bulls = " << feedback.bulls
	//	//		<< " | Cows = " << feedback.cows << "\n";
	//	//}
}
