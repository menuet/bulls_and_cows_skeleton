
#include "game_solver.hpp"

namespace bulls_and_cows {
    // TODO: define the body of the functions declared in game_solver.cpp

  

    PossibleSolutions generate_all_possible_codes(const GameOptions& game_options)
    {

        Code MinChaine;
        Code MaxChaine;

        for (int unsigned i = 0; i < game_options.number_of_characters_per_code; i++)
        {
            MinChaine.value += game_options.minimum_allowed_character;
            MaxChaine.value += game_options.maximum_allowed_character;
        }

        PossibleSolutions PSolution;
        PSolution.codes.push_back(MinChaine);

         Code NewChaine;
        NewChaine.value = MinChaine.value;

        while (NewChaine.value != MaxChaine.value)
        {
            for (int unsigned i = game_options.number_of_characters_per_code; i > 0; i--)
            {
                if (NewChaine.value[i - 1] != game_options.maximum_allowed_character)
                {
                    NewChaine.value[i - 1] = MinChaine.value[i - 1] + 1;
                    break;
                }
                else
                {
                    NewChaine.value[i - 1] = game_options.minimum_allowed_character;
                }
            }
            PSolution.codes.push_back(MinChaine);
        }

        return PSolution;
    }

} // namespace bulls_and_cows
