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
        std::string code;
        char c;
        unsigned int nbChara = game_options.number_of_characters_per_code;

        for (unsigned int i = 0; i < nbChara; i++)
        {
            c = generate_random_character(game_options.minimum_allowed_character,
                                          game_options.maximum_allowed_character);
            code += c;
        }

        boardCreated.secret_code.value = code;

        return boardCreated;
    }

    // Validate that a user-entered code contains proper number of allowed characters
    bool validate_attempt(const GameOptions& game_options, const Code& attempt)
    {
        unsigned int nbChara = game_options.number_of_characters_per_code;
        char miniC = game_options.minimum_allowed_character;
        char maxiC = game_options.maximum_allowed_character;

        if (attempt.value.size() == nbChara)
        {
            for (unsigned int i = 0; i < nbChara; i++)
            {
                if (attempt.value[i] < miniC || attempt.value[i] > maxiC)
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
        feedbackUser.bulls = 0;
        feedbackUser.cows = 0;

        std::map<char, int> map;

        // check bull
        for (int i = 0; i < secret_code.value.length(); i++)
        {
            char secretChar = secret_code.value[i];
            char attemptChar = attempt.value[i];

            if (secretChar == attemptChar)
            {
                feedbackUser.bulls++;
            }
            else
            {
                if (map.find(secretChar) != map.end()) // secret_code.value[i] exists dans la map
                {
                    int freq = map.find(secretChar)->second; // on augmente le nombre d'occurence de ce character
                    freq++;
                    map.erase(secretChar);
                    map.insert(std::pair<char, int>(secretChar, freq));
                }
                else
                {
                    map.insert(std::pair<char, int>(secretChar, 1)); // first occurence of this char
                }
            }
        }

        // check cow
        for (int i = 0; i < secret_code.value.length(); i++)
        {
            char secretChar = secret_code.value[i];
            char attemptChar = attempt.value[i];

            if (secretChar != attemptChar)
            {
                if (map.find(attemptChar) != map.end()) // AttemptChar exists dans la map
                {

                    feedbackUser.cows++;
                    if (map.find(attemptChar)->second == 1)
                    {
                        map.erase(attemptChar);
                    }
                    else
                    {
                        int freq = map.find(attemptChar)->second;
                        freq--;
                        map.erase(attemptChar);
                        map.insert(std::pair<char, int>(attemptChar, freq));
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
        ;

        if (game_options.number_of_characters_per_code < 9)
        {
            output_stream << "What is your guess #0" << board.attempts_and_feedbacks.size() + 1 << " ("
                          << game_options.number_of_characters_per_code
                          << " characters between '" << game_options.minimum_allowed_character << "' and '"
                          << game_options.maximum_allowed_character
                          << "')\n"
                             "? ";
        
        }
        else
        {

            output_stream << "What is your guess #"<< board.attempts_and_feedbacks.size() + 1 <<" (" << game_options.number_of_characters_per_code
                          << " characters between '" << game_options.minimum_allowed_character << "' and '"
                          << game_options.maximum_allowed_character
                          << "')\n"
                             "? ";
        }


        user_choice.value = ask_string(input_stream); // ask the user to provide a string

        bool validate = validate_attempt(game_options, user_choice);
        if (validate == 0)
        {
            output_stream << "Your guess has an invalid length or contains non-allowed characters, please try again\n";
            user_choice = ask_attempt(std::cout, std::cin, game_options, board);
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
        // if the nb of bulls == the length of the secret code
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
        if (board.attempts_and_feedbacks.size() == game_options.max_number_of_attempts ||
            is_win(game_options, board) == true)
        {
            return true; // end of the game;
        }
        return false;
    }

    void display_board(std::ostream& output_stream, const GameOptions& game_options, const Board& board)
    {

        int nb = game_options.max_number_of_attempts;
        int lengthCode = game_options.number_of_characters_per_code;

        output_stream << "-----------";
        for (int i = 0; i < lengthCode; i++)
        {
            output_stream << "--";
        }

        output_stream << "----------------\n";

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

        output_stream << "-----------";
        for (int i = 0; i < lengthCode; i++)
        {
            output_stream << "--";
        }
        output_stream << "----------------\n";

        output_stream << "| ATTEMPTS ";
        for (int i = 0; i < lengthCode; i++)
        {
            output_stream << "  ";
        }
        output_stream << "| BULLS | COWS |\n";

        output_stream << "-----------";
        for (int i = 0; i < lengthCode; i++)
        {
            output_stream << "--";
        }
        output_stream << "----------------\n";

        for (int i = nb - 1; i >= 0; i--)
        {
            if (board.attempts_and_feedbacks.empty())
            {
                if (i < 9)
                {
                    output_stream << "| #0" << i + 1 << "      ";
                    for (int j = 0; j < lengthCode; j++)
                    {
                        output_stream << ". ";
                    }
                    output_stream << "|       |      |\n";
                }
                else
                {
                    output_stream << "| #" << i + 1 << "      ";
                    for (int j = 0; j < lengthCode; j++)
                    {
                        output_stream << ". ";
                    }
                    output_stream << "|       |      |\n";
                }
            }
            else
            {
                if (i < 9)
                {
                    output_stream << "| #0" << i + 1 << "      ";

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
                else
                {
                    output_stream << "| #" << i + 1 << "      ";

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
        }

        output_stream << "-----------";
        for (int i = 0; i < lengthCode; i++)
        {
            output_stream << "--";
        }
        output_stream << "----------------\n";
    }

} // namespace bulls_and_cows
