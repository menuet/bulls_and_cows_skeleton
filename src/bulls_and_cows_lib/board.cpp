#include "board.hpp"
#include "random.hpp"

namespace bulls_and_cows {

    // TODO: define the body of the functions declared in board.cpp

    // Create a board and with a new random secret code composed of allowed characters
    Board create_board(const GameOptions& game_options){
        Board board;

        // on va declarer une classe string sc pour la concatenation de tout ce que la fonction generate_random_character renvoie.
        std::string sc = "";
        for (unsigned int i = 0; i < game_options.number_of_characters_per_code; i++) {

             // concatenation.
             sc = sc + generate_random_character(game_options.minimum_allowed_character, game_options.maximum_allowed_character);
        }

        // attribution du resultat de la concatenation au membre secret_code.
        board.secret_code.value= sc;

        return board;

        
    }



    // Validate that a user-entered code contains proper number of allowed characters
    bool validate_attempt(const GameOptions& game_options, const Code& attempt){
        bool att= false;
        // comparaison du nombre de caracteres de l essai et celui du secret_code

        if (attempt.value.length() == game_options.number_of_characters_per_code ){
            att = true;
            std::cout << "proper number of allowed character" << std::endl;
        }
        else{
            att= false;
            std::cout << " no proper number of allowed character" << std::endl;
        
        }
        return att;
        //-----------------------------------------------------------------------------------------
        

        // on verifie que les caracteres du attempt soient compris entre les min et max allowed character
        //  pour chaque valeur i de attempt on compare avec les min et max allowed character
        bool att2= true;

        unsigned int i = 0;
        while (att2 ==true &&  i < game_options.number_of_characters_per_code){
             att2= (attempt.value[i] > game_options.minimum_allowed_character && attempt.value[i]< game_options.maximum_allowed_character );
             i++; 
            
         }
        return att2;
        
    }



    // Compare a user-entered code with the secret code and give the corresponding number of bulls and cows
    Feedback compare_attempt_with_secret_code(const Code& attempt, const Code& secret_code) {
        
        Feedback f;
        // range for : pour parcourir tous les characteres aue l utilisateur a entre 
        for (int i: attempt.value) {
            // range for : pour parcourir tous les characteres du code secret
            for (int j: secret_code.value) {
                // 1) on verifie que le charactere est present dans la le code  2) et qu'il est bien place
                if (attempt.value[i] == secret_code.value[j] && i ==j ) {
                     f.bulls++;
                }
                else {
                    // 1) on verifie que le charactere est present dans le code  2) mais qu'il est mal place
                    if (attempt.value[i] == secret_code.value[j] && i !=j ) {
                        f.cows++;
                    }
                }
            }
            return f;
        }
    }

    // Test if this is the end of the game
    bool is_end_of_game(const GameOptions& game_options, const Board& board) {
        
        bool end = false;

        // comparaison du nombre d essai effectue par l utilisateur et le nombre max de test
        if (board.attempts_and_feedbacks.size() == game_options.max_number_of_attempts){
            end = true;
            std::cout << "it is the end of the game" << std::endl;
        }

        else{
            end = false;
            std::cout << "you have an other chance " << std::endl;
        }
        return end;
    }

    // Test if the last attempt is a win
    bool is_win(const GameOptions& game_options, const Board& board) {
        
        bool win = false;
        
        if (board.attempts_and_feedbacks.empty()) {
            win = false;
        }

        if (board.attempts_and_feedbacks.back().attempt.value == board.secret_code.value) {
            win = true;
        }
        return win;
    }


    // Ask the user to provide another attempt
    Code ask_attempt(std::ostream& output_stream, std::istream& input_stream, const GameOptions& game_options, const Board& board) {
         
         Code attempt;

         output_stream << "What's your choice #01 (" << game_options.number_of_characters_per_code
                       << " characters allowed between '" << game_options.minimum_allowed_character << "' & '"
                       << game_options.maximum_allowed_character << "') ?" << std::endl;
         input_stream >> attempt.value;

         while (!validate_attempt(game_options, attempt))
         {
             output_stream << "no allowed characters or no valid length, enter an other choice\n"
                           << "What's your choice #01 (" << game_options.number_of_characters_per_code
                           << " characters allowed between '" << game_options.minimum_allowed_character << "' & '"
                           << game_options.maximum_allowed_character << "') ?" << std::endl;
             input_stream >> attempt.value;
         }

         return attempt;
    }

                     
    // Display the scret code and the list of attempts of the board
    void display_board(std::ostream& output_stream, const GameOptions& game_options, const Board& board){
        if (is_win(game_options, board) || is_end_of_game(game_options, board))
         {
             output_stream << "\n--------------------------------\n"
                           << "| secret   ";
             for (auto sc : board.secret_code.value)
             {
                 output_stream << sc;
                 output_stream << " ";
             }
         }
         else
         {

             output_stream << "--------------------------------\n"
                           << "| secret   ";
             for (unsigned i = 0; i < game_options.number_of_characters_per_code; i++)
             {
                 output_stream << "* ";
             }
         }
         output_stream << "|              |\n--------------------------------\n"
                       << "| attempts ";

         for (unsigned j = 0; j < game_options.number_of_characters_per_code; j++)
         {
             output_stream << "  ";
         }
         output_stream << "| bulls | cows |\n "
                       << "--------------------------------\n";

         for (unsigned k = game_options.max_number_of_attempts; k > 0; k--)
         {
             std::string point{};
             for (unsigned l = 0; l < game_options.number_of_characters_per_code; l++)
             {
                 point += ". ";
             }
             if (board.attempts_and_feedbacks.size() < k)
             {
                 if (k < 10)
                     output_stream << "| #0";
                 else
                     output_stream << "| #";
                 output_stream << k << "      " << point << "|       |      |\n";
             }
             else
             {
                 if (k < 10)
                     output_stream << "| #0";
                 else
                     output_stream << "| #";
                 output_stream << k << "      ";
                 for (auto byone : board.attempts_and_feedbacks.at(k - 1).attempt.value)
                 {
                     output_stream << byone;
                     output_stream << " ";
                 }
                 output_stream << "|   " << board.attempts_and_feedbacks.at(k - 1).feedback.bulls << "   |  "
                               << board.attempts_and_feedbacks.at(k - 1).feedback.cows << "   |\n";
             }
         }
         output_stream << "--------------------------------\n";
    }

} // namespace bulls_and_cows
