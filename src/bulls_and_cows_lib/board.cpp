
#include "board.hpp"
#include "random.hpp"
#include <iostream>
#include <vector>
//#include <boost/algorithm/string.hpp>
namespace bulls_and_cows {





    bool unichar(std::string str) // checks if the string contains unique characters
    {
        for (int i = 0; i < str.length() - 1; i++)
        {
            for (int j = i + 1; j < str.length(); j++)
            {
                if (str[i] == str[j])
                {
                    return false;
                }
            }
        }
        return true;
    }


    Code generate_code(const GameOptions& game_options)
    {
        Code mycode;
        for (unsigned int i = 0U; i < game_options.number_of_characters_per_code; i++) // generation of the code
        {
            mycode.value.push_back(generate_random_character(
                game_options.minimum_allowed_character, game_options.maximum_allowed_character));
        }
        return mycode;
    }

    Board create_board(const GameOptions& game_options)
    {
        Board ans;

        ans.secret_code = generate_code(game_options);

        if (game_options.unique_characters) // if unicity of characters in code required
        {
            bool out = false;
            while (!unichar(ans.secret_code.value))    // while code does not meet the requirement, generate a new one
            {

                if (unichar(ans.secret_code.value))
                {
                    out = true;
                }
                else
                {
                    ans.secret_code = generate_code(game_options);
                }
            }

        }
        return ans;
    }


   


        //Checked
       bool validate_attempt(const GameOptions& game_options, const Code& attempt) // check if the user input attempt is correct
       {
           if (game_options.number_of_characters_per_code == attempt.value.size()) // Size checj
           {
               for (const char& c : attempt.value)
               {
                   if ((c < game_options.minimum_allowed_character) | (c > game_options.maximum_allowed_character)) // Char value check
                   {
                       return false;
                   }

                   if (game_options.unique_characters) // Unicity check
                   {
                       if (!unichar(attempt.value))
                       {
                           return false;
                       }
                   }
               }
               return true;
           }
           else
           {
               return false;
           }
               
       }



       Feedback compare_attempt_with_secret_code(const Code& attempt, const Code& secret_code)
       {
           Feedback myfeed{};
           std::string tmp_secret_code = secret_code.value;
           std::string tmp_attempt = attempt.value;
           std::size_t found;
           // bulls managing first, the easiest one
           for (int i = 0; i < tmp_secret_code.size(); i++) 
           {
               if (tmp_secret_code[i] == tmp_attempt[i])
               {
                   tmp_attempt.erase(i, 1); // erase char in order not to exmaine it twice
                   tmp_secret_code.erase(i, 1);
                   myfeed.bulls++;
                   i--; // tricky bug I had
               }
           }

           // cows managing once bulls are out
           for (int j = 0; j < tmp_attempt.size(); j++)
           {
               found = tmp_secret_code.find(tmp_attempt[j]);
               if (found != std::string::npos)
               {
                   tmp_secret_code.erase(tmp_secret_code.find(tmp_attempt[j]), 1);
                   myfeed.cows++;
               }
           }

           return myfeed;
       }
       bool is_end_of_game(const GameOptions& game_options, const Board& board) // Check of the loss, when all attempts are filled
       {
           if (game_options.max_number_of_attempts == board.attempts_and_feedbacks.size())
           {
               return true;
           }
           return false;
       }
       
       
       bool is_win(const GameOptions& game_options, const Board& board) // Check of the win
       {
           if ((board.attempts_and_feedbacks.empty())) 
               return false;
           if (board.attempts_and_feedbacks.back().attempt.value == board.secret_code.value)
           {
               return true;
           }

           return false;
       }


       std::string moins_function(int number, std::string loopadd) // puts the right number of character loopadd in order to make a responsive output in console
       {
           std::string moins = "";
           for (int i = 0; i < number; i++)
           {
               for (int j = 0; j < loopadd.size(); j++)
               moins.push_back(loopadd[j]);
           }
           return moins;
       }

       void print_code(std::string code)    // indeed
       {
           char* ccode = const_cast<char*>(code.c_str());
           std::string codewspace = "";
           for (int i = 0; i < code.length(); i++)
           {
               std::cout << ccode[i] << " ";
           }
       }

       // unsuccessfull attempts to optimize the display

       /*void affichagebg(std::ostream& output_stream, size_t compteur, std::string tentative, unsigned int bulls, unsigned int cows)
       {
           std::cout << "| #" << ((compteur >= 10) ? "" : "0") << compteur << "      ";
           print_code(tentative);
           //std::cout << ((bulls == NULL) ? "|       |       |\n" : "   " << bulls << "   |   " << cows << "   |\n");
           std::cout << "|   " << ((bulls == NULL) ? " " : "") << bulls << "   |   "
                     << ((cows == NULL) ? " " : "") << cows << "   |\n";
           output_stream << "| #" << ((compteur >= 10) ? "" : "0") << compteur << "      " << ;
       }*/



       /*void optiif(std::ostream& output_stream, const GameOptions& game_options, bool dotoratt, size_t number,
                   AttemptAndFeedback att)
       {
           std::string space = moins_function(7, " ");
           std::string starting_space = moins_function(6, " ");
           std::string zero = (number >= 10) ? "" : "0";

           if (dotoratt)
               output_stream << "| #" << zero << number << starting_space
                             << moins_function(game_options.number_of_characters_per_code, ". ") << "|" << space << "|"
                             << space << "|\n";
           else
           {
               const auto& attempt = att.attempt;
               const auto& feedback = att.feedback;
               output_stream << "| #" << zero << number << starting_space;
               print_code(attempt.value);
               output_stream << "|   " << feedback.bulls << "   |   " << feedback.cows << "   |\n";
           }
       }*/



       void display_board(std::ostream& output_stream, const GameOptions& game_options, const Board& board)
       {
           // HEAD ...
           // Showing answer to debug
           //output_stream << "Secret code (for debugging and cheating) = " << board.secret_code.value << "\n";
           output_stream << "-----------" << moins_function(game_options.number_of_characters_per_code, "--") << "--"
                         << "---------------\n";
           output_stream << "| SECRET   " << moins_function(game_options.number_of_characters_per_code, "* ") << "| "
                         << "              |\n";
           output_stream << "-----------" << moins_function(game_options.number_of_characters_per_code, "--") << "--"
                         << "---------------\n";
           output_stream << "| ATTEMPTS " << moins_function(game_options.number_of_characters_per_code, "  ") << "| "
                         << "BULLS | COWS  |\n";
           output_stream << "-----------" << moins_function(game_options.number_of_characters_per_code, "--") << "--"
                         << "---------------\n";
           //...

           // BODY ...
           int number_of_attemps = game_options.max_number_of_attempts;
           for (size_t i = number_of_attemps; i > board.attempts_and_feedbacks.size(); i--) // display of empty attempts
           {
               output_stream << "| #" << ((i >= 10) ? "" : "0") << i << "      " // ternary to add a 0 before the digit if needed
                             << moins_function(game_options.number_of_characters_per_code, ". ")
                             << "|       |       |\n";
               //affichagebg(std::cout, i, moins_function(game_options.number_of_characters_per_code, "."), NULL, NULL);
               //here the affichagebg method works but it puts 0 in unfilled attempts, i am not satisfied with it so i don't use it
           }

           if (!board.attempts_and_feedbacks.empty())
           {
               for (size_t index = board.attempts_and_feedbacks.size(); index > 0; --index) // display of filled attempts
               {
                   const auto& attempt_and_feedback = board.attempts_and_feedbacks[index - 1];
                   const auto& attempt = attempt_and_feedback.attempt;
                   const auto& feedback = attempt_and_feedback.feedback;
                   
                   /*affichagebg(index, attempt.value, feedback.bulls,
                               feedback.cows);*/
                   output_stream << "| #" << ((index >= 10) ? "" : "0") << index << "      ";
                   print_code(attempt.value);
                   output_stream << "|   " << feedback.bulls << "   |   " << feedback.cows << "   |\n";
               }
           }
           //...

           // FOOTER ...
           output_stream << "-----------" << moins_function(game_options.number_of_characters_per_code, "--") << "-"
                         << "----------------\n";
           //...
       }
   
       
       
       void whats_your_guess(std::ostream& output_stream, const GameOptions& game_options, std::string s,
                             int current_attempt, unsigned int number_of_characters_per_code,
                             char minimum_allowed_character, char maximum_allowed_character) // prints the question written properly
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

           bool valueformat = false; // flag used to handle the validity of user attempt
           while (!valueformat)
           {
               //if (current_attempt < 10) // could be replaced with ternary but it's really hard to read
               //{
               //    whats_your_guess(output_stream, game_options, "0", current_attempt,
               //                     game_options.number_of_characters_per_code, game_options.minimum_allowed_character,
               //                     game_options.maximum_allowed_character);
               //}
               //else
               //{
               //    whats_your_guess(output_stream, game_options, "", current_attempt,
               //                     game_options.number_of_characters_per_code, game_options.minimum_allowed_character,
               //                     game_options.maximum_allowed_character);
               //}

               ((current_attempt < 10)
                    ? whats_your_guess(output_stream, game_options, "0", current_attempt,
                                       game_options.number_of_characters_per_code,
                                       game_options.minimum_allowed_character, game_options.maximum_allowed_character)
                    : whats_your_guess(output_stream, game_options, "", current_attempt,
                                       game_options.number_of_characters_per_code,
                                       game_options.minimum_allowed_character, game_options.maximum_allowed_character));

               valueformat = true;

               input_stream >> incode.value; // take the user input
               if (incode.value.size() != game_options.number_of_characters_per_code) // Size check
               {
                   valueformat = false;
                   output_stream
                       << "Your guess has an invalid length, please enter a "<< game_options.number_of_characters_per_code <<" characters code\n";
               }

               else
               {
                   for (char& c : incode.value)
                   {
                       if ((c < game_options.minimum_allowed_character) | (c > game_options.maximum_allowed_character)) // Character check
                       {
                           valueformat = false;

                           output_stream << "Your guess contains non-allowed characters, "
                                            "please try again\n";

                           
                       }
                       if (game_options.unique_characters) // Unicity check
                       {
                           if (!unichar(incode.value))
                           {
                               valueformat = false;
                               output_stream << "Please enter a code with unique characters\n";
                               break;
                           }
                       }
                   }
               }
           }
           return incode;
       }



} // namespace bulls_and_cows
