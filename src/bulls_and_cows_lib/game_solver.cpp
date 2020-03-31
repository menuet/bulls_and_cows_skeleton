
#include "game_solver.hpp"
#include <math.h>

namespace bulls_and_cows {
    
    PossibleSolutions generate_all_possible_codes(const GameOptions& game_options)
    {
        PossibleSolutions all_solutions{};
        Code current_code{};
        current_code.value = std::string(game_options.number_of_characters_per_code, game_options.minimum_allowed_character);
        unsigned int counter = 0;
        const unsigned int number_of_allowed_characters = game_options.maximum_allowed_character - game_options.minimum_allowed_character + 1;

        do
        {
            unsigned int previous_char = counter % number_of_allowed_characters;
            current_code.value[0] = game_options.minimum_allowed_character + char(previous_char);
            for (unsigned int i = 1; i < game_options.number_of_characters_per_code; i++)
            {
                current_code.value[i] = game_options.minimum_allowed_character +
                    (char)(((counter - previous_char) / (int)pow(number_of_allowed_characters, i)) %
                           number_of_allowed_characters);
                previous_char = current_code.value[i - 1] - game_options.minimum_allowed_character;
            }
            if (game_options.allow_duplicate || !check_duplicates(current_code.value))
            {
                all_solutions.codes.push_back(current_code);
            }
            counter++;
        } while (current_code.value !=
                 std::string(game_options.number_of_characters_per_code, game_options.maximum_allowed_character));

        return all_solutions;
    }

} // namespace bulls_and_cows
