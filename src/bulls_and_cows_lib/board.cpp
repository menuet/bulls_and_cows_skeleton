#include "board.hpp"
#include "game_options.hpp"
#include "input.hpp"
#include "random.hpp"
#include <map>

namespace bulls_and_cows {

    // TODO: define the body of the functions declared in board.cpp

    // Create a board and with a new random secret code composed of allowed characters
    Board create_board(const GameOptions& game_options)
    {
        Board boardCreated{};
        boardCreated.secret_code.value.resize(game_options.number_of_characters_per_code, 'O');
        for (unsigned int i = 0; i < game_options.number_of_characters_per_code; i++)
        {
            boardCreated.secret_code.value[i] = generate_random_character(game_options.minimum_allowed_character,
                                                                          game_options.maximum_allowed_character);
        }

        return boardCreated;
    }

    // Validate that a user-entered code contains proper number of allowed characters
    bool validate_attempt(const GameOptions& game_options, const Code& attempt)
    {
        if (attempt.value.size() == game_options.number_of_characters_per_code)
        {
            for (auto i : attempt.value)
            {
                if (i < game_options.minimum_allowed_character || i > game_options.maximum_allowed_character)
                {
                    return false; // character not allowed
                }
            }
        }
        else // the user enters a larger code
        {
            return false;
        }

        return true;
    }

    // Compare a user-entered code with the secret code and give the corresponding number of bulls and cows
    Feedback compare_attempt_with_secret_code(const Code& attempt, const Code& secret_code)
    {
        Feedback feedbackUser{};

        std::map<char, int> map_occurences_secretCode;

        // check bull AND fill a map with the characters and their corresponding occurence found in the SECRET CODE
        // in this map, the character matching a bull are not inserted
        for (int i = 0; i < secret_code.value.length(); i++)
        {
            char secretChar = secret_code.value[i];
            char attemptChar = attempt.value[i];

            if (secretChar == attemptChar)
                feedbackUser.bulls++;
            else
            {
                const auto iter = map_occurences_secretCode.find(secretChar);

                if (iter != map_occurences_secretCode.end()) // secret_code.value[i] exists dans la map
                    ++iter->second;
                else
                    map_occurences_secretCode.insert({secretChar, 1}); // first occurence of this char
            }
        }

        // check cow
        for (int i = 0; i < secret_code.value.length(); i++)
        {
            char secretChar = secret_code.value[i];
            char attemptChar = attempt.value[i];

            if (secretChar != attemptChar)
            {
                if (map_occurences_secretCode.find(attemptChar) !=
                    map_occurences_secretCode.end()) // AttemptChar exists dans la map
                {

                    feedbackUser.cows++;
                    if (map_occurences_secretCode.find(attemptChar)->second == 1)
                    {
                        map_occurences_secretCode.erase(attemptChar);
                    }
                    else
                    {
                        int freq = map_occurences_secretCode.find(attemptChar)->second;
                        freq--;
                        map_occurences_secretCode.erase(attemptChar);
                        map_occurences_secretCode.insert(std::pair<char, int>(attemptChar, freq));
                    }
                }
            }
        }

        return feedbackUser;
    }

    // Ask the user to provide another attempt
    Code ask_attempt(std::ostream& output_stream, std::istream& input_stream, const GameOptions& game_options,
                     const Board& board)
    {
        Code user_choice{};
        std::string s;

        s = (board.attempts_and_feedbacks.size() < 9) ? "What is your guess #0" : "What is your guess #";

        output_stream << s << board.attempts_and_feedbacks.size() + 1 << " ("
                      << game_options.number_of_characters_per_code << " characters between '"
                      << game_options.minimum_allowed_character << "' and '" << game_options.maximum_allowed_character
                      << "')\n"
                         "? ";
        user_choice.value = ask_string(input_stream); // ask the user to provide a string

        bool validate = validate_attempt(game_options, user_choice);
        if (!validate)
        {
            output_stream << "Your guess has an invalid length or contains non-allowed characters, please try again\n";
            user_choice = ask_attempt(output_stream, input_stream, game_options, board);
        }

        return user_choice;
    }

    // Test if the last attempt is a win
    bool is_win(const GameOptions& game_options, const Board& board)
    {
        if (board.attempts_and_feedbacks.empty())
        {
            return false;
        }
        // if the nb of bulls == the length of the secret code, then the player wins
        if (board.attempts_and_feedbacks.back().feedback.bulls == game_options.number_of_characters_per_code)
        {
            return true;
        }

        return false;
    }

    // Test if this is the end of the game
    bool is_end_of_game(const GameOptions& game_options, const Board& board)
    {
        if (board.attempts_and_feedbacks.empty())
        {
            return false;
        }
        if (board.attempts_and_feedbacks.size() == game_options.max_number_of_attempts || is_win(game_options, board))
        {
            return true; // end of the game if max attempts reached or if nb of bulls == the length of the secret code;
        }
        return false;
    }

    void display_board_borders(std::ostream& output_stream, const GameOptions& game_options)
    {
        output_stream << "-----------";
        for (unsigned int i = 0; i < game_options.number_of_characters_per_code; i++)
        {
            output_stream << "--";
        }

        output_stream << "----------------\n";
    }

    void display_board(std::ostream& output_stream, const GameOptions& game_options, const Board& board)
    {

        int lengthCode = game_options.number_of_characters_per_code;

        display_board_borders(output_stream, game_options);

        output_stream << "| SECRET   ";
        if (!is_end_of_game(game_options, board))
        {
            for (int i = 0; i < lengthCode; i++)
            {
                output_stream << "* ";
            }
        }
        else
        {
            for (int i = 0; i < lengthCode; i++)
            {
                output_stream << board.secret_code.value[i] << " ";
            }
        }
        output_stream << "|              |\n";

        display_board_borders(output_stream, game_options);

        output_stream << "| ATTEMPTS ";
        for (int i = 0; i < lengthCode; i++)
        {
            output_stream << "  ";
        }
        output_stream << "| BULLS | COWS |\n";

        display_board_borders(output_stream, game_options);

        std::string s;
        for (int i = game_options.max_number_of_attempts - 1; i >= 0; i--)
        {
            if (board.attempts_and_feedbacks.empty())
            {
                s = (i < 9) ? "| #0" : "| #";
                output_stream << s << i + 1 << "      ";
                for (int j = 0; j < lengthCode; j++)
                {
                    output_stream << ". ";
                }
                output_stream << "|       |      |\n";
            }
            else
            {
                s = (i < 9) ? "| #0" : "| #";
                output_stream << s << i + 1 << "      ";

                if (board.attempts_and_feedbacks.size() < (i + 1))
                {
                    for (int j = 0; j < lengthCode; j++)
                    {
                        output_stream << ". ";
                    }
                    output_stream << "|       |      |\n";
                }
                else
                {
                    for (int j = 0; j < lengthCode; j++)
                    {
                        output_stream << board.attempts_and_feedbacks[i].attempt.value[j] << " ";
                    }
                    output_stream << "|   " << board.attempts_and_feedbacks[i].feedback.bulls << "   |   "
                                  << board.attempts_and_feedbacks[i].feedback.cows << "  |\n";
                }
            }
        }

        display_board_borders(output_stream, game_options);
    }

} // namespace bulls_and_cows
