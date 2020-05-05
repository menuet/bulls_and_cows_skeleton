
#include "board.hpp"
#include "input.hpp"
using namespace std;

namespace bulls_and_cows {

    // TODO: define the body of the functions declared in board.cpp

    string addSpaceBetweenAllChar(string s)
    {
        int n = (int)s.length();
        string nouvStr = "";

        for (int i = 0; i < n; i++)
        {
            nouvStr = nouvStr + s[i] + " ";
        }

        return nouvStr;
    }

    bool isAlphabaticOrder(string s)
    {
        int n = (int)s.length();

        for (int i = 1; i < n; i++)
        {

            // if element at index 'i' is less
            // than the element at index 'i-1'
            // then the string is not sorted
            if (s[i] < s[i - 1])
                return false;
        }

        return true;
    }

    bool isStrUpper(string s)
    {
        int n = (int)s.length();

        for (int i = 1; i < n; i++)
        {

            // if element at index 'i' is less
            // than the element at index 'i-1'
            // then the string is not sorted
            if (!isupper((char)s[i]))
                return false;
        }

        return true;
    }

    int count_occurence_char(string s, char c)
    {
        int count = 0;

        for (int i = 0; i < s.size(); i++)
            if (s[i] == c)
                count++;

        return count;
    }

    Board create_board(const GameOptions& game_options)
    {
        Board board{};
        Code code{};
        const int MAX = 26;

        char alphabet[MAX] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M',
                              'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};

        string ordAsc = "";
        string ordDesc = "";
        string c = "";
        string strCode = "";

        // while (strCode.size < 5)
        // {
        while (strCode.size() < (int)game_options.number_of_characters_per_code)
        {
            // res = res + alphabet[rand() % MAX];
            c = alphabet[rand() % MAX];
            ordAsc = c + "H";
            ordDesc = "A" + c;

            if (isAlphabaticOrder(ordAsc) && isAlphabaticOrder(ordDesc))
            {
                strCode = strCode + c;
            }
        }
        // }

        code.value = strCode;
        board.secret_code = code;
        return board;
    }

    void display_board(std::ostream& output_stream, const GameOptions& game_options, const Board& board)
    {

        output_stream << "\n-------------------------------------\n";
        output_stream << "| SECRET   ";
        if (is_end_of_game(game_options, board))
            output_stream << addSpaceBetweenAllChar(board.secret_code.value);
        else
            for (int i = 0; i < (int)game_options.number_of_characters_per_code; i++)
            {
                output_stream << "* ";
            }
        output_stream << "|              |\n";
        output_stream << "| ATTEMPTS ";
        for (int i = 0; i < (int)game_options.number_of_characters_per_code; i++)
        {
            output_stream << "  ";
        }
        output_stream << "| BULLS | COWS |\n";
        output_stream << "-------------------------------------\n";

        for (int j = (int)game_options.max_number_of_attempts; j > 0; j--)
        {
            if (j < 10)
                output_stream << "| #0" << j << "      ";
            else
                output_stream << "| #" << j << "      ";

            if (board.attempts_and_feedbacks.size() > 0)
            {
                for (std::vector<AttemptAndFeedback>::size_type k = 0; k < board.attempts_and_feedbacks.size(); k++)
                {
                    if ((k + 1) == j)
                    {
                        output_stream << addSpaceBetweenAllChar(board.attempts_and_feedbacks[k].attempt.value);
                    }
                }
            }
            if (j > board.attempts_and_feedbacks.size())
            {
                for (int i = 0; i < (int)game_options.number_of_characters_per_code; i++)
                {
                    output_stream << ". ";
                }
            }

            if (board.attempts_and_feedbacks.size() > 0 && j <= board.attempts_and_feedbacks.size())
            {
                for (std::vector<AttemptAndFeedback>::size_type k = 0; k < board.attempts_and_feedbacks.size(); k++)
                {
                    if ((k + 1) == j)
                        output_stream << "|   " << board.attempts_and_feedbacks[k].feedback.bulls << "   |   "
                                      << board.attempts_and_feedbacks[k].feedback.cows << "  |\n";
                }
            }
            else
                output_stream << "|       |      |\n";
        }
        output_stream << "-------------------------------------\n";
    }

    bool validate_attempt(const GameOptions& game_options, const Code& attempt)
    {
        if (!attempt.value.empty() && attempt.value.size() == game_options.number_of_characters_per_code)
        {
            if (!isStrUpper(attempt.value))
                return false;
            else
                return true;
        }
        return false;
    }

    Feedback compare_attempt_with_secret_code(const Code& attempt, const Code& secret_code)
    {
        Feedback feedback{};
        int bulls = 0;
        int cows = 0;
        string charsWithDifPosition = "";

        for (int i = 0; i < secret_code.value.size(); i++)
        {
            if (secret_code.value[i] == attempt.value[i])
                bulls++;
        }

        for (int i = 0; i < secret_code.value.size(); i++)
        {
            if (secret_code.value[i] != attempt.value[i] &&
                count_occurence_char(secret_code.value, attempt.value[i]) > 0)
            {
                if (count_occurence_char(attempt.value, attempt.value[i]) > 1 &&
                    count_occurence_char(charsWithDifPosition, attempt.value[i]) == 0)
                    charsWithDifPosition = charsWithDifPosition + attempt.value[i];
                cows++;
            }
        }

        for (int i = 0; i < charsWithDifPosition.size(); i++)
        {
            int nbOccurInSecCode = count_occurence_char(secret_code.value, charsWithDifPosition[i]);
            int nbOccurInAttempt = count_occurence_char(attempt.value, charsWithDifPosition[i]);

            if (nbOccurInSecCode > nbOccurInAttempt)
            {
                int diff = nbOccurInSecCode - nbOccurInAttempt;
                cows = cows - diff;
            }
            else if (nbOccurInAttempt > nbOccurInSecCode)
            {
                int diff = nbOccurInAttempt - nbOccurInSecCode;
                cows = cows - diff;
            }
        }

        feedback.bulls = bulls;
        feedback.cows = cows;
        return feedback;
    }

    Code ask_attempt(std::ostream& output_stream, std::istream& input_stream, const GameOptions& game_options,
                     const Board& board)
    {
        output_stream << "What is your guess #";
        if (board.attempts_and_feedbacks.size() < 1)
            output_stream << "01";
        else
        {
            if (board.attempts_and_feedbacks.size() + 1 < 10)
                output_stream << "0" << board.attempts_and_feedbacks.size() + 1;
            else
                output_stream << board.attempts_and_feedbacks.size() + 1;
        }

        output_stream << " (" << game_options.number_of_characters_per_code << " characters between '"
                      << game_options.minimum_allowed_character << "' and '" << game_options.maximum_allowed_character
                      << "')\n?";
        std::string v = ask_string(input_stream);
        Code attempt{};
        attempt.value = v;
        bool isValidAttempt = validate_attempt(game_options, attempt);

        while (!isValidAttempt)
        {
            output_stream << "Your guess has invalid length or contains non- allowed characters, please try again\n";
            output_stream << "What is your guess #";
            if (board.attempts_and_feedbacks.size() < 1)
                output_stream << "01";
            else
            {
                if (board.attempts_and_feedbacks.size() + 1 < 10)
                    output_stream << "0" << board.attempts_and_feedbacks.size() + 1;
                else
                    output_stream << board.attempts_and_feedbacks.size() + 1;
            }

            output_stream << " (" << game_options.number_of_characters_per_code << " characters between '"
                          << game_options.minimum_allowed_character << "' and '"
                          << game_options.maximum_allowed_character << "')\n?";
            v = ask_string(input_stream);
            attempt.value = v;
            isValidAttempt = validate_attempt(game_options, attempt);
        }
        return attempt;
    }

    bool is_end_of_game(const GameOptions& game_options, const Board& board)
    {
        if (board.attempts_and_feedbacks.size() == (int)game_options.max_number_of_attempts)
            return true;
        if (is_win(game_options, board))
            return true;
        return false;
    }

    bool is_win(const GameOptions& game_options, const Board& board)
    {
        if (board.attempts_and_feedbacks.size() &&
            board.attempts_and_feedbacks[board.attempts_and_feedbacks.size() - 1].attempt.value ==
                board.secret_code.value)
        {

            return true;
        }

        return false;
    }

} // namespace bulls_and_cows
