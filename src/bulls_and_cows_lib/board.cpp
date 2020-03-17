
#include "board.hpp"

namespace bulls_and_cows {

    // TODO: define the body of the functions declared in board.cpp
    Board create_board(const GameOptions& game_options)
    {
        //std::vector<char> answer{};
        std::string answer = "";
        for (unsigned int i = 0U; i < game_options.number_of_characters_per_code; i++)
        {
            char temp = bulls_and_cows::generate_random_character(game_options.minimum_allowed_character,
                                                                  game_options.maximum_allowed_character);
            answer += temp;
        }
        //Creating board and assiging the secret code created above
        Board myboard{};
        myboard.secret_code.value = answer;
        return myboard;
    }


    bool validate_attempt(const GameOptions& game_options, const Code& attempt)
    {
        if (attempt.value.size = game_options.number_of_characters_per_code)
            return true;
        else
            return false;
    }

    Feedback compare_attempt_with_secret_code(const Code& attempt, const Code& secret_code)
    {
        Feedback myfeed;
        for (int i = 0; i < secret_code.value.size; i++)
        {
            char temp = secret_code.value[i];
            for (int j = 0; j < attempt.value.size; j++)
            {
                if (secret_code.value.find(attempt.value[j]))
                    myfeed.cows++;
                if (temp == attempt.value[j])
                    myfeed.bulls++;
            }
        }
        return myfeed;
    }

    bool is_end_of_game(const GameOptions& game_options, const Board& board)
    {

        return true;
    }




} // namespace bulls_and_cows
