#include "random.hpp"
#include <random>

namespace bulls_and_cows {

    int generate_random_integer(int min_value, int max_value)
    {
        static std::random_device rd{};
        static std::mt19937 rg{rd()};
        std::uniform_int_distribution<int> distrib{min_value, max_value};
        return distrib(rg);
    }

    char generate_random_character(char min_value, char max_value)
    {
        return static_cast<char>(generate_random_integer(min_value, max_value));
    }

} // namespace bulls_and_cows