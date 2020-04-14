
#include "game_solver.hpp"
#include <algorithm>
#include <set>

namespace bulls_and_cows {

	void code_gen(const GameOptions& game_options, PossibleSolutions& pls, std::string used_alphabet,
		Code& code)
	{
		for (char temp : used_alphabet)
		{
			//code creation, step by step
			if (code.value.length() < game_options.number_of_characters_per_code)
			{
				code.value.push_back(temp);

				code_gen(game_options, pls, used_alphabet, code);
				code.value.pop_back(); 
			}
			//push in vector
			else
			{
				if (game_options.isDuplicate == false && contains_duplicates(code.value)) {
					break;
				}
				pls.codes.push_back(code);
				break;
			}
		}
	}

	bool contains_duplicates(const std::string& s)
	{
		std::set<char> check_uniq;
		for (unsigned long int i = 0; i < s.length(); ++i)
			if (!check_uniq.insert(s[i]).second)
				return true; // Duplicated char found
		return false; // No duplicated char found
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
		code_gen(game_options, avc, used_alphabeat, codes);

		//Useless now, I check before creating possible solutions.
		/*if (game_options.isDuplicate == false) {
			get_code_without_duplicates(avc);
		}*/

		return avc;
	}


	Code pick_random_attempt(const PossibleSolutions& possible_solutions)
	{
		if (possible_solutions.codes.size() != 0) {
			int pos = (generate_random_integer(0, static_cast<int> (possible_solutions.codes.size() - 1)));
			return possible_solutions.codes.at(pos);
		}
		return possible_solutions.codes.at(0);
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
