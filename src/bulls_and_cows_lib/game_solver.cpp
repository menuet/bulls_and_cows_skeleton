
#include "game_solver.hpp"

namespace bulls_and_cows {
    // TODO: define the body of the functions declared in game_solver.cpp

    // The main recursive method
    // to print all possible
    // strings of length k
    void allCombinations(PossibleSolutions& possible_solutions, std::string& set, std::string prefix, int n, int k)
    {

        Code pref{};
        pref.value = prefix;

        // Base case: k is 0,
        // print prefix
        if (k == 0)
        {
            pref.value.erase(0, 1);
            possible_solutions.codes.push_back(pref);
            return;
        }

        // One by one add all characters
        // from set and recursively
        // call for k equals to k-1
        for (int i = 0; i < n; i++)
        {
            std::string newPrefix;

            // Next character of input added
            newPrefix = prefix + set[i];

            // k is decreased, because
            // we have added a new character
            allCombinations(possible_solutions, set, newPrefix, n, k - 1);
        }
    }

    PossibleSolutions generate_all_possible_codes(const GameOptions& game_options)
    {

        PossibleSolutions possible_solutions{};

        unsigned int CODE_LENGTH = game_options.number_of_characters_per_code;
        unsigned int NUM_CHAR =
            ((int)game_options.maximum_allowed_character - (int)game_options.minimum_allowed_character) + 1;

        std::vector<char> arrayPossibilities{};
        std::string s{};

        s.resize(NUM_CHAR);

        for (int i = game_options.minimum_allowed_character; i <= game_options.maximum_allowed_character; i++)
        {
            arrayPossibilities.push_back((char)(i)); // ABC
        }

        for (unsigned int i = 0; i < NUM_CHAR; i++)
        {
            s[i] = arrayPossibilities[i];
        }

        allCombinations(possible_solutions, s, " ", NUM_CHAR, CODE_LENGTH);

        return possible_solutions;
    }

    void combinationRecursive(unsigned int combinationLength, unsigned int position, Code& current, Code& elements,
                              PossibleSolutions& possible_solutions)
    {
        if (position >= combinationLength)
        {
            possible_solutions.codes.push_back(current);
        }

        for (int j = 0; j < elements.value.size(); ++j)
        {

            current.value[position] = elements.value[j];

            combinationRecursive(combinationLength, position + 1, current, elements, possible_solutions);
        }
    }

    Code pick_random_attempt(const PossibleSolutions& possible_solutions)
    {
        Code codeRandom{};

        int indexRandom = rand() % possible_solutions.codes.size();

        codeRandom = possible_solutions.codes[indexRandom];

        std::cout << "# Code picked randomnly: " << codeRandom.value;

        return codeRandom;
    }

    void remove_incompatible_codes_from_possible_solutions(const AttemptAndFeedback& attempt_and_feedback,
                                                           PossibleSolutions& possible_solutions)
    {
        Feedback feed;
        size_t size = possible_solutions.codes.size();

        for (int i = 0; i < size; i++)
        {
            size = possible_solutions.codes.size();
            feed = compare_attempt_with_secret_code(possible_solutions.codes[i], attempt_and_feedback.attempt);

            if ((feed.bulls != attempt_and_feedback.feedback.bulls) &&
                (feed.cows != attempt_and_feedback.feedback.cows))
            {
                if (i == possible_solutions.codes.size() - 1) //if it is the last element
                {
                    possible_solutions.codes.erase(possible_solutions.codes.end()-1);
                }
                else
                {
                    possible_solutions.codes.erase(possible_solutions.codes.begin() + i,possible_solutions.codes.begin() + i + 1);
                    i--;
                }

            }
        }
    }
} // namespace bulls_and_cows
