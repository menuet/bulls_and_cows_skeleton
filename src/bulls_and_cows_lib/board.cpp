
#include "board.hpp"

namespace bulls_and_cows {

    // TODO: define the body of the functions declared in board.cpp
    // Create a board and with a new random secret code composed of allowed characters
    Board create_board(const GameOptions& game_options)
    {
        Board board;
         

        for (int unsigned i = 0; i < game_options.number_of_characters_per_code; i++)
        {
            board.secret_code.value =
                board.secret_code.value + generate_random_character(game_options.minimum_allowed_character,
                                                                    game_options.maximum_allowed_character);
        }

        return board;
    }

    // Validate that a user-entered code contains proper number of allowed characters
    bool validate_attempt(const GameOptions& game_options, const Code& attempt)
    {
      

        if (attempt.value.size() == game_options.number_of_characters_per_code)
        {
            for (int unsigned i = 0; i < game_options.number_of_characters_per_code; i++)
            {
                if (attempt.value[i] < game_options.minimum_allowed_character ||
                    attempt.value[i] > game_options.maximum_allowed_character)
                {
                    return false;
                }
            }
                return true;
        }
        return false;
        
    }

 

    // Compare a user-entered code with the secret code and give the corresponding number of bulls and cows
    Feedback compare_attempt_with_secret_code(Code attempt,Code secret_code)
    {
       
        Feedback feedback;
       

        for (int unsigned i = 0; i < attempt.value.size();i++)
        {
            if (attempt.value[i] == secret_code.value[i])
            {

                attempt.value.erase(i, 1);
                secret_code.value.erase(i, 1);

                feedback.bulls++;

                i--;
            }
           
        }

        for (int unsigned i = 0; i < secret_code.value.size(); i++)
        {
            for (int unsigned j = 0; j < attempt.value.size(); j++)

            if (attempt.value[j]==secret_code.value[i])
            {
                attempt.value.erase(j, 1);
                feedback.cows++;
                i--;
            }
                
        }

        return feedback;
    }

    // Test if this is the end of the game
    bool is_end_of_game(const GameOptions& game_options, const Board& board)
    {
        if (game_options.max_number_of_attempts == board.attempts_and_feedbacks.size())
        {
            return true;
        }
        return false;
    }

    // Test if the last attempt is a win
    bool is_win(const GameOptions& game_options, const Board& board)
    {

        if (board.attempts_and_feedbacks.empty())
            return false;
        else if (board.attempts_and_feedbacks.back().attempt.value == board.secret_code.value)
        {
            return true;
        }
        else
            return false;
    }

    // Display the scret code and the list of attempts of the board
    void display_board(std::ostream& output_stream, const GameOptions& game_options, const Board& board)
    {
       

        std::string secretmot{};
        if (!is_end_of_game(game_options, board) && !is_win(game_options, board))
        {
            for (int unsigned i = 0; i < board.secret_code.value.size(); i++)
                secretmot = secretmot + "*";
        }
        else
            secretmot = board.secret_code.value;

            output_stream << "-----------------------------------------\n";
        output_stream << "| Secret\t" << secretmot << "\t|\t\t|\n";
        output_stream << "-----------------------------------------\n";
        output_stream << "| ATTEMPTS\t\t| BULLS | COWS  |\n ";
        output_stream << "-----------------------------------------\n";

        std::string affiche{};
        for (int unsigned i = 0; i < game_options.number_of_characters_per_code; i++)
            affiche = affiche + "-";

        for (int unsigned i = game_options.max_number_of_attempts; i > board.attempts_and_feedbacks.size(); i--)
        {
            if (i < 10)
                output_stream << "| #0" << i << "\t\t"<<affiche<<"\t|\t|\t|\n";
            else
                output_stream << "| #" << i << "\t\t" << affiche <<"\t|\t|\t|\n";
        }

        if (!board.attempts_and_feedbacks.empty())
        {
            for (size_t j = board.attempts_and_feedbacks.size(); j > 0; j--)
            {
                const auto& ValueMot = board.attempts_and_feedbacks[j - 1].attempt.value;
                const auto& bulls = board.attempts_and_feedbacks[j - 1].feedback.bulls;
                const auto& cows = board.attempts_and_feedbacks[j - 1].feedback.cows;
                if (j < 10)
                    output_stream << "| #0" << j << "\t\t" << ValueMot << "\t|  " << bulls << "\t|  "
                                  << cows << "\t|\n";
                else
                    output_stream << "| #" << j << "\t\t" << ValueMot << "\t|  " << bulls << "\t|  " << cows
                                  << "\t|\n";
            }
        }

        output_stream << "-----------------------------------------\n";
    }

    // Ask the user to provide another attempt
    Code ask_attempt(std::ostream& output_stream, std::istream& input_stream, const GameOptions& game_options,
                     const Board& board)
    {
        bool verif = false;
        Code code;
        while (!verif)
        {
            if (board.attempts_and_feedbacks.size() < 10)
                output_stream << "What is your guess #0";
            else
                output_stream << "What is your guess #";

            output_stream << board.attempts_and_feedbacks.size() + 1;
            output_stream << " (" << game_options.number_of_characters_per_code;
            output_stream << " characters between '" << game_options.minimum_allowed_character << "' and '"
                          << game_options.maximum_allowed_character << "' )\n?";

            input_stream >> code.value;

            for (int unsigned i = 0; i < code.value.size(); i++)
            {
                if (code.value[i] >= 'a' && code.value[i] <= 'z')
                     code.value[i] = code.value[i] - 32;
            }
               

            verif = validate_attempt(game_options, code);
        }

        return code;
    }

} // namespace bulls_and_cows
