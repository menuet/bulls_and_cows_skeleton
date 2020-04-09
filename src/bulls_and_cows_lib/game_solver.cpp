
#include "game_solver.hpp"
#include <list>
#include <vector>
#include <algorithm>
#include <iterator>
#include <ostream>
#include "random.hpp"

namespace bulls_and_cows {

    PossibleSolutions generate_all_possible_codes(const GameOptions& game_options)
    {
        PossibleSolutions poss;
        std::string alphabet;
        int ecart_lettre = 0;

        Code possible_code;

        for (char c = game_options.minimum_allowed_character; c <= game_options.maximum_allowed_character; c++)
        {
            alphabet.push_back(c);
            ecart_lettre += 1;
        }

        while (possible_code.value.size() != game_options.number_of_characters_per_code)
        {
            possible_code.value += game_options.minimum_allowed_character;
        }
        poss.codes.push_back(possible_code);

        size_t f = poss.codes.size();
        //

        
        possible_code.value.erase(0, possible_code.value.size());

        
        
        while(f < pow(ecart_lettre, game_options.number_of_characters_per_code))
        {

            possible_code.value.erase(0, possible_code.value.size());
            int d = game_options.number_of_characters_per_code;
            
            while (d > 0)
            {
                if (poss.codes[f-1].value.back() != game_options.maximum_allowed_character)
                {
                    possible_code.value.push_back(char(poss.codes[f-1].value.back()) + 1);

                    if (d == 1)
                    {
                        possible_code.value.push_back( char ( poss.codes[f-1].value[0] ) );
                        std::reverse(possible_code.value.begin(), possible_code.value.end());
                    }
                    
                    else
                    {
                        std::string sub2 = poss.codes[f-1].value.substr(0,d-1);
                        std::reverse(sub2.begin(), sub2.end());

                        possible_code.value.append(sub2);
                        std::reverse(possible_code.value.begin(), possible_code.value.end());
                        d = 0;
                    }
                    
                    
                }

                else
                {
                    int q = game_options.number_of_characters_per_code;
                    
                    while (poss.codes[f-1].value[q-1] == game_options.maximum_allowed_character)
                    {
                        possible_code.value.push_back(char(game_options.minimum_allowed_character));
                        q--;
                    }
                    //possible_code.value.push_back(char());
                    possible_code.value.push_back(char(poss.codes[f - 1].value[q - 1] + 1));
                    std::string sub3 = poss.codes[f - 1].value.substr(0,q-1);
                    std::reverse(sub3.begin(), sub3.end());

                    possible_code.value.append(sub3);
                    std::reverse(possible_code.value.begin(), possible_code.value.end());
                    d = 0;
                }
                

            } 
            poss.codes.push_back(possible_code);
            f++;
        }

        for (int o =0; o<poss.codes.size();o++)
        {
          std::cout << poss.codes[o].value << "\n";
        }


        return poss;
    }

    Code pick_random_attempt(const PossibleSolutions& possible_solutions)
    {
        int x = generate_random_integer(0, static_cast<int>(possible_solutions.codes.size()-1));
        return possible_solutions.codes[x];
    }


}
