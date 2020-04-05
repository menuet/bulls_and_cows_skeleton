
#pragma once

#include <string>
#include <vector>

namespace bulls_and_cows {

    // Each time you call this function, it produces a random number
    // between min_value included and max_value included
    int generate_random_integer(int min_value, int max_value);
	unsigned int generate_random_unsigned_integer(unsigned int min_value, unsigned int max_value);
    // Each time you call this function, it produces a random character
    // between min_value included and max_value included
    char generate_random_character(char min_value, char max_value);

} // namespace bulls_and_cows
