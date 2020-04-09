
#include "game_solver.hpp"
#include "random.hpp"
#include <algorithm>
#include <iostream>
#include <vector>

namespace bulls_and_cows {

    Code generate_next_code(const GameOptions& game_options, Code previous_code)
    {
        Code new_code;
        new_code.value = previous_code.value;
        // int nb_character = game_options.number_of_characters_per_code;
        for (unsigned int i = game_options.number_of_characters_per_code; i > 0; i--)
        {
            if (previous_code.value[i - 1] != game_options.maximum_allowed_character)
            {
                new_code.value[i - 1] = previous_code.value[i - 1] + 1;
                return new_code;
            }

            else
            {
                new_code.value[i - 1] = game_options.minimum_allowed_character;
            }
        }
        return new_code;
    }

    PossibleSolutions generate_all_possible_codes(const GameOptions& game_options)
    {
        PossibleSolutions possiblesolutions;
        Code first_code;
        Code last_code;
        for (unsigned int i = 0; i < game_options.number_of_characters_per_code; i++)
        {
            first_code.value += game_options.minimum_allowed_character;
            last_code.value += game_options.maximum_allowed_character;
        }

        possiblesolutions.codes.push_back(first_code);

        while (possiblesolutions.codes.back().value != last_code.value)
        {
            first_code = generate_next_code(game_options, first_code);
            possiblesolutions.codes.push_back(first_code);
        }

        return possiblesolutions;
    }

    Code pick_random_attempt(const PossibleSolutions& possible_solutions)
    {
        return possible_solutions
            .codes[generate_random_integer(0, static_cast<int>(possible_solutions.codes.size() - 1))];
    }

    void remove_incompatible_codes_from_possible_solutions(const AttemptAndFeedback& attempt_and_feedback,
                                                           PossibleSolutions& possible_solutions)
    { //.attempt : AABAA .feedback.bulls : 0 .feedback.cows : 3
        possible_solutions.codes.erase(
            std::remove_if(possible_solutions.codes.begin(), possible_solutions.codes.end(), [&](Code c) {
                if (compare_attempt_with_secret_code(c, attempt_and_feedback.attempt).bulls !=
                        attempt_and_feedback.feedback.bulls ||
                    compare_attempt_with_secret_code(c, attempt_and_feedback.attempt).cows !=
                        attempt_and_feedback.feedback.cows)
                {
                    return true;
                }
                return false;
            }),possible_solutions.codes.end());
    }


} // namespace bulls_and_cows
