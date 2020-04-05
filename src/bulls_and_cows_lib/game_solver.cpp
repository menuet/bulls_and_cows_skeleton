
#include "game_solver.hpp"
#include "game.hpp"

namespace bulls_and_cows {
    // TODO: define the body of the functions declared in game_solver.cpp


	void generate_next_code(PossibleSolutions& dico_all_codes, std::string sequence, unsigned int  number_distinct_alphabet_char,
		unsigned int number_of_characters_per_code, std::string alphabet)
	{
		if (number_of_characters_per_code == 0)
		{
			dico_all_codes.codes.push_back(sequence);
			return;
		}
		for (unsigned int i = 0; i < number_distinct_alphabet_char; i++)
		{
			std::string seq;
			seq = sequence + alphabet[i];
			generate_next_code(dico_all_codes, seq, number_distinct_alphabet_char, number_of_characters_per_code - 1, alphabet);
		}
	}


	PossibleSolutions generate_all_codes(const GameOptions& game_options)
	{
		const unsigned int number_distinct_alphabet_char = game_options.maximum_allowed_character - game_options.minimum_allowed_character + 1; //le nombre de caractere distinct de l'alphabet possible 
		std::string alphabet;

		for (char i = game_options.minimum_allowed_character; i <= game_options.maximum_allowed_character; i++)
		{
			alphabet.push_back(i);
		}

		PossibleSolutions dico_all_codes{};
		generate_next_code(dico_all_codes, "", number_distinct_alphabet_char, game_options.number_of_characters_per_code, alphabet);
		std::cout << "Number of codes in dico : " << dico_all_codes.codes.size();

		return dico_all_codes;
	}


	PossibleSolutions remove_impossible_codes(PossibleSolutions& dico_all_codes, FinalBoard current_attempt, std::string current_code)
	{

		int size = static_cast<int>(dico_all_codes.codes.size());
		for (int i = 0; i < size; i++)
		{

			FinalBoard comparison = count_bulls_cows_with_double(dico_all_codes.codes[i], current_code, comparison);

			if (comparison.bulls != current_attempt.bulls || comparison.cows != current_attempt.cows)
			{
				dico_all_codes.codes.erase(dico_all_codes.codes.begin() + i);
				size = size - 1;
				i = i - 1;
			}


		}
		return dico_all_codes;
	}




} // namespace bulls_and_cows
