
#include "game_solver.hpp"
#include "game_options.hpp"
#include "random.hpp"
namespace bulls_and_cows {
    

    void therealgen(const GameOptions& game_options, PossibleSolutions& pls, std::string used_alphabet,
                  Code& code)
        // This method is the real method generating all possible attempts
    {
        for (char temp : used_alphabet) //  for each allowed character
        {
            if (code.value.length() < game_options.number_of_characters_per_code) // if the last character position of code is not yet reached
            {
                code.value.push_back(temp); // add the character at position num 

                therealgen(game_options, pls, used_alphabet, code); // new call of method to write on the next character position of code 
                code.value.pop_back(); // delete the last character in order to write the next character on the same position
            }
            else if (code.value.length() >= game_options.number_of_characters_per_code) // if the code is completely written
            {
                pls.codes.push_back(code);  // put the code in pls
                break;
            }
        }
    }



    void deleteduplicates(PossibleSolutions& pls)   // if the user requires unicity of characrter, this method will remove the codes not meeting the condition
    {
        auto end = std::remove_if(pls.codes.begin(), pls.codes.end(),
                                  [](Code const& code) -> bool {
                                      // use of lambda expression to pass several parameters to remove_if
                                        std::string used_chars;
                                        for (const char& c : code.value)
                                        if (used_chars.find(c) != std::string::npos)
                                        {
                                        return true;
                                        }
                                        else
                                        {
                                            used_chars.push_back(c);
                                        }
                                        return false;
                                  
                                  });
        pls.codes.erase(end, pls.codes.end());
    }
    

    

    PossibleSolutions generate_all_possible_codes(const GameOptions& game_options)
    {
        PossibleSolutions yeet{};
        std::string alphabet;
        Code codes;
        // Generation of the set of used character, stored in a string
        for (char c = game_options.minimum_allowed_character; c <= game_options.maximum_allowed_character; c++)
        {
            alphabet.push_back(c);
        }
        therealgen(game_options, yeet, alphabet, codes); // Call of the real method
        if (game_options.unique_characters)
            deleteduplicates(yeet);
        return yeet;
    }

    Code pick_random_attempt(const PossibleSolutions& possible_solutions) // everything is in the name
    {
        int pos = (generate_random_integer(0, static_cast<int>(possible_solutions.codes.size() - 1)));
        return possible_solutions.codes[pos];
    }

    

     
    void remove_incompatible_codes_from_possible_solutions(const AttemptAndFeedback& attempt_and_feedback,
                                                           PossibleSolutions& possible_solutions)
    {
        auto end = std::remove_if(possible_solutions.codes.begin(), possible_solutions.codes.end(),                                  
                           [attempt_and_feedback](Code const& c) -> bool {
            //use of lambda expression to pass several parameters to remove_if 
                               Feedback tempfeed = compare_attempt_with_secret_code(c, attempt_and_feedback.attempt);
                               
                               if (tempfeed.bulls != attempt_and_feedback.feedback.bulls ||
                                   tempfeed.cows != attempt_and_feedback.feedback.cows) 
                               {
                                   return true; // the code needs to be deleted 
                               }
                                 return false;
                         });
        possible_solutions.codes.erase(end, possible_solutions.codes.end()); // delete the code from array
    }

} // namespace bulls_and_cows
