#include "board.hpp"
#include "random.hpp"
#include "input.hpp"
#include <algorithm>
#include <vector>


namespace bulls_and_cows {

    Board create_board(const GameOptions& game_options)
    {
        Board myboard{};

        for (unsigned int j = 0; j < game_options.number_of_characters_per_code; j++) // pour j allant de 0 � number_of_characters_per_code(5) 
        {
            char temp = generate_random_character(game_options.minimum_allowed_character,
                game_options.maximum_allowed_character); // g�n�re un caract�re entre le minimum/maximum_allowed_character ici d�fini de A � Z
            myboard.secret_code.value.push_back(temp); //retourne le caract�re
        }

        //std::cout << myboard.secret_code.value; //acc�der � la valeur du code secret dans myboard
        return myboard;
    }

    bool validate_attempt(const GameOptions& game_options, const Code& attempt)
    {
        if (attempt.value.size() != game_options.number_of_characters_per_code) // si la taille de ta tentative est diff�rente que number_of_characters_per_code retourne faux
        {
            return false;
        }

        for (const char attempt_char : attempt.value)
        {
            if (attempt_char < game_options.minimum_allowed_character ||
                attempt_char > game_options.maximum_allowed_character) // v�rifie que les caract�res sont bien compris entre le minimum et le maximum 
            {
                return false;
            }
        }


        return true;
    }

    Feedback compare_attempt_with_secret_code(const Code& attempt, const Code& secret_code)
    {
        Feedback myfeedback{};
        int cpt_bulls = 0;
        int cpt_cows = 0;
        std::size_t presence;
        std::string secret_code_bis = secret_code.value;
        std::string attempt_bis = attempt.value;


        for (unsigned int i = 0; i < attempt.value.size(); i++)
        {


            if (attempt.value[i] == secret_code.value[i])
            {
                cpt_bulls++;
                
            }
        }

        for (int j = 0; j < attempt.value.size(); j++)
        {
            presence = secret_code_bis.find(attempt_bis[j]);
            if (presence != std::string::npos)
            {
                secret_code_bis.erase(secret_code_bis.find(attempt_bis[j]), 1);
                cpt_cows++;
            }
        }


        myfeedback.bulls = cpt_bulls;
        myfeedback.cows = cpt_cows - cpt_bulls; // contraint de faire cette soustraction sinon les bulls sont compt�s comme des cows.

        return myfeedback;
    }


    bool is_end_of_game(const GameOptions& game_options, const Board& board)
    {
        if (board.attempts_and_feedbacks.size() == game_options.max_number_of_attempts) // si la taille du vecteur vaut le max_number_of_attempts (12) alors fin de partie
        {
            return true;
        }
        return false;
    }

    bool is_win(const GameOptions& game_options, const Board& board)
    {
        for (AttemptAndFeedback tempo : board.attempts_and_feedbacks) // r�cup�re un � un les �l�ment du vecteur en les stockant sur tempo   (foreach en c#) 
        {
            if (tempo.feedback.bulls == game_options.number_of_characters_per_code) // on regarde si on a bien 5 bulls pour savoir si on a gagn�
            {
                return true;
            }
        }
        return false;
    }

    void display_board(std::ostream& output_stream, const GameOptions& game_options, const Board& board)
    {
        Code secret{};
        const char star = '-';
        if (is_win(game_options, board) || is_end_of_game(game_options, board))
        {
            secret.value = board.secret_code.value;
        }

        else
        {
            for (unsigned int i = 0; i < game_options.number_of_characters_per_code; i++)
            {
                secret.value.push_back(star);
                secret.value.push_back(' ');
            }
        }

        output_stream << "----------------------------\n"
            "| SECRET"
            << secret.value
            << "|                        | \n"
            "----------------------------------|\n"
            "| ATTEMPTS           | bulls_and_cows| COWS| \n"
            "------------------------------------| \n";


        for (auto element : board.attempts_and_feedbacks) //element parcourt le vecteur de tentative attempt and feedbacks qui est compos� de bulls and cows
        {
            output_stream << "| " << element.attempt.value << "\t\t | " << element.feedback.bulls << "\t   | "
                << element.feedback.cows << "\t   | \n"; // affiche la tentative entrer et les bulls and cows
        }
        output_stream << "-------------------\n";

    }

    Code ask_attempt(std::ostream& output_stream, std::istream& input_stream, const GameOptions& game_options,
        const Board& board)
    {
        Code attempt{}; // cr�er un code attempt

        // attempt.value = ask_string(input_stream); autre m�thode

        auto nb_attempt = board.attempts_and_feedbacks.size() + 1; // augment le nb_attempt de 1 quand on a essay� une fois
        unsigned int nb_char = game_options.number_of_characters_per_code; // nombre de caract�res qu'on doit rentrer (ici 5)
        const char max = game_options.maximum_allowed_character;// d�finit le caract�re maximum (ici Z)
        const char min = game_options.minimum_allowed_character; // d�finit le caract�re minimum (ici A)

        output_stream << "This is your " << nb_attempt << " attempt, choose " << nb_char << " characters between " << min
            << " et " << max << ": ";
        attempt.value = ask_string(input_stream); // input stream c'est la saisie de l'utilisateur on va v�rifier que c'est un string et si ca l'est on la met dans attempt.value
        return attempt;

    }

} // namespace bulls_and_cows