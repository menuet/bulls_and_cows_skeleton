
#include "game.hpp"
#include "board.hpp"
#include "game_options.hpp"
#include "game_solver.hpp"
#include "input.hpp"
#include "main_menu.hpp"
#include <chrono>
#include <fstream>
#include <iostream>
#include <thread>
#include <string>
#include <stdlib.h> 
#include <time.h>
#include "random.hpp"
#include <random>
#include <vector>


namespace bulls_and_cows {

    


    std::string create_code(const GameOptions& g1)// fonction qui retourne le code secret en fonction des games options( prend en parametre la reference d'une structure GameOptions g1 )
    {
        std::string code_secret;
        char Charact{};
        for (int unsigned i = 0; i < g1.number_of_characters_per_code; i++)
        {
            Charact = generate_random_character(g1.minimum_allowed_character,
                                                     g1.maximum_allowed_character);
           
            // ajoute le caractere généré de facon random dans le string code (condition si le nombre de caractere atteint celui du game option)
            code_secret.push_back(Charact);
        }
        return code_secret;
    }
    

   /* int compteur_bulls(std::string code_secret, std::string code_test, bool secret_charact_used[],
                       bool test_charact_used[])
    {
        int n = 0; //le compteur

        for (int i = 0; i < 5; i++)
        {
            if (code_secret[i] == code_test[i])
            {
                n++;
                // on note les characteres utilisées
                secret_charact_used[i] = true;
                test_charact_used[i] = true;
            }
        }

        return n;
    }*/

    
    int compteur_bullsV2(std::string code_secret, std::string code_test)
    {
        int n = 0; // le compteur
        for (int i = 0; i < code_test.size(); i++)
        {
            if (code_secret[i] == code_test[i])
            {
                n++;
            }
        }
        return n;
    }

   /* int compteur_cows(std::string code_secret, std::string code_test, bool secret_charact_used[],
                      bool test_charact_used[])
    {
        int n = 0;//le compteur

        
        for (int i = 0; i < 5; i++)
        {
            for (int j = 0; j < 5; j++)
            {
                // ne pas utiliser un charatere deja utilisé
                if (secret_charact_used[i] || test_charact_used[j])
                    continue;

                if (code_secret[i] == code_test[j])
                {
                    n++;
                    // on note les characteres utilisées
                    secret_charact_used[i] = true;
                    test_charact_used[j] = true;
                }
            }
        }

        return n;
    }*/

    unsigned int compteur_cowsV2(std::string code_secret, std::string code_test)
    {
        std::string code_temp = code_secret;
        //  ne pas utiliser un charatere deja utilisé (les bulls)
        for (int i = 0; i < code_test.size(); i++)
        {
            if (code_secret[i] == code_test[i])
            {
                code_test[i] = '1';
                code_temp[i] = '0';
            }
        }
        int n = 0; // le compteur
        for (int i = 0; i < code_test.size(); i++)
        {
            for (int j = 0; j < code_temp.size(); j++)
            {
                if (code_test[i] == code_temp[j] && i != j)
                {
                    n++;
                    // on note les characteres utilisées
                    code_test[i] = '1';
                    code_temp[j] = '0';
                }
            }
        }
        return n;
    }

    bool secure_saisie(std::string const& code, const GameOptions& g1) //retourne un bouleen en fonction de la validité de la saisie
    {
        

        if (code.size() != g1.number_of_characters_per_code)
        {
            std::cout << "Le nombre de charactere est INVALIDE, recommencez : \n";
            
            return false;// retourne faux si le nombre de caractere est invalide
        }

        for (const char& i : code)
        {
            if (i > g1.maximum_allowed_character || i < g1.minimum_allowed_character)
            {
                std::cout << "characteres non defini par les games option  : \n";

                return false;// retourne faux si les  caracteres sont hors range
            }
        }
        return true;
    }

    std::string input(const GameOptions& g1)
    {
        std::string code;
        do
        {
            std::cout << "Quel est votre tentative: ";
            std::cin >> code;
           
        } while (!secure_saisie(code, g1)); // tant que le code n'est pas valide avec une saisie secure
        return code;

    }

    void user_plays_against_computer(const GameOptions& game_options)
    {
       
        //generation du code aléatoire
        std::string code_ordi = create_code(game_options);
        //std::cout << code_ordi << std::endl; 
      

        std::cout << "Touvez le code secret de l'ordi" << std::endl;
        std::cout << "Jouons...! " << std::endl;

        unsigned int essais = 0;
        while (essais != game_options.max_number_of_attempts)
        {
            // l'utilisateur saisit son essai
            std::string test = input(game_options);
            essais++;
            /* V1 des compteurs
            // Pour marquer les caracteres qui ont ete utiliser
            bool secret_charact_used[5]= {false, false, false, false, false};
            
            bool test_charact_used[5] = {false, false, false, false, false};*/

            //int bulls = compteur_bulls(code_ordi, test, secret_charact_used, test_charact_used);
            unsigned int bulls = compteur_bullsV2(code_ordi, test);

            // condition de victoire
            if (bulls == game_options.number_of_characters_per_code)
            {
                std::cout << "Felicitation!!!" << std::endl;
                std::cout << "Vous avez trouver le code secret en  " << essais << " tentatives" << std::endl;
                break;
            }

            
            //int cows = compteur_cows(code_ordi, test, secret_charact_used, test_charact_used);
            int cows = compteur_cowsV2(code_ordi, test);

            // nouvelle tentatve
            std::cout << "Tentative " << essais << ": Votre code " << test << " possede " << bulls << " bulls et "
                      << cows << " cows." << std::endl;
        }

        // defaite
        std::cout << "Perdu... " << std::endl;
        std::cout << "Le code secret est " << code_ordi << std::endl;

        
    }
   
    //fonction qui prend en reference un vecteur et ajoute toutes les combinaisons possible de caractere possible ici 8 dans le tableau de char
    //et de longueur k
    void algo(char alpha[], std::string code, int n, int l, std::vector<std::string>& storage)
    {

        // on ajoute 1 par 1 les caracteres et on rappelle grace a la fontion suivante, en decrementant (l est egale à l-1) 

        if (l == 0)
        {
           

            storage.push_back(code);

            return;
        }


        for (int i = 0; i < n; i++)
        {
            std::string newcode;

            // nouveau caractere ajouté
            newcode = code + alpha[i];


            algo(alpha, newcode, n, l - 1, storage);
        }
    }

    void generate_all_possibles_codes(char alpha[], int k, int n, std::vector<std::string>& myvecto)// sert à rappeler de maniere recursif algo
    {
        algo(alpha, "", n, k, myvecto);
    }

     void delele_0bulls_0cows(std::vector<std::string>& allcodes, unsigned int bulls, unsigned int cows, std::string test)// fonction qui permet lorque 
       // q'une tentative a 0bulls et 0cows d'enlever touts les codes avec les meme character que la tentative
        
    {
        size_t data = allcodes.size();
        int convertdata = static_cast<int>(data);

        int x = convertdata-1;
        if (bulls == 0 && cows == 0)
        { 
            std::string code_temp;

            for (int w = 0; w < x; w++)
            {
                data = allcodes.size();
                convertdata = static_cast<int>(data);
                x = convertdata - 1;
                code_temp = allcodes[w];
                std::cout << "reflexion en cours..." << std::endl;

                for (int i = 0; i < test.size(); i++)
                {
                    for (int j = 0; j < code_temp.size(); j++)
                    {
                        if (test[i] == code_temp[j])
                        {
                            allcodes.erase(allcodes.begin() + w);
                            
                        }
                    }
                }
                
            }
            
        }
        else
        {
            
        }
    }
    

    void computer_plays_against_computer(const GameOptions& game_options)
    {

        std::cout << "First Version CPU VS CPU" << std::endl;
        std::vector<std::string> allcodes;
        char set1[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H'}; //coder en dur pour l'instant
        generate_all_possibles_codes(set1, game_options.number_of_characters_per_code, 8, allcodes);
        std::string code_ordi = create_code(game_options); // Le code SECRET
        size_t data = allcodes.size();
        int convertdata = static_cast<int>(data);

        int size = convertdata; // nombre de codes possibles
        //int x = (pow(8,5)-1) coder en dur car pb de conversion double en int par la suite
        unsigned int essais = 0;
       
        while (essais != -1)
        {
            data = allcodes.size();
            convertdata = static_cast<int>(data);

            size = convertdata-1; // nombre de codes possibles
            essais++;
            int o = generate_random_integer(0, size); // on prend un code possible aleatoirement 
            std::cout << "Le vrai code est " << code_ordi << std::endl;
            std::string test = allcodes[o];
            std::cout << "Le code test est " << test << std::endl;

            unsigned int bulls = compteur_bullsV2(code_ordi, test);

            // condition de victoire
            if (bulls == game_options.number_of_characters_per_code)
            {
                std::cout << "Felicitation!!!" << std::endl;
                std::cout << "taille du vecteur allcodes: " << allcodes.size() << '\n';
                break;
            }

            allcodes.erase(allcodes.begin() + o);// le code testé est faux on le supprime du vecteur
            
            
            unsigned int cows = compteur_cowsV2(code_ordi, test);


            delele_0bulls_0cows(allcodes, bulls, cows, test);// fonction treees longue avec qql crash
            

            std::cout << "Tentative " << essais << ": Votre code " << test << " possede " << bulls << " bulls et "
                      << cows << " cows." << std::endl;
        }
        
        }

        
       /* std::cout
            << "TODO:\n"
               "    Create a board with a randomly generated secret code\n"
               "    Generate the list of all the possible codes\n"
               "    DO\n"
               "       Display the board and the list of attempts so far\n"
               "       Display the number of remaining possible codes so far\n"
               "       Wait for 2 seconds\n"
               "       Pick a random attempt among in the list of remaining possible codes\n"
               "       Compare the computer's attempt with the secret code and deduce the number of bulls and cows\n"
               "       Add the computer's attempt to the list of attempts of the board\n"
               "       Remove all the codes that are incompatible with the attempt's feedback from the list of "
               "possible codes\n"
               "    WHILE not end of game\n"
               "    Display the board and the list of attempts so far\n"
               "    Display a message telling if the computer won or lost\n";*/








    

    void configure_game_options(GameOptions& game_options)
    {
       /* std::cout << "TODO:\n"
                     "    DO\n"
                     "       Display the current game options\n"
                     "       Display the game options menu\n"
                     "       Ask the user to type its choice\n"
                     "       Treat the user's choice\n"
                     "    UNTIL user's choice is to go back to main menu\n";*/

      

    }

    void play_game()
    {
        GameOptions game_options{};

        while (true)
        {
            std::cout << "\n#################################\n";
            display_main_menu(std::cout);

            const auto user_choice = ask_main_menu_choice(std::cin);
            switch (user_choice)
            {
            case MainMenuChoice::Quit:
                std::cout << "\nBye bye!\n";
                return;
            case MainMenuChoice::UserPlaysAgainstComputer:
                user_plays_against_computer(game_options);
                break;
            case MainMenuChoice::ComputerPlaysAgainstComputer:
                computer_plays_against_computer(game_options);
                break;
            case MainMenuChoice::ConfigureOptions:
                configure_game_options(game_options);
                break;
            case MainMenuChoice::Error:
                std::cout << "\nYou did not enter a valid choice, please try again\n";
                break;
            }
        }
    }

} // namespace bulls_and_cows
