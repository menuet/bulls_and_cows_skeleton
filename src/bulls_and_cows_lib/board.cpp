
#include "board.hpp"

namespace bulls_and_cows {

    
#include "board.hpp"
#include "random.hpp"
#include <algorithm>

    namespace bulls_and_cows {
        using namespace std;
        Board create_board(const GameOptions& game_options)
        {
            Board board;
            std::string code{};
            for (unsigned i = 0; i < game_options.number_of_characters_per_code; i++)
            {
                code += generate_random_character(game_options.minimum_allowed_character,
                                                  game_options.maximum_allowed_character);
            }
            board.secret_code.value = code;
            return board;
        }

        bool validate_attempt(const GameOptions& game_options, const Code& attempt)
        {
            if (attempt.value.length() != game_options.number_of_characters_per_code)
            {
                return false;
            }

            for (unsigned i = 0; i < game_options.number_of_characters_per_code; i++)
            {
                if (attempt.value[i] < game_options.minimum_allowed_character ||
                    attempt.value[i] > game_options.maximum_allowed_character)
                {
                    return false;
                }
            }

            return true;
        }

        bool is_end_of_game(const GameOptions& game_options, const Board& board)
        {
            if (board.attempts_and_feedbacks.size() == game_options.max_number_of_attempts)
            {
                return true;
            }
            return false;
        }

        bool is_win(const GameOptions& game_options, const Board& board)
        {
            if (board.attempts_and_feedbacks.back().attempt.value == board.secret_code.value)
            {
                return true;
            }
            return false;
        }

        Code ask_attempt(std::ostream& output_stream, std::istream& input_stream, const GameOptions& game_options,
                         const Board& board)
        {
            AttemptAndFeedback attemptfeedback;
            Code attempt;
            do
            {
                output_stream << "Please Enter a string of " << game_options.maximum_allowed_character << "characters"
                              << endl;
                input_stream >> attempt.value;
            } while (!validate_attempt(game_options, attempt));
            return attempt;
        }

    } // namespace bulls_and_cows
