
#include "board.hpp"
#include "random.hpp"

namespace bulls_and_cows {

    // TODO: define the body of the functions declared in board.cpp
    Board create_board(const GameOptions& game_options)
    {
        Board myboard{};

        for (unsigned int i = 0; i < game_options.number_of_characters_per_code; i++)
        {
            auto rand = generate_random_character(game_options.minimum_allowed_character,
                                                  game_options.maximum_allowed_character);

            myboard.secret_code.value.push_back(rand);
        }

        return myboard;
    }

    bool validate_attempt(const GameOptions& game_options, const Code& attempt)
    {
        if (attempt.value.size() == game_options.number_of_characters_per_code)
        {
            for (unsigned int i=0; i<attempt.value.size(); i++)
            {
                if (!(attempt.value[i] >= game_options.minimum_allowed_character && attempt.value[i] <= game_options.maximum_allowed_character))
                {
                    return false;
                }
            }

            return true;
        }
        return false;
    }

    Feedback compare_attempt_with_secret_code(const Code& attempt, const Code& secret_code)
    {
        Feedback myfeedback{};
        int cpt_bulls = 0;
        int cpt_cows = 0;
        unsigned int n = 0;

        for (unsigned int i = 0; i < attempt.value.size(); i++)
        {
            for (unsigned int j = n; j < secret_code.value.size(); j++)
            {
                if (secret_code.value[j] == attempt.value[i])
                {
                    if (i == j)
                    {
                        cpt_bulls++;
                    }
                    else
                    {
                        cpt_cows;
                    }
                }
            }
            n++;
        }

        myfeedback.bulls = cpt_bulls;
        myfeedback.cows = cpt_cows;

        return myfeedback;
    }

    bool is_end_of_game(const GameOptions& game_options, const Board& board)
    {
        board.attempts_and_feedbacks.size() == game_options.max_number_of_attempts;
    }

    bool is_win(const GameOptions& game_options, const Board& board)
    {
        for (AttemptAndFeedback tempo : board.attempts_and_feedbacks)
        {
            if (tempo.feedback.bulls == game_options.number_of_characters_per_code)
            {
                return true;
            }
        }
        return false;
    }

    void display_board(std::ostream& output_stream, const GameOptions& game_options, const Board& board)
    {
        if (is_win(game_options, board) || is_end_of_game(game_options, board))
        {
            output_stream << "Secret Code : " << board.secret_code.value << "\n";
        }
        else
        {
            output_stream << "Secret Code : ";
            for (unsigned int i = 0; i < game_options.number_of_characters_per_code; i++)
            {
                output_stream << "* "
                              << "\n";
            }
        }

        for (auto element : board.attempts_and_feedbacks)
        {
            output_stream << element.attempt.value << " ||||| "
                          << "Bulls : " << element.feedback.bulls << " // Cows : " << element.feedback.cows << "\n";
        }
    }

    Code ask_attempt(std::ostream& output_stream, std::istream& input_stream, const GameOptions& game_options,
                     const Board& board)
    {
        Code attempt{};
        output_stream << "Enter your attempt : ";
        input_stream >> attempt.value;

        return attempt;
    }

} // namespace bulls_and_cows
