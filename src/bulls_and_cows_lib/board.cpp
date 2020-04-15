
#include "board.hpp"


namespace bulls_and_cows {

    // TODO: define the body of the functions declared in board.cpp

    std ::string create_secret(const GameOptions& game_options, std::istream& input_stream)     //retourne le code secret entre par l'utilisateur dans la forme adequate
    {
        Code Code;
        bool verif = false;
        unsigned int compteur;

        while (verif != true)
        {
            compteur = 0;
            verif = true;
            std::cout << "Veuillez entrer votre code Secret\n";
            Code.value = ask_string(input_stream);      //recuperation du code entre par l'user
            for (int i = 0; i < Code.value.size(); i++) // parcours du code secret
            {
                compteur++;
                std ::cout << "Caractere etudie " << Code.value[i] << " -> ";
                if (Code.value[i] > game_options.maximum_allowed_character ||
                    Code.value[i] < game_options.minimum_allowed_character) // si caractere hors range definie
                {
                    verif = false;

                    std ::cout << " |!| Caractere non admis |!|\n"
                                  "Les aracteres doivent etre compris entre '"
                               << game_options.minimum_allowed_character << "' et '"
                               << game_options.maximum_allowed_character << "'\n";
                }
                else
                {
                    std::cout << "Valide\n";
                }
            }
            if (compteur != game_options.number_of_characters_per_code)     // si caractere trop long
            {
                verif = false;
                std ::cout << "Code trop long ou trop court \n"
                              "|!| Le code doit faire "
                           << game_options.number_of_characters_per_code << " caractere en longueur |!|\n";
            }
        }
        std ::cout << "Votre code : " << Code.value << " a ete valide \n";
        return Code.value;
    }

    std ::string create_secret_randomly(const GameOptions& game_options, std::istream& input_stream)    //Cree un code random
    {
        Code Code;
        std::cout << "Creation d'un code aleatoire\n";
        for (unsigned int i = 0; i < game_options.number_of_characters_per_code; i++)   //Cree le code avec le bon nombre de caractere
        {   
            Code.value.push_back(generate_random_character( game_options.minimum_allowed_character , game_options.maximum_allowed_character));
        }
        return Code.value;
    
    }
    void display_board(const GameOptions& game_options, Board Board)
    {
        // En tete
        // 1er ligne;
        std::cout << "\n-----------";
        for (unsigned int i = 0; i < game_options.number_of_characters_per_code; i++)
        {
            std::cout << "--";
        }
        std::cout << "-----------------\n";
        //2e ligne                      /!\ a changer pour afficher si réussi /!\ 
        std::cout << "| SECRET   ";
        for (unsigned int i = 0; i < game_options.number_of_characters_per_code; i++)
        {
            std::cout << " *";
        }
        std::cout << " |              |\n";
        // 3e ligne
        std::cout << "-----------";
        for (unsigned int i = 0; i < game_options.number_of_characters_per_code; i++)
        {
            std::cout << "--";
        }
        std::cout << "-----------------\n";
        // 4e ligne
        std::cout << "| ATTEMPTS ";
        for (unsigned int i = 0; i < game_options.number_of_characters_per_code; i++)
        {
            std::cout << "  ";
        }
        std::cout << " | BULLS | COWS |\n";
        // 5e ligne
        std::cout << "-----------";
        for (unsigned int i = 0; i < game_options.number_of_characters_per_code; i++)
        {
            std::cout << "--";
        }
        std::cout << "-----------------\n";

        // Lignes evoluant en fonction du nombre d'essais
        for (int i = game_options.max_number_of_attempts; i > 0; i--)
        {
            std::cout << "| #" << i << "      ";
            if (i < 10) // decalage pour compenser la perte du chiffre des dizaines
            {
                std::cout << " ";
            }
            // affichage d'un essai realise
            if (Board.attempts_and_feedbacks.size() >= i)
            {
                for (unsigned int j = 0; j < game_options.number_of_characters_per_code; j++)
                {
                    std::cout << " " << Board.attempts_and_feedbacks[i - 1].attempt.value[j];
                }
                std::cout << " |   " << Board.attempts_and_feedbacks[i - 1].feedback.bulls << "   |   "
                          << Board.attempts_and_feedbacks[i - 1].feedback.cows << "  |\n";
            }
            // cas ou l'essai n'a pas encore ete fait
            else
            {
                for (unsigned int j = 0; j < game_options.number_of_characters_per_code; j++)
                {
                    std::cout << " .";
                }
                std::cout << " |       |      |\n";
            }
        }
        // Bas de page
        std::cout << "-----------";
        for (unsigned int i = 0; i < game_options.number_of_characters_per_code; i++)
        {
            std::cout << "--";
        }
        std::cout << "-----------------\n";
    }


    std ::string create_attempt(const GameOptions& game_options, std::istream& input_stream) //Valide une tentative entre par l'utilisateur
    {
        Code Code;
        bool verif = false;
        unsigned int compteur;

        while (verif != true)
        {
            compteur = 0;
            verif = true;
            std::cout << "Veuillez entrer votre proposition\n";
            Code.value = ask_string(input_stream);      // recuperation du code entre par l'user
            for (int i = 0; i < Code.value.size(); i++) // parcours du code secret
            {
                compteur++;
                if (Code.value[i] > game_options.maximum_allowed_character ||
                    Code.value[i] < game_options.minimum_allowed_character) // si caractere hors range definie
                {
                    verif = false;

                    std ::cout << "Caractere etudie " << Code.value[i] << " -> "
                               << " |!| Caractere non admis |!|\n"
                                  "Les aracteres doivent etre compris entre '"
                               << game_options.minimum_allowed_character << "' et '"
                               << game_options.maximum_allowed_character << "'\n";
                }
                else
                {
                    //std::cout << "Valide\n";
                }
            }
            if (compteur != game_options.number_of_characters_per_code) // si caractere trop long
            {
                verif = false;
                std ::cout << "Code trop long ou trop court \n"
                              "|!| Le code doit faire "
                           << game_options.number_of_characters_per_code << " caractere en longueur |!|\n";
            }
        }
        return Code.value;
    
    }
    
    bool is_win(const GameOptions& game_options, const Board& board)
    {
        bool win = false;
        for (unsigned int i = 0; i < board.attempts_and_feedbacks.size(); i++)
        {
            if (board.attempts_and_feedbacks[i].feedback.bulls == game_options.number_of_characters_per_code)
            {
                std ::cout << "\n bulls: " << board.attempts_and_feedbacks[i].feedback.bulls
                           << " nbr to reach : " << game_options.number_of_characters_per_code << "\n";
                win = true;
                return win;
            }
        }
        return win;
    }
    bool is_end_of_game(const GameOptions& game_options, const Board& board)
    {
        bool end = false;
        if (board.attempts_and_feedbacks.size() == game_options.max_number_of_attempts)
        {
            end = true;
        }
        return end;
    }

    Feedback compare_attempt_with_secret_code(const Code& attempt, const Code& secret_code)
    {
        Feedback Feedback;
        unsigned int Compteur_bulls = 0;
        unsigned int Compteur_cows = 0;
        bool cow = false;

        for (int i = 0; i < attempt.value.size(); i++)
        {
            if (secret_code.value[i] == attempt.value[i])
            {
                Compteur_bulls++;
            }
            else
            {
                for (int j = 0; j < secret_code.value.size(); j++)
                
                    if (secret_code.value[j] == attempt.value[i] && i != j)
                    {
                        cow = true;
                    }
                }
                if (cow)
                {
                    Compteur_cows++;
                }
                cow = false;
            }
        Feedback.bulls = Compteur_bulls;
        Feedback.cows = Compteur_cows ; 
        return Feedback;
    
    }

} // namespace bulls_and_cows
