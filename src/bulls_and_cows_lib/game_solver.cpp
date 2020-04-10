
#include "game_solver.hpp"
#include <math.h>

namespace bulls_and_cows {
    
    PossibleSolutions generate_all_possible_codes(const GameOptions& game_options)
    {
        PossibleSolutions all_solutions{};
        Code current_code{};

        //The first code is composed of the minimum allowed character repeated the number of charaters per code times
        current_code.value = std::string(game_options.number_of_characters_per_code, game_options.minimum_allowed_character);

        // The last code is composed of the maximum allowed character repeated the number of charaters per code times
        std::string final_string =
            std::string(game_options.number_of_characters_per_code, game_options.maximum_allowed_character);
        
        // Check if duplicates are allowed, if they are not allowed, check if there is duplicates in the code
        if (game_options.allow_duplicate || !check_duplicates(current_code.value))
        {
            all_solutions.codes.push_back(current_code);
        }

        while (current_code.value != final_string)
        {
            //We increment the first character
            current_code.value[0]++;

            //For each character in the other part of code, we check if the previous character is superior to the maximum allowed character
            //If it is, we set the previous character to the minimum allowed character and we increment the current one.
            for (unsigned int i = 1; i < game_options.number_of_characters_per_code; i++)
            {
                if (current_code.value[i-1]>game_options.maximum_allowed_character)
                {
                    current_code.value[i]++;
                    current_code.value[i - 1] = game_options.minimum_allowed_character;
                }
            }

            // Check if duplicates are allowed, if they are not allowed, check if there is duplicates in the code
            if (game_options.allow_duplicate || !check_duplicates(current_code.value))
            {
                all_solutions.codes.push_back(current_code);
            }
        }

        return all_solutions;
    }

} // namespace bulls_and_cows
