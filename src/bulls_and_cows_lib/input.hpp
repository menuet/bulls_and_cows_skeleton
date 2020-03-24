
#pragma once

#include <iostream>
#include <string>

namespace bulls_and_cows {

    // ask the user to enter a string
    std::string ask_string(std::istream& input_stream);

    // ask the user to enter an integer
    // if the user provides something else than an integer, then return the default value
    int ask_int_or_default(std::istream& input_stream, int default_value);

    // ask the user to enter an integer
    // if the user provides something else than an integer, then return the default value
    unsigned int ask_uint_or_default(std::istream& input_stream, unsigned int default_value);

    // ask the user to enter a character
    // if the user provides something else than a character, then return the default value
    char ask_char_or_default(std::istream& input_stream, char default_value);

} // namespace bulls_and_cows
