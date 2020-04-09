
#include "board.hpp"

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

    std::string gencode(GameOptions game_options)
    {
        std::string myreturn;
        for (unsigned int i = 0U; i < game_options.number_of_characters_per_code; i++)
        {
            // Génération du code secret en character
            myreturn = myreturn + generate_random_character(game_options.minimum_allowed_character, game_options.maximum_allowed_character);
        }
        return myreturn;
    }
    // TODO: define the body of the functions declared in board.cpp
    Board create_board(const GameOptions& game_options)
    {
        Board myboard{};
        myboard.secret_code.value = gencode(game_options);

        if (game_options.unicate)
        {
            while (!unichar(myboard.secret_code.value))
            {
            myboard.secret_code.value = gencode(game_options);
            }
        }
        //std::cout << "Le code secret est le suivant :" << myboard.secret_code.value;
        return myboard;
    }


    bool validate_attempt(const GameOptions& game_options, const Code& attempt)
    {
        //Valide si le nombre de char est le bon et qu'ils sont compris entre le min et max ...
        if (game_options.number_of_characters_per_code == attempt.value.size())
        {
            for (const char& c : attempt.value)
            {
                if ((c < game_options.minimum_allowed_character) | (c > game_options.maximum_allowed_character))
                    return false;
            }
            return true;
        }
        else
            return false;
    }

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
            }
        }

        return myfeed;
    }

    // Retourne true si le joueur a atteint le max number of attempts
    bool is_end_of_game(const GameOptions& game_options, const Board& board)
    {
        if (game_options.max_number_of_attempts == board.attempts_and_feedbacks.size())
        {
            std::cout << "You loose, too bad, try again you'll do maybe better ...";
            return true;
        }
        else return false;
    }

    bool is_win(const GameOptions& game_options, const Board& board)
    {

        if ((board.attempts_and_feedbacks.empty()))
            return false;

        else if (board.attempts_and_feedbacks.back().attempt.value == board.secret_code.value)
        {
            if (board.attempts_and_feedbacks.size() < (game_options.max_number_of_attempts / 2))
                std::cout << "You won on your " << board.attempts_and_feedbacks.size() << " attemp,  Well done !!!";
            else if (board.attempts_and_feedbacks.size() > (game_options.max_number_of_attempts / 2))
                std::cout << "You won on your " << board.attempts_and_feedbacks.size() << " attemp, That was close !!!";
            return true;
        }

        else return false;
    }


    Code ask_attempt(std::ostream& output_stream, std::istream& input_stream, const GameOptions& game_options,
                         const Board& board)
        {
            Code incode;
            auto current_attempt = board.attempts_and_feedbacks.size() + 1;

            bool valueformat = false;
            while (!valueformat)
            {
                output_stream << "What is your guess #" << current_attempt << " ("
                              << game_options.number_of_characters_per_code << " characters between '"
                              << game_options.minimum_allowed_character << "' and '"
                              << game_options.maximum_allowed_character << "')\n? ";

                valueformat = true;

                input_stream >> incode.value;
                if (incode.value.size() != game_options.number_of_characters_per_code)
                {
                    valueformat = false;
                    output_stream
                        << "Your guess has an invalid length or contains non-allowed characters, please try again\n";
                    break;
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
                            break;
                        }
                    }
                }
            }
            return incode;
        }

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

        //Fonction visant à optimiser l'affichage du jeu
        void optiif(std::ostream& output_stream, const GameOptions& game_options, bool dotoratt, size_t number, AttemptAndFeedback att)
        {
            std::string space = moins_function(7, " ");
            std::string starting_space = moins_function(6, " ");
            std::string zero = (number >= 10) ? "" : "0";

            if (dotoratt)
                output_stream << "| #" << zero << number << starting_space 
                << moins_function(game_options.number_of_characters_per_code, ". ") 
                << "|" << space << "|"<< space << "|\n";
            else
            {
                const auto& attempt = att.attempt;
                const auto& feedback = att.feedback;
                output_stream << "| #" << zero << number << starting_space;
                print_code(attempt.value);
                output_stream << "|   " << feedback.bulls << "   |   " << feedback.cows << "   |\n";
            }
        }

    void display_board(std::ostream& output_stream, const GameOptions& game_options, const Board& board)
        {
            // HEAD ... Ne change jamais
            output_stream << "-----------" << moins_function(game_options.number_of_characters_per_code, "--") << "--"<< "---------------\n";
            output_stream << "| SECRET   " << moins_function(game_options.number_of_characters_per_code, "* ") << "| "<< "              |\n";
            output_stream << "-----------" << moins_function(game_options.number_of_characters_per_code, "--") << "--"<< "---------------\n";
            output_stream << "| ATTEMPTS " << moins_function(game_options.number_of_characters_per_code, "  ") << "| "<< " BULLS | COWS |\n";
            output_stream << "-----------" << moins_function(game_options.number_of_characters_per_code, "--") << "--"<< "---------------\n";
            //...

            // BODY ... 
            AttemptAndFeedback atte{};
            int number_of_attemps = game_options.max_number_of_attempts;
            for (unsigned int i = number_of_attemps; i > board.attempts_and_feedbacks.size(); i--)
            {
               optiif(output_stream, game_options, true, i, atte);
            }

            if (!board.attempts_and_feedbacks.empty())
            {
                for (size_t index = board.attempts_and_feedbacks.size(); index > 0; --index)
                {
                    const auto& attempt_and_feedback = board.attempts_and_feedbacks[index - 1];
                    optiif(output_stream, game_options, false, index, attempt_and_feedback);
                }
            }
            //...

            // FOOTER ...
            output_stream << "-----------" << moins_function(game_options.number_of_characters_per_code, "--") << "-"
                          << "----------------\n";
            //...
     }
    
} // namespace bulls_and_cows
