
#include "game_solver.hpp"
#include "game.hpp"
#include <algorithm>

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

	//fonction recursive
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

	PossibleSolutions generate_all_possible_codes(const GameOptions& game_options)
	{
		//Objet qui va stocker tous les codes possible
		PossibleSolutions dico_all_codes{};
		
		//code courant
		std::string current_sequence;
		
		// 1er code compose du chars mini repete le nombre de chars par code permit 
		current_sequence = std::string(game_options.number_of_characters_per_code, game_options.minimum_allowed_character);
		
		//dernier code possible compose du char max repete le nombre de chars par code permit 
		std::string last_code = std::string(game_options.number_of_characters_per_code, game_options.maximum_allowed_character);
		
		//on push le 1er code 
		dico_all_codes.codes.push_back(current_sequence);
		
		//Tant que le code courant n'est pas egal au dernier code possible
		while (current_sequence != last_code)
		{
			//1er char incremente 
			current_sequence[0]++;

			//systeme de retenue, on regarde si le precedent char est > au char max possible, si c'est le cas on le remet au mini
			// et on incremente le suivant 
			// number_of_characters_per_code = 3 & char_min = A char_max = B ex: AAA, BAA, ABA, BBA, AAB, BAB, ABB, BBB
			for (unsigned int i = 1; i < game_options.number_of_characters_per_code; i++)
			{
				if (current_sequence[i - 1] > game_options.maximum_allowed_character)
				{
					current_sequence[i]++;
					current_sequence[i - 1] = game_options.minimum_allowed_character;
				}
			}
			dico_all_codes.codes.push_back(current_sequence);
			
		}
		
		return dico_all_codes;
	}


	

	void erase_invalid_solutions(PossibleSolutions& dico_all_codes, const FinalBoard& current_attempt)
	{
		FinalBoard comparison;
		dico_all_codes.codes.erase(
			std::remove_if(dico_all_codes.codes.begin(), dico_all_codes.codes.end(), [&current_attempt, &comparison](const std::string& code)
				{
					return count_bulls_cows_with_double(code, current_attempt.secretCode, comparison).bulls != current_attempt.bulls || count_bulls_cows_with_double(code, current_attempt.secretCode, comparison).cows != current_attempt.cows;
				}),
			dico_all_codes.codes.end());
	}



} // namespace bulls_and_cows
