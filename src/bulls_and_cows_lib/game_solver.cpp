
#include "game_solver.hpp"
#include <algorithm>

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
                    NewChaine.value[i - 1] = NewChaine.value[i - 1] + 1;
                    break;
                }
                else
                {
                    NewChaine.value[i - 1] = game_options.minimum_allowed_character;
                }
            }
            PSolution.codes.push_back(NewChaine);
        }

        return PSolution;
    }

     Code pick_random_attempt(const PossibleSolutions& possible_solutions)
    {
            return possible_solutions
                .codes[(generate_random_integer(0, static_cast<int>(possible_solutions.codes.size() - 1)))];
    }

      void remove_incompatible_codes_from_possible_solutions(const AttemptAndFeedback& attempt_and_feedback,
                                                           PossibleSolutions& possible_solutions)
    {
       
          possible_solutions.codes.erase(std::remove_if(possible_solutions.codes.begin(),possible_solutions.codes.end(),[&](Code code)
                            {
                                                          Feedback feed = compare_attempt_with_secret_code(
                                                              code, attempt_and_feedback.attempt);
                              if (feed.bulls != attempt_and_feedback.feedback.bulls || feed.cows != attempt_and_feedback.feedback.cows)
                                    return true;
                                                         
                              return false;
                                                         
                            }),possible_solutions.codes.end());
    }

} // namespace bulls_and_cows
