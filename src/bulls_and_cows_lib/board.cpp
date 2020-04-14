
#include "board.hpp"
#include"random.cpp"

namespace bulls_and_cows {

    using namespace std;

    Board create_board(const GameOptions& game_options)
    {
        Board board;
        for( int i=0; i< game_options.number_of_characters_per_code; i++)
        {
            board.secret_code.value+=generate_random_character(game_options.minimum_allowed_character,
                                                                game_options.maximum_allowed_character);
        }
        return board;
    }

     bool validate_attempt(const GameOptions& game_options, const Code& attempt)
     {
         int h(0);
         if(attempt.value.length() !=game_options.number_of_characters_per_code )
         {
             return false;
             h+=1;
         }
         for (int i = 0; i < attempt.value.length(); i++)
         {
             if (attempt.value[i] < game_options.minimum_allowed_character ||  attempt.value[i] > game_options.maximum_allowed_character)
             {
                 return false;
                 h+=1;
             }
         }
         if (h==0)
         {
             return true;
         }

     }

     Feedback compare_attempt_with_secret_code(const Code& attempt, const Code& secret_code)
     {
         Feedback feedback;
         int bulls (0);
         int cows (0);
         vector<bool> ChoixValide;

         for (int i=0; i< attempt.value.length();i++)
         {
             if (attempt.value[i]==secret_code.value[i])
             {
                 ChoixValide(true);
                 bulls+=1;

             }
             else
            {
                ChoixValide(false);
            }
         }
         for (int i=0; i<attempt.value.length();i++)
         {
             if(ChoixValide[i]==false)
             {
                 for (int j=0; i<attempt.value.length();j++)
                 {
                     if(j!=i)
                     {
                         if(secret_code.value[i]==attempt.value[j] && ChoixValide[j]==false)
                         {
                             ChoixValide[j]=true;
                             cows+=1;

                         }
                     }
                 }
             }

         }
         feedback.bulls=bulls;
         feedback.cows=cows;
         return feedback;

     }

     bool is_end_of_game(const GameOptions& game_options, const Board& board)
     {
         if (game_options.max_number_of_attempts != board.attempts_and_feedbacks.size())
         {
             return false;
         }
         return true;
     }

      bool is_win(const GameOptions& game_options, const Board& board)
      {
          int i(0);
          if (board.attempts_and_feedbacks.empty())
        {
            return false;
        }
        else
            {
                while(secret_code.value[i]==attempt.value[i] && i<attempt.value.length())
                {
                    i+=+;
                }

            }
        if (i==attempt.value.length())
        {
            return true;
        }
      }

      void display_board(std::ostream& output_stream, const GameOptions& game_options, const Board& board)
      {

          if (is_win(game_options, board) || is_end_of_game(game_options, board))
          {
              cout<<secret.code;
          }

      }

      Code ask_attempt(std::ostream& output_stream, std::istream& input_stream, const GameOptions& game_options,const Board& board)
      {
          Code guess;
          cout<<"Write your guess";
          cin>> guess.value;

          while (validate.attempt==false)
          {
              cout<<"Your attempt don't respect the condition, please try again";
              cin>>guess.value;
          }

          return guess;


      }



    // TODO: define the body of the functions declared in board.cpp

} // namespace bulls_and_cowsws
