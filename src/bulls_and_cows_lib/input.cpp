
#include "input.hpp"
#include <sstream>

namespace bulls_and_cows {

    std::string ask_string(std::istream& input_stream)
    {
        std::string value{};
        std::getline(input_stream, value);
        return value;

    }

    int ask_int_or_default(std::istream& input_stream, int default_value)
    {
        const auto string_value = ask_string(input_stream);
        std::istringstream iss(string_value);
        int value{};
        iss >> value;
        if (iss.fail() || iss.peek() != std::stringstream::traits_type::eof())
            return default_value;
        return value;
    }

    unsigned int ask_uint_or_default(std::istream& input_stream, unsigned int default_value)
    {
        const auto string_value = ask_string(input_stream);
        std::istringstream iss(string_value);
        unsigned int value{};
        iss >> value;
        if (iss.fail() || iss.peek() != std::stringstream::traits_type::eof())
            return default_value;
        return value;
    }

    char ask_char_or_default(std::istream& input_stream, char default_value)
    {
        const auto string_value = ask_string(input_stream);
        std::istringstream iss(string_value);
        char value{};
        iss >> value;
        if (iss.fail() || iss.peek() != std::stringstream::traits_type::eof())
            return default_value;
        return value;
    }

} // namespace bulls_and_cows
