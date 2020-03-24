
#include "board.hpp"
#include "random.hpp"
#include <iostream>
namespace bulls_and_cows {
    //Checked
   Board create_board(const GameOptions& game_options)
    {
        Board ans;

        for (unsigned int i = 0U; i < game_options.number_of_characters_per_code; i++)
        {
            if (game_options.maximum_allowed_character >= 65 && game_options.maximum_allowed_character <= 90 &&
                game_options.minimum_allowed_character >= 65 && game_options.minimum_allowed_character <= 90)
            {
                ans.secret_code.value = ans.secret_code.value + bulls_and_cows::generate_random_character(
                                                                    game_options.minimum_allowed_character,
                                                                    game_options.maximum_allowed_character);
            }

            else if(game_options.maximum_allowed_character >= 48 && game_options.maximum_allowed_character <= 57 &&
                     game_options.minimum_allowed_character >= 48 && game_options.minimum_allowed_character <= 57)
            {
                ans.secret_code.value = ans.secret_code.value + (char)bulls_and_cows::generate_random_integer(
                                                                    game_options.minimum_allowed_character,
                                                                    game_options.maximum_allowed_character);
            }

            else
            {
                
            }
            
            
        }
        return ans;
    }
        //Checked
       bool validate_attempt(const GameOptions& game_options, const Code& attempt)
       {
           if (game_options.number_of_characters_per_code == attempt.value.size())
           {
               for (const char& c : attempt.value)
               {
                   if ((c < game_options.minimum_allowed_character) | (c > game_options.maximum_allowed_character))
                   {
                       return false;
                   }
               }
               return true;
           }
           else
           {
               return false;
           }
               
       }
    //Checked 1-2
       Feedback compare_attempt_with_secret_code(const Code& attempt, const Code& secret_code)
       {
           Feedback myfeed{};
           std::string tmp_secret_code = secret_code.value;
           std::string tmp_attempt = attempt.value;
           std::size_t found;
           // bulls managing
           for (int i = 0; i < tmp_secret_code.size(); i++)
           {
               if (tmp_secret_code[i] == tmp_attempt[i])
               {
                   tmp_attempt.erase(i, 1);
                   tmp_secret_code.erase(i, 1);
                   myfeed.bulls++;
                   i--;
               }
           }

           // cows managing
           for (int j = 0; j < tmp_attempt.size(); j++)
           {
               found = tmp_secret_code.find(tmp_attempt[j]);
               if (found != std::string::npos)
               {
                   tmp_secret_code.erase(tmp_secret_code.find(tmp_attempt[j]), 1);
                   myfeed.cows++;
                   std::cout << tmp_attempt[j] << "-" << myfeed.cows << "  " << tmp_secret_code.find(tmp_attempt[j])
                             << "\n";
               }
           }

           return myfeed;
       }
       //Checked 
       bool is_end_of_game(const GameOptions& game_options, const Board& board)
       {
           if (game_options.max_number_of_attempts == board.attempts_and_feedbacks.size())
           {
               return true;
           }
           return false;
       }
       
       
       //Checked
       bool is_win(const GameOptions& game_options, const Board& board)
       {
           if ((board.attempts_and_feedbacks.empty())) 
               return false;
           if (board.attempts_and_feedbacks.back().attempt.value == board.secret_code.value)
           {
               std::cout << "You won !! GG WP";
               return true;
           }

           return false;
       }



       // SIMPLE TEST
       /*void display_board(std::ostream & output_stream, const GameOptions & game_options, const Board & board)
       {
           output_stream << "Secret code (for debugging and cheating) = " << board.secret_code.value << "\n";
           for (unsigned int index = 0; index < board.attempts_and_feedbacks.size(); ++index)
           {
               const auto& attempt_and_feedback = board.attempts_and_feedbacks[index];
               const auto& attempt = attempt_and_feedback.attempt;
               const auto& feedback = attempt_and_feedback.feedback;
               output_stream << "Attempt #" << (index + 1) << " = " << attempt.value << " | Bulls = " << feedback.bulls
                   << " | Cows = " << feedback.cows << "\n";
           }
       }
       */

       std::string moins_function(int number, std::string loopadd)
       {
           std::string moins = "";
           for (int i = 0; i < number; i++)
           {
               moins += loopadd;
           }
           return moins;
       }

       void print_code(std::string code)
       {
           char* ccode = const_cast<char*>(code.c_str());
           std::string codewspace = "";
           for (int i = 0; i < code.length(); i++)
           {
               std::cout << ccode[i] << " ";
           }
       }

       void display_board(std::ostream& output_stream, const GameOptions& game_options, const Board& board)
       {
           // HEAD ...
           output_stream << "Secret code (for debugging and cheating) = " << board.secret_code.value << "\n";
           output_stream << "-----------" << moins_function(game_options.number_of_characters_per_code, "--") << "--"
                         << "---------------\n";
           output_stream << "| SECRET   " << moins_function(game_options.number_of_characters_per_code, "* ") << "| "
                         << "              |\n";
           output_stream << "-----------" << moins_function(game_options.number_of_characters_per_code, "--") << "--"
                         << "---------------\n";
           output_stream << "| ATTEMPTS " << moins_function(game_options.number_of_characters_per_code, "  ") << "| "
                         << " BULLS | COWS |\n";
           output_stream << "-----------" << moins_function(game_options.number_of_characters_per_code, "--") << "--"
                         << "---------------\n";
           //...

           // BODY ...
           int number_of_attemps = game_options.max_number_of_attempts;
           for (unsigned int i = number_of_attemps; i > board.attempts_and_feedbacks.size(); i--)
           {
               if (i >= 10)
               {
                   output_stream << "| #" << i << "      "
                                 << moins_function(game_options.number_of_characters_per_code, ". ")
                                 << "|       |       |\n";
               }
               else
               {
                   output_stream << "| #0" << i << "      "
                                 << moins_function(game_options.number_of_characters_per_code, ". ")
                                 << "|       |       |\n";
               }
           }

           if (!board.attempts_and_feedbacks.empty())
           {
               for (size_t index = board.attempts_and_feedbacks.size(); index > 0; --index)
               {
                   const auto& attempt_and_feedback = board.attempts_and_feedbacks[index - 1];
                   const auto& attempt = attempt_and_feedback.attempt;
                   // std::cout <<"VALUE "<<attempt.value<<"\n";
                   const auto& feedback = attempt_and_feedback.feedback;
                   if (index >= 10)
                   {
                       output_stream << "| #" << index << "      ";
                       print_code(attempt.value);
                       output_stream << "|   " << feedback.bulls << "   |   " << feedback.cows << "   |\n";
                   }
                   else
                   {
                       output_stream << "| #0" << index << "      ";
                       print_code(attempt.value);
                       output_stream << "|   " << feedback.bulls << "   |   " << feedback.cows << "   |\n";
                   }
               }
           }
           //...

           // FOOTER ...
           output_stream << "-----------" << moins_function(game_options.number_of_characters_per_code, "--") << "-"
                         << "----------------\n";
           //...
       }
       
       //Checked display (not working though)
       /*
       void display_board(std::ostream& output_stream, const GameOptions& game_options, const Board& board)
       {
           

           if ((board.attempts_and_feedbacks.empty())) // printing if player hasn't played already
           {
               output_stream << "-------------------------------------\n"
                                "| SECRET   * * * * * |              |\n"
                                "-------------------------------------\n"
                                "| ATTEMPTS           | BULLS | COWS |\n"
                                "-------------------------------------\n"
                                "| #12      . . . . . |       |      |\n"
                                "| #11      . . . . . |       |      |\n"
                                "| #10      . . . . . |       |      |\n"
                                "| #09      . . . . . |       |      |\n"
                                "| #08      . . . . . |       |      |\n"
                                "| #07      . . . . . |       |      |\n"
                                "| #06      . . . . . |       |      |\n"
                                "| #05      . . . . . |       |      |\n"
                                "| #04      . . . . . |       |      |\n"
                                "| #03      . . . . . |       |      |\n"
                                "| #02      . . . . . |       |      |\n"
                                "| #01      . . . . . |       |      |\n"
                                "-------------------------------------\n";
           }




           if (!board.attempts_and_feedbacks.empty())       //printing if player has already played
           {
           int sz = (int)board.attempts_and_feedbacks.size();
           
            // start of head printing
           int anssize = game_options.number_of_characters_per_code;
           std::string espaces = "";
           std::string moins = "---------------------------";
           std::string etoiles = "";
           std::string points = "";
           for (unsigned int i = 0U; i < game_options.number_of_characters_per_code; i++)
           {
               points = points + ". ";
           }
           for (int j = 0; j < anssize; j++)
           {
               etoiles = etoiles + "* ";
               espaces = espaces + "  ";
               moins = moins + "--";
           }
           moins = moins + "\n";

           output_stream << moins << "| SECRET  " << etoiles << "|              |\n"
                         << moins << "| ATTEMPTS" << espaces << "| BULLS | COWS |\n"
                         << moins;
           // end of head printing

               for (unsigned int i = 0U; i < game_options.max_number_of_attempts; i++) // for all attempts
               {
                   // board.attempts_and_feedbacks[sz - i];
                   if (i < game_options.max_number_of_attempts - sz) // writting the empty attempts
                   {

                       if (game_options.max_number_of_attempts - i < 10)
                       {
                           output_stream << "| #" << '0' << game_options.max_number_of_attempts - i << '   ' << '   '
                                         << points << "|"
                                         << "   "
                                         << " "
                                         << "   "
                                         << "|"
                                         << "  " << board.attempts_and_feedbacks[i].feedback.cows << "   |\n";
                       }
                       // two different cases to put the 0 digit in case of need
                       else
                       {
                           output_stream << "| #" << game_options.max_number_of_attempts - i << '   ' << '   ' << points
                                         << "|"
                                         << "   "
                                         << " "
                                         << "   "
                                         << "|"
                                         << "  "
                                         << " "
                                         << "   |\n";
                       }
                   }

                   else

                   { // writting played attempts
                       std::string codeout;
                       for (unsigned int k = 0U; k < game_options.number_of_characters_per_code; k++)
                       {
                           codeout = codeout + board.attempts_and_feedbacks[i].attempt.value + " ";
                       }
                       if (game_options.max_number_of_attempts - i < 10)
                       {
                           output_stream << "| #" << '0' << game_options.max_number_of_attempts - i << '   ' << '   '
                                         << codeout + "|"
                                         << "   " << board.attempts_and_feedbacks[i].feedback.bulls << "   "
                                         << "|"
                                         << "  " << board.attempts_and_feedbacks[i].feedback.cows << "   |\n";
                       }

                       else
                       {
                           output_stream << "| #" << game_options.max_number_of_attempts - i << '   ' << '   '
                                         << codeout + "|"
                                         << "   " << board.attempts_and_feedbacks[i].feedback.bulls << "   "
                                         << "|"
                                         << "  " << board.attempts_and_feedbacks[i].feedback.cows << "   |\n";
                       }
                   }
               }

               output_stream << moins;
           }
           

       }

       */
       
       
       //Checked
       
       void whats_your_guess(std::ostream& output_stream, const GameOptions& game_options, std::string s,
                             int current_attempt, unsigned int number_of_characters_per_code,
                             char minimum_allowed_character, char maximum_allowed_character)
       {
           output_stream << "What is your guess #" << s << current_attempt << " (" << number_of_characters_per_code
                         << " characters between '" << minimum_allowed_character << "' and '"
                         << maximum_allowed_character << "')\n? ";
       }

       Code ask_attempt(std::ostream& output_stream, std::istream& input_stream, const GameOptions& game_options,
                        const Board& board)
       {
           // Max number of attemps and max number of character ...
           Code incode;
           int current_attempt = (int)board.attempts_and_feedbacks.size() + 1;

           bool valueformat = false;
           while (!valueformat)
           {
               if (current_attempt < 10)
               {
                   whats_your_guess(output_stream, game_options, "0", current_attempt,
                                    game_options.number_of_characters_per_code, game_options.minimum_allowed_character,
                                    game_options.maximum_allowed_character);
               }
               else
               {
                   whats_your_guess(output_stream, game_options, "", current_attempt,
                                    game_options.number_of_characters_per_code, game_options.minimum_allowed_character,
                                    game_options.maximum_allowed_character);
               }

               valueformat = true;

               input_stream >> incode.value;
               if (incode.value.size() != game_options.number_of_characters_per_code)
               {
                   valueformat = false;
                   output_stream
                       << "Your guess has an invalid length or contains non-allowed characters, please try again\n";
               }

               else
               {
                   for (char& c : incode.value)
                   {
                       if ((c < game_options.minimum_allowed_character) | (c > game_options.maximum_allowed_character))
                       {
                           valueformat = false;

                           output_stream << "Your guess has an invalid length or contains non-allowed characters, "
                                            "please try again\n";
                       }
                   }
               }
           }
           return incode;
       }



} // namespace bulls_and_cows
