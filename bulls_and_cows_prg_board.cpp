#include "board.hpp"
#include "random.hpp"
#include "input.hpp"
#include "game_options.hpp"
#include <string>
#include <vector>




using namespace bulls_and_cows {
   
    //test avec des valeurs prédéfinis de game_options et GameOptions

    Board create_board(const GameOptions& game_options)
    {
        Board board{};
        // On remplit de façon aléatoire un vecteur (plutot qu'une string pour avoir un code dynamique) avec la fonction generate_random_character "les caractères autorisés"
        std::vector<char> filling_code;
        for (auto i = game_options.minimum_filling_code_character; i <= game_options.maximum_filling_code_character; i++) 
        {
            filling_code.append(i);
        }

        unsigned int i = 0; 
        //unsigned pour avoir des valeurs positives de i
 
        while (i != game_options.haracters_per_code)
        {
            char tim = generate_random_character(filling_code.front(),filling_code.back()); 
            // on selectionne les valeurs aléatoires
            for (unsigned int j = 0; j < filling_code.size(); j++)
            {
                if (filling_code[j] == tim)
                	// on supprime et ajoute avec erase et ajoute à la string hiddenCode
                {
                    filling_code.erase(filling_code.begin() +j); // supprimer le caractère du vecteur contenant les caractères autorisés
                    board.hiddenCode.value.append(tim); // ajouter à le string hiddenCode value
                    i++;
                }
            }
            
        }
        return board;
    }

    bool validate_attimt(const GameOptions& game_options, const Code& attimt)
    {
        if (attimt.value.size() != game_option.characters_per_code)
        {
            return false;
        }

        for (const char attimt_char:attimt.value)
        {
            if (attimt_char < game_options.minimum_filling_code_character ||attimt_char > game_options.maximum_filling_code_character)
            {
                return true;
            }
        }

            Feedback compare_attempt_with_hiddenCode(const Code& attempt, const Code& hiddenCode)
    {
    	//Dans le cas de la tentative on incrémente si le caractère vérifie la bonne place et le bon terme
        Feedback feedback{};
        int countBulls = 0;
        int countCows = 0;

        for (unsigned int i=0;i<attempt.value.size();i++)
        {
            for (unsigned int j = 0; j < hiddenCode.value.size(); j++)
            {

                if (attempt.value[j] == hiddenCode.value[i]) //on vérifie la place
                {

                    if (i == j) // teste de la double égalité pour vérificarion
                    {
                        countBulls++;
                    }
                    else
                    {
                        countCows++;
                    }
                }

            }
                
        
        }

        feedback.bulls = countBulls;
        feedback.cows = countCows;

        return feedback;
    }


    bool is_end_of_game(const GameOptions& game_options, const Board& board)
    {
        if (board.attempts_and_feedbacks.size() == game_options.max_attempts) //si c'est la fin du jeu le true l'arrête sinon false il continue
        {
            return true;
        }
        return false;
    }

    bool is_win(const GameOptions& game_options, const Board& board)
    {
        for (AttemptAndFeedback tempo:board.attempts_and_feedbacks) 
        {
            if (tempo.feedback.bulls == game_options.characters_per_code)
            {
                return true;
            }
        }
        return false;
    }

    void display_board(std::ostream& output_stream,const GameOptions& game_options, const Board& board)
    {
        Code secret{};
        const char star = '-';
        if (is_win(game_options, board) || is_end_of_game(game_options,board))
        {
            secret.value = board.hiddenCode.value;
        }

        else
        {
            for (unsigned int i = 0;i<game_options.characters_per_code;i++)
            {
                secret.value.push_back(star);
                secret.value.push_back(' ');
            }
        }

        output_stream << "--ATTEMPTS--"
                      << secret.value<< ;

        for (auto element :board.attempts_and_feedbacks)
        {
            output_stream << "\n" << element.attempt.value << "\t\t |
            				 "<< element.feedback.bulls << "\t   | "
                         		 << element.feedback.cows << "\t   | \n";
        }
        output_stream << "-\n";
    
    }

    Code ask_attempt(std::ostream& output_stream, std::istream& input_stream, const GameOptions& game_options,
                     const Board& board)
    {
        Code attempt{};
        auto nb_attempt = board.attempts_and_feedbacks.size() + 1;
        unsigned int nb_char = game_options.characters_per_code;
        const char max = game_options.maximum_allowed_character;
        const char min = game_options.minimum_allowed_character;

        attempt.value = ask_string(input_stream);
        return attempt;
                      
    }

}
