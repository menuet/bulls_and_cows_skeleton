
#include "board.hpp"
#include <bulls_and_cows_lib\input.hpp>
#include <bulls_and_cows_lib\random.hpp>
using namespace std;
//#include <string>

namespace bulls_and_cows {

    // TODO: define the body of the functions declared in board.cpp
   Board create_board(const GameOptions& game_options)
    {
        Board gameboard{};
        gameboard.secret_code.value.resize(game_options.number_of_characters_per_code); // else we are out of range
        for (unsigned int i = 0; i < game_options.number_of_characters_per_code; i++)
        {
            gameboard.secret_code.value[i] = generate_random_character(game_options.minimum_allowed_character,
                                                                       game_options.maximum_allowed_character);
        }
        return gameboard;
   }
   bool validate_attempt(const GameOptions& game_options, const Code& attempt)
   {
     
      string result = attempt.value;
       if (result.length() != game_options.number_of_characters_per_code) //return false if the length isn't correct
       {
           return false;
       }

       for (int i = 0; i < result.size(); i++) //return false if the entered-user is out of range
       {
           if (result[i] < game_options.minimum_allowed_character || result[i] > game_options.maximum_allowed_character)

           {
               return false;
           }
       }

       return true;
    }

    Feedback compare_attempt_with_secret_code(const Code& attempt, const Code& secret_code)
    {
        string secret = secret_code.value;
        string result = attempt.value;
        Feedback feed;
        unsigned COWS = 0, BULLS = 0;

        for (int i = 0; i < result.size(); i++)
        {
            if (result[i] == secret[i]) //If the code entered by the user corresponds to secret code
            {
                BULLS++;   //So count the bulls points
            }
        }
        for (int i = 0; i < result.size(); i++)
        {
            if (secret.find(result[i]) != string::npos && result[i] != secret[i])//if the user-entered code or its position is different
            {
                COWS++; //increment the cows points
            }
        }
        feed.cows = COWS; // Displays the cows score
        feed.bulls = BULLS;  // Displays the bulls score
        return feed;

    }

    bool is_end_of_game(const GameOptions& game_options, const Board& board)
    {

        if (board.attempts_and_feedbacks.size() == game_options.max_number_of_attempts) // the number of attempts is reached
        {
            std::cout << " GAME OVER ! Is the end of game ... \n";
            return true;
        }
        else
        {
            return false;
        }
    }

    bool is_win(const GameOptions& game_options, const Board& board)
    {
        if (board.attempts_and_feedbacks.empty())
        {
            return false;
        }
        else if (board.attempts_and_feedbacks.back().attempt.value ==board.secret_code.value) //"back.() -->reference to the last element entered "
        {
            std::cout << "############################ \n";
            std::cout << "           YOU WON !         \n";
            std::cout << "############################ \n";
           
        }
        return true;
        
    }

    void display_board(std::ostream& output_stream, const GameOptions& game_options, const Board& board)
    {

        output_stream <<
            "-------------------------------------\n"
            "| SECRET   * * * * * |              |\n"
            "-------------------------------------\n"
            "| ATTEMPTS           | BULLS | COWS |\n"
            "-------------------------------------\n";
       
        for (unsigned int i = 0; i != board.attempts_and_feedbacks.size(); ++i)
        {
            const auto& attempt_and_feedback = board.attempts_and_feedbacks[i];
            output_stream << " ATTEMPTS #" << (i + 1) << " : " << attempt_and_feedback.attempt.value
                          << "  | BULLS = " << attempt_and_feedback.feedback.bulls
                          << "  | COWS = " << attempt_and_feedback.feedback.cows << "\n";
        }
    }

    Code ask_attempt(std::ostream& output_stream, std::istream& input_stream, const GameOptions& game_options,
                     const Board& board)
    {
        output_stream << "Enter your attempt to discover the secret code" << "\n";
        Code attempt;
        input_stream >> attempt.value;

        while (!validate_attempt(game_options, attempt)) // check if the attempt meet the requirements
        {
                output_stream << " Retry, wrong format !" << endl;
                input_stream >> attempt.value;

        }
        return attempt;


    }
   
}
// namespace bulls_and_cows
