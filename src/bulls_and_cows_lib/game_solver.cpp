
#include "game_solver.hpp"
#include "game_options.hpp"
namespace bulls_and_cows {
    

    void recursif(int num, int max, const GameOptions& game_options, PossibleSolutions& pls, std::string used_alphabeat,
                  Code codes)
    {
        for (char temp : used_alphabeat)
        {
            if (num <= max)
            {
                codes.value.push_back(temp);
                num++;

                recursif(num, max, game_options, pls, used_alphabeat, codes);
                codes.value.pop_back();
            }
            else if (num > max)
            {
                pls.codes.push_back(codes);
                num--;
                break;
            }
            num--;
        }
    }

    

    PossibleSolutions generate_all_possible_codes(const GameOptions& game_options)
    {
        PossibleSolutions yeet{};
        std::string alphabet;
        Code codes;
        // Génération de la chaine avec toutes les lettres du min a la max
        for (char c = game_options.minimum_allowed_character; c <= game_options.maximum_allowed_character; c++)
        {
            alphabet.push_back(c);
        }
        recursif(1, game_options.number_of_characters_per_code, game_options, yeet, alphabet, codes);
        return yeet;
    }

     


} // namespace bulls_and_cows
