
#include "game_solver.hpp"
#include "random.hpp"


namespace bulls_and_cows {
    // TODO: define the body of the functions declared in game_solver.cpp

    // The recursive method
    void allCombinations(PossibleSolutions& possible_solutions, std::string& setPossibleCharacters, std::string prefixCode, int nbPossibleChar, int sizeCode)
    {
        Code newCombination{};
        newCombination.value = prefixCode;

        if (sizeCode == 0)
        {
            possible_solutions.codes.push_back(newCombination); // we add to our vector possible_solutions.codes the code newCombination
            return;
        }

        // One by one we add all characters from set of possible characters(ex: all char from A to H) and recursively call for sizeCode equals to sizeCode-1
        for (int i = 0; i < nbPossibleChar; i++)
        {
            std::string newPrefixCode;

            // we create a new combination with a char from the string setPossibleCharacters, and we add it to a prefix until the size of the code
            newPrefixCode = prefixCode + setPossibleCharacters[i];

            // sizeCode decreased, because we have added a new character to the new possible combination
            allCombinations(possible_solutions, setPossibleCharacters, newPrefixCode, nbPossibleChar, sizeCode - 1);
        }
    }

    PossibleSolutions generate_all_possible_codes(const GameOptions& game_options)
    {

        PossibleSolutions possible_solutions{};
        unsigned int nbPossibleChar =((int)game_options.maximum_allowed_character - (int)game_options.minimum_allowed_character) + 1;
        std::vector<char> arrayPossibilities{};
        std::string setPossibleCharacters{};
        setPossibleCharacters.resize(nbPossibleChar);

        for (int i = game_options.minimum_allowed_character; i <= game_options.maximum_allowed_character; i++)
        {
            arrayPossibilities.push_back((char)(i)); // on créé une array avec tous les char possibles
            //si les char possibles sont de A à H, notre vector arrayPossibilities sera = "ABCDEFGH"
        }

        //on copie les valeurs de ce vector dans un string setPossibleCharacters
        for (unsigned int i = 0; i < nbPossibleChar; i++)
            setPossibleCharacters[i] = arrayPossibilities[i];

        //on génère toutes les solutions possibles, il y en aura en tout: nbPossibleChar^nbLengthOfCode
        allCombinations(possible_solutions, setPossibleCharacters, "",nbPossibleChar, game_options.number_of_characters_per_code);

        return possible_solutions;
    }

    Code pick_random_attempt(const PossibleSolutions& possible_solutions)
    {
        Code codeRandom{};

        int indexRandom = rand() % possible_solutions.codes.size();
        //int indexRandom = generate_random_integer(0, (possible_solutions.codes.size() - 1));

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
                if (i == size - 1) // if it is the last element
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
