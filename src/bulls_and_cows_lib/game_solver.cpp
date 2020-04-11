
#include "game_solver.hpp"
#include <algorithm>

namespace bulls_and_cows {
	void recursif(int num, int max, const GameOptions& game_options, PossibleSolutions& pls, std::string used_alphabeat,
		Code codes)
	{
		for (char temp : used_alphabeat)
		{
			if (num <= max)
			{
				codes.value.push_back(temp);
				num++;

				recursif(num, max, game_options, pls, used_alphabeat, codes);
				codes.value.pop_back();
			}
			else if (num > max)
			{
				pls.codes.push_back(codes);
				break;
			}
			num--;
		}
	}

	void get_code_without_duplicates(PossibleSolutions& pls)
	{
		auto end = std::remove_if(pls.codes.begin(), pls.codes.end(),
			[&pls](Code const& code) -> bool {
				// use of lambda expression to pass several parameters to remove_if
				std::string used_chars;
				for (char c : code.value)
					if (used_chars.find(c) != std::string::npos)
					{
						return true;
					}
					else
					{
						used_chars.push_back(c);
					}
				return false;

			});
		pls.codes.erase(end, pls.codes.end());
	}

	PossibleSolutions generate_all_possible_codes(const GameOptions& game_options)
	{
		PossibleSolutions avc{};
		std::string used_alphabeat;
		for (char c = game_options.minimum_allowed_character; c <= game_options.maximum_allowed_character; c++)
		{
			used_alphabeat.push_back(c);
		}
		Code codes;
		recursif(1, game_options.number_of_characters_per_code, game_options, avc, used_alphabeat, codes);

		std::cout << "char from min to max : " << used_alphabeat << "\n";

		if (game_options.isDuplicate == false) {
			get_code_without_duplicates(avc);
		}

		return avc;
	}


	Code pick_random_attempt(const PossibleSolutions& possible_solutions)
	{
		if (possible_solutions.codes.size() != 0) {
			int pos = (generate_random_integer(0, static_cast<int> (possible_solutions.codes.size() - 1)));
			return possible_solutions.codes[pos];
		}
		return possible_solutions.codes[0];
	}


	void remove_incompatible_codes_from_possible_solutions(const AttemptAndFeedback& attempt_and_feedback, PossibleSolutions& possible_solutions)
	{
		possible_solutions.codes.erase(std::remove_if(possible_solutions.codes.begin(), possible_solutions.codes.end(),
			[attempt_and_feedback](Code const& c) -> bool { 
				Feedback tempfeed = compare_attempt_with_secret_code(c, attempt_and_feedback.attempt);
				if (tempfeed.bulls != attempt_and_feedback.feedback.bulls || tempfeed.cows != attempt_and_feedback.feedback.cows)
					return true;

				return false;
			}),
			possible_solutions.codes.end());
	}
}
