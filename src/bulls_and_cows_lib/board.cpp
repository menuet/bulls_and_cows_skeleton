
#include "board.hpp"
#include "random.cpp"
namespace bulls_and_cows {
   
    
    Board create_board(const GameOptions& game_options)
    {
        Board board;
        std::string code{};
        for (unsigned i = 0; i < game_options.number_of_characters_per_code; i++)
        {
            code = code + generate_random_character(game_options.minimum_allowed_character,
                                                    game_options.maximum_allowed_character);
        }
        board.secret_code.value = code;
        return board;
    }

    bool validate_attempt(const GameOptions& game_options, const Code& attempt)
    {
        for (unsigned i = 0; i < game_options.number_of_characters_per_code; i++)
        {
            if (attempt.value[i] < game_options.minimum_allowed_character ||
                attempt.value[i] > game_options.maximum_allowed_character)
            {
                return false;
            }
        }
        if (attempt.value.size() != game_options.number_of_characters_per_code)
        {
            return false;
        }
        return true;
    }
    // TODO: define the body of the functions declared in board.cpp

} // namespace bulls_and_cows
