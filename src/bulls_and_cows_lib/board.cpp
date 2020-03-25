
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

	CodeValidity validate_attempt(const GameOptions& game_options, const Code& attempt)
	{
		if (game_options.number_of_characters_per_code == attempt.value.size())
		{
			for (const char& c : attempt.value)
			{
				//From A to D for example
				if ((c < game_options.minimum_allowed_character) | (c > game_options.maximum_allowed_character))
				{
					return CodeValidity::ForbiddenCharacter;
				}
			}
			return CodeValidity::Valid;
		}
		return CodeValidity::LengthError;
	}
	
	//Copy as parameter because don't want any extern modifications.
	Feedback compare_attempt_with_secret_code(Code attempt, Code secret_code)
	{
		Feedback myfeed{};
		/*std::string tmp_secret_code = secret_code.value;
		std::string tmp_attempt = attempt.value;*/
		std::size_t found;

		//bulls managing
		for (int i = 0; i < secret_code.value.size(); i++)
		{
			if (secret_code.value[i] == attempt.value[i])
			{
				attempt.value.erase(i, 1);
				secret_code.value.erase(i, 1);
				myfeed.bulls++;
				i--;
			}
		}

		//cows managing
		for (int j = 0; j < attempt.value.size(); j++)
		{
			found = secret_code.value.find(attempt.value[j]);
			if (found != std::string::npos)
			{
				secret_code.value.erase(found, 1);
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
		}

		return (game_options.max_number_of_attempts == board.attempts_and_feedbacks.size());

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
		}

		return (board.attempts_and_feedbacks.back().attempt.value == board.secret_code.value);
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

	std::string special_char(int number, std::string spec)
	{
		std::string spe_string = "";
		for (int i = 0; i < number; i++)
		{
			for (int j = 0; j < spec.size(); j++) {
				spe_string.push_back(spec[j]);
			}
		}
		return spe_string;
	}

	std::string display_current_attempt(std::string atpt)
	{
		std::string atpt_spaces = "";
		for (int i = 0; i < atpt.size(); i++)
		{
			atpt_spaces.push_back(atpt[i]);
			atpt_spaces.push_back(' ');
		}
		return atpt_spaces;
	}

	//SUPER GENERIC AND OPTIMIZED FUNCTION, I SWEATED. FINALLY.
	//OBLIGED TO SET VARIABLES, IT DOESNT WORK DIRECTLY IN OUTPUTS.
	void display_zero(const GameOptions& game_options, std::ostream& output_stream, size_t i, std::string at, unsigned int b, unsigned int c) {
		std::string s = (i >= 10) ? "" : "0", s2 = (at == " ") ? special_char(game_options.number_of_characters_per_code, ". ") : display_current_attempt(at), s3 = (c != NULL || c == 0) ? "|   " : "",
			s4 = (c != NULL || c == 0) ? std::to_string(b) : "|       |       |\n", s5= (c != NULL || c == 0) ? "   |   " : "", s6 = (c != NULL || c==0) ? std::to_string(c) : "", s7= (c != NULL || c == 0) ? "   |\n" : "";
		output_stream << "| #" << s;
		output_stream << i << "      ";
		output_stream << s2;
		output_stream << s3;
		output_stream << s4;
		output_stream << s5;
		output_stream << s6;
		output_stream << s7;
	}

	
	void display_board(std::ostream& output_stream, const GameOptions& game_options, const Board& board)
	{
		output_stream << "\n";
		output_stream << "-----------" << special_char(game_options.number_of_characters_per_code, "--") << "--" << "---------------\n";
		output_stream << "| SECRET   " << board.secret_code.value << "| " << "              |\n";
		output_stream << "-----------" << special_char(game_options.number_of_characters_per_code, "--") << "--" << "---------------\n";
		output_stream << "| ATTEMPTS " << special_char(game_options.number_of_characters_per_code, "  ") << "| " << " BULLS | COWS |\n";
		output_stream << "-----------" << special_char(game_options.number_of_characters_per_code, "--") << "--" << "---------------\n";

		int number_of_attemps = game_options.max_number_of_attempts;
		for (size_t i = number_of_attemps; i > board.attempts_and_feedbacks.size(); i--)
		{
			display_zero(game_options, output_stream, i, " ", NULL, NULL);
		}
		if (!board.attempts_and_feedbacks.empty())
		{
			for (size_t index = board.attempts_and_feedbacks.size(); index > 0; --index)
			{
				const auto& attempt_and_feedback = board.attempts_and_feedbacks[index - 1];
				const auto& attempt = attempt_and_feedback.attempt;
				const auto& feedback = attempt_and_feedback.feedback;
				
				display_zero(game_options, output_stream, index, attempt.value, feedback.bulls, feedback.cows);
			}
		}

		output_stream << "-----------" << special_char(game_options.number_of_characters_per_code, "--") << "-" << "----------------\n";

	} // namespace bulls_and_cows
}
