#pragma once

#include <iostream>
#include <string>

namespace bulls_and_cows {

    // Ask the user to enter a string
    std::string ask_string(std::istream& input_stream);

    // Ask the user to enter an integer
    // If the user provides something else than an integer, then return the default value
    int ask_int_or_default(std::istream& input_stream, int default_value);

    // Ask the user to enter an integer
    // If the user provides something else than an integer, then return the default value
    unsigned int ask_uint_or_default(std::istream& input_stream, unsigned int default_value);

    // Ask the user to enter a character
    // If the user provides something else than a character, then return the default value
    char ask_char_or_default(std::istream& input_stream, char default_value);

} // namespace bulls_and_cows