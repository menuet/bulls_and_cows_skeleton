

#include "board.hpp"
#include "random.hpp"
#include <string>
using namespace std; // lifehack

namespace bulls_and_cows {

    Board create_board(const GameOptions& game_options)
    {
        Board b; // creer une structure board vide
        for (size_t i = 0; i < game_options.number_of_characters_per_code;
             i++) // boucle for qui remplit le code secret d'une taille game_options.number_of_characters_per_code
        {
            b.secret_code.value += generate_random_character(
                game_options.minimum_allowed_character,
                game_options
                    .maximum_allowed_character); // lettre entre la lettre min et max de l'option passé en parametre
        }

        // TODO: peut etre initialiser l array de feedback
        return b;
    }

    bool validate_attempt(const GameOptions& game_options, const Code& attempt)
    {
        string codex = attempt.value;
        if (codex.length() != game_options.number_of_characters_per_code) // verification de la taille du code
        {
            return false;
        }

        for (int i = 0; i < codex.size(); i++) //  on parcourt de chaque caracter du codex
        {
            if (codex[i] < game_options.minimum_allowed_character ||
                codex[i] > game_options.maximum_allowed_character) // si une des lettres est en dehors des bornes fixés
                                                                   // (genre 'A' et 'H')
            {
                return false;
            }
        }

        return true;
    }

    Feedback compare_attempt_with_secret_code(const Code& attempt, const Code& secret_code)
    {
        string REALCODE = secret_code.value;
        string codex = attempt.value;
        Feedback f;
        int cows = 0;
        int bulls = 0;

        //on crééer un tableau de boolean
        vector<bool> bullvector;
        for (int i = 0; i < codex.size(); i++)
        {
            bullvector.push_back(false);
        }

        // on compte les bulls
        for (int i = 0; i < codex.size(); i++) // on parcourt de chaque caracter du codex
        {
            if (codex[i] == REALCODE[i]) // si on a trouvé le caractere dans le code
            {
                bulls++;
                bullvector[i] = true;
            }
        }

        // on compte les cows
        // !!!!!! on part du principe que si dans l'attempt on met 2 fois un char présent 1 fois dans le secret_code,
        // alors on a 2 cows. <- FAUX
        for (int i = 0; i < codex.size(); i++) // on parcourt de chaque caracter du codex
        {
            if (REALCODE.find(codex[i]) != string::npos && codex[i] != REALCODE[i] && !bullvector[REALCODE.find(codex[i])]) // si on a trouvé le caractere dans le code et ce n'est pas un bulls alors ok
            {
                cows++;
            }
        }



        f.cows = cows;
        f.bulls = bulls;

        return f;
    }

    bool is_end_of_game(const GameOptions& game_options, const Board& board)
    {
        // attempt pareil que secretcode
        for (int i = 0; i < size(board.attempts_and_feedbacks);
             i++) // on parcourt la liste des attemptes et on regarde si il y en a un similaire au code secret
        {
            if (board.attempts_and_feedbacks[i].attempt.value == board.secret_code.value)
            {
                return true;
            }
        }

        // derniere tentative
        if (size(board.attempts_and_feedbacks) >= game_options.max_number_of_attempts)
        {
            return true;
        }

        return false;
    }

    bool is_win(const GameOptions& game_options, const Board& board)
    {
        if (board.attempts_and_feedbacks.size() == 0) // on vérifie qu'il y a déjà eu au moins une tentative
        {
            return false;
        }
        if (board.attempts_and_feedbacks[board.attempts_and_feedbacks.size()-1].attempt.value == board.secret_code.value) // on regarde la derniere valeur du tableauc
        {
            return true;
        }
        return false;
    }

    void display_board(std::ostream& output_stream, const GameOptions& game_options, const Board& board)
    {

            string showup =
                "-------------------------------------\n"
                "| SECRET   * * * * * |              |\n"
                "-------------------------------------\n"
                "| ATTEMPTS           | BULLS | COWS |\n"
                "-------------------------------------\n";

            // Attention!! Il faut prendre en compte les lignes pas encore remplis
            for (int i = game_options.max_number_of_attempts; i > ((int)board.attempts_and_feedbacks.size())-1; i--)
            {
                if (i>8)
                {
                    showup += "| #" + to_string(i + 1) + "      . . . . . |       |      |\n";
                }
                else
                {
                    showup += "| #0" + to_string(i + 1) + "      . . . . . |       |      |\n";
                }
               
            }
           
            for (int i = (int)board.attempts_and_feedbacks.size()-1; i >= 0; i--) //size_t est tjr positif (impossible de faire i-- quand i=0) donc on trick
            {
                string numero;
                if ((i+1)>9)
                {
                    numero = "| #" + to_string(i + 1);
                }
                else
                {
                    numero = "| #0" + to_string(i + 1);
                }
                showup += numero + "          "+ board.attempts_and_feedbacks[i].attempt.value + " |   " +
                          to_string(board.attempts_and_feedbacks[i].feedback.bulls) + "   |   " +
                          to_string(board.attempts_and_feedbacks[i].feedback.cows) + "  |\n";
            }
            showup += "-------------------------------------\n";
            output_stream << showup; // output_stream a la place de cout pour afficher du text?
        //}
        
    }

    Code ask_attempt(std::ostream& output_stream, std::istream& input_stream, const GameOptions& game_options, const Board& board)
    {
        output_stream << "Rentrez votre tentative!" << endl;
        Code codex;
        input_stream >> codex.value;
        
        while (!validate_attempt(game_options, codex)) //on vérifie la qualitée de l'attempt ici
        {
            output_stream << "Rerentrez votre tentative, bien cette fois stp!" << endl;
            input_stream >> codex.value;
        }

        return codex;
    }

} // namespace bulls_and_cows
