#include "random.hpp"
#include "game_solver.hpp"

namespace bulls_and_cows {


    std::vector<Code> generate_all_possibilities(GameOptions game_options)
    {
        std::vector<Code> all_possible;
        Code origine;
        for (unsigned int i = 0; i < game_options.number_of_characters_per_code; i++)
        {
            origine.value.push_back(game_options.minimum_allowed_character);
        }
        while (origine.value[0] <= game_options.maximum_allowed_character)
        {
            all_possible.push_back(origine);
            origine.value[game_options.number_of_characters_per_code - 1]++;
            for (int i = game_options.number_of_characters_per_code - 1; i > 0; i--)
            {
                if (origine.value[i] > game_options.maximum_allowed_character)
                {
                    origine.value[i] = game_options.minimum_allowed_character;
                    int j = i - 1;
                    origine.value[j]++;
                }
                else
                    break;
            }
        }

        return all_possible;
    }

     void remove_all_incompatible_codes(const GameOptions& game_options, std::vector<Code>& all_possible,
                                       AttemptAndFeedback newcomputerattemp)
    {
        for (int i = all_possible.size() - 1; i >= 0; i--)
        {
            Feedback f;
            f = bulls_and_cows::compare_attempt_with_secret_code(newcomputerattemp.attempt, all_possible[i]);
            if (newcomputerattemp.feedback.bulls != f.bulls || newcomputerattemp.feedback.cows != f.cows)
            {
                all_possible[i] = all_possible.back();
                all_possible.pop_back();
            }
        }
    }

      Code pick_random_attempt(std::vector<Code>& all_possible)
    {
          int r = bulls_and_cows::generate_random_integer(0, all_possible.size() - 1);
          Code s = all_possible[r];
          return s;
    }
} // namespace bulls_and_cows