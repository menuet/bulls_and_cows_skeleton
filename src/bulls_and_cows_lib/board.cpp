#include "board.hpp"
#include "random.hpp"
#include <iostream>

namespace bulls_and_cows {

    Board create_board(const GameOptions& game_options)
    {
        Board ans;

        for (unsigned int i = 0U; i < game_options.number_of_characters_per_code; i++)
        {
            if (game_options.maximum_allowed_character >= 65 && game_options.maximum_allowed_character <= 90 &&
                game_options.minimum_allowed_character >= 65 && game_options.minimum_allowed_character <= 90)
            {
                ans.secret_code.value = ans.secret_code.value + bulls_and_cows::generate_random_character(
                                                                    game_options.minimum_allowed_character,
                                                                    game_options.maximum_allowed_character);
            }

            else if (game_options.maximum_allowed_character >= 48 && game_options.maximum_allowed_character <= 57 &&
                     game_options.minimum_allowed_character >= 48 && game_options.minimum_allowed_character <= 57)
            {
                ans.secret_code.value = ans.secret_code.value + (char)bulls_and_cows::generate_random_integer(
                                                                    game_options.minimum_allowed_character,
                                                                    game_options.maximum_allowed_character);
            }

            else
            {
            }
        }
        return ans;
    }

    bool validate_attempt(const GameOptions& game_options, const Code& attempt)
    {
        if (game_options.number_of_characters_per_code == attempt.value.size())
        {
            for (const char& c : attempt.value)
            {
                if ((c < game_options.minimum_allowed_character) | (c > game_options.maximum_allowed_character))
                {
                    return false;
                }
            }
            return true;
        }
        else
        {
            return false;
        }
    }

    Feedback compare_attempt_with_secret_code(const Code& attempt, const Code& secret_code)
    {
        Feedback myfeed{};
        std::string tmp_secret_code = secret_code.value;
        std::string tmp_attempt = attempt.value;
        std::size_t found;
        // bulls managing
        for (int i = 0; i < tmp_secret_code.size(); i++)
        {
            if (tmp_secret_code[i] == tmp_attempt[i])
            {
                tmp_attempt.erase(i, 1);
                tmp_secret_code.erase(i, 1);
                myfeed.bulls++;
                i--;
            }
        }
        // cows managing
        for (int j = 0; j < tmp_attempt.size(); j++)
        {
            found = tmp_secret_code.find(tmp_attempt[j]);
            if (found != std::string::npos)
            {
                tmp_secret_code.erase(tmp_secret_code.find(tmp_attempt[j]), 1);
                myfeed.cows++;
                //               std::cout << tmp_attempt[j] << "-" << myfeed.cows << "  " <<
                //               tmp_secret_code.find(tmp_attempt[j])
                //                         << "\n";
            }
        }
        return myfeed;
    }

    bool is_end_of_game(const GameOptions& game_options, const Board& board)
    {
        if (game_options.max_number_of_attempts == board.attempts_and_feedbacks.size())
        {
            return true;
        }
        return false;
    }

    bool is_win(const GameOptions& game_options, const Board& board)
    {
        if ((board.attempts_and_feedbacks.empty()))
            return false;

        if (board.attempts_and_feedbacks.back().attempt.value == board.secret_code.value)
        {
            return true;
        }

        return false;
    }

    std::string moins_function(int number, std::string loopadd)
    {
        std::string moins = "";
        for (int i = 0; i < number; i++)
        {
            for (int j = 0; j < loopadd.size(); j++)
                moins.push_back(loopadd[j]);
        }
        return moins;
    }

    void print_code(std::string code)
    {
        char* ccode = const_cast<char*>(code.c_str());
        std::string codewspace = "";
        for (int i = 0; i < code.length(); i++)
        {
            std::cout << ccode[i] << " ";
        }
    }

    void display_board(std::ostream& output_stream, const GameOptions& game_options, const Board& board)
    {
        // HEAD ...
        output_stream << "Secret code (for debugging and cheating) = " << board.secret_code.value << "\n";
        output_stream << "-----------" << moins_function(game_options.number_of_characters_per_code, "--") << "--"
                      << "---------------\n";

        if (is_end_of_game(game_options, board) == true || is_win(game_options, board) == true)
        {
            output_stream << "| SECRET   ";
            for (int i = 0; i < board.secret_code.value.size(); i++)
            {
                std::cout << board.secret_code.value[i] << " ";
            }
            output_stream << "| "
                          << "              |\n";
        }
        else
        {
            output_stream << "| SECRET   " << moins_function(game_options.number_of_characters_per_code, "* ") << "| "
                          << "              |\n";
        }
        output_stream << "-----------" << moins_function(game_options.number_of_characters_per_code, "--") << "--"
                      << "---------------\n";
        output_stream << "| ATTEMPTS " << moins_function(game_options.number_of_characters_per_code, "  ") << "| "
                      << " BULLS | COWS |\n";
        output_stream << "-----------" << moins_function(game_options.number_of_characters_per_code, "--") << "--"
                      << "---------------\n";
        //...

        // BODY ...
        int number_of_attemps = game_options.max_number_of_attempts;
        for (size_t i = number_of_attemps; i > board.attempts_and_feedbacks.size(); i--)
        {

            output_stream << "| #" << ((i >= 10) ? "" : "0") << i << "      "
                          << moins_function(game_options.number_of_characters_per_code, ". ") << "|       |       |\n";
        }

        if (!board.attempts_and_feedbacks.empty())
        {
            for (size_t index = board.attempts_and_feedbacks.size(); index > 0; --index)
            {
                const auto& attempt_and_feedback = board.attempts_and_feedbacks[index - 1];
                const auto& attempt = attempt_and_feedback.attempt;
                const auto& feedback = attempt_and_feedback.feedback;

                output_stream << "| #" << ((index >= 10) ? "" : "0") << index << "      ";
                print_code(attempt.value);
                output_stream << "|   " << feedback.bulls << "   |   " << feedback.cows << "   |\n";
            }
        }
        //...

        // FOOTER ...
        output_stream << "-----------" << moins_function(game_options.number_of_characters_per_code, "--") << "-"
                      << "----------------\n";
        //...
    }

    void whats_your_guess(std::ostream& output_stream, const GameOptions& game_options, std::string s,
                          int current_attempt, unsigned int number_of_characters_per_code,
                          char minimum_allowed_character, char maximum_allowed_character)
    {
        output_stream << "What is your guess #" << s << current_attempt << " (" << number_of_characters_per_code
                      << " characters between '" << minimum_allowed_character << "' and '" << maximum_allowed_character
                      << "')\n? ";
    }
    Code ask_attempt(std::ostream& output_stream, std::istream& input_stream, const GameOptions& game_options,
                     const Board& board)
    {
        // Max number of attemps and max number of caracter ...
        Code incode;
        int current_attempt = (int)board.attempts_and_feedbacks.size() + 1;
        bool valueformat = false;
        while (!valueformat)
        {
            if (current_attempt > 10)
            {
                whats_your_guess(output_stream, game_options, "0", current_attempt,
                                 game_options.number_of_characters_per_code, game_options.minimum_allowed_character,
                                 game_options.maximum_allowed_character);
            }
            else
            {
                whats_your_guess(output_stream, game_options, "", current_attempt,
                                 game_options.number_of_characters_per_code, game_options.minimum_allowed_character,
                                 game_options.maximum_allowed_character);
            }

            valueformat = true;

            input_stream >> incode.value;
            if (incode.value.size() != game_options.number_of_characters_per_code)
            {
                valueformat = false;
                output_stream << "Your guess has an invalid length, please try again\n";
            }

            else
            {
                for (char& c : incode.value)
                {
                    if ((c < game_options.minimum_allowed_character) | (c > game_options.maximum_allowed_character))
                    {
                        valueformat = false;

                        output_stream << "Your guess contains non-allowed characters, "
                                         "please try again\n";
                    }
                }
            }
        }

        return incode;
    }

} // namespace bulls_and_cows
