#include "game_options.hpp"
#include "game.hpp"
#include <fstream>
#include <iostream>
#include <string>

namespace bulls_and_cows {

    // Permet d'afficher les options du jeu dans la console ou sur un fichier.
    void printOptions(const GameOptions& game_options, std::ostream& output_stream)
    {
        output_stream << "minimum_allowed_character=" << game_options.minimum_allowed_character << "\n";
        output_stream << "maximum_allowed_character=" << game_options.maximum_allowed_character << "\n";
        output_stream << "number_of_characters_per_code=" << game_options.number_of_characters_per_code << "\n";
        output_stream << "max_number_of_attempts=" << game_options.max_number_of_attempts << "\n";
        output_stream << "save_game=" << game_options.save_game << "\n";
        output_stream << "accept_doublons=" << game_options.accept_doublons << "\n";
    }

    // Permet de modifier les options pendant une partie.
    void modifOptions(GameOptions& gameoption1)
    {
        std::cout << "Caractère min : ";
        std::cin >> gameoption1.minimum_allowed_character;

        std::cout << "Caractère max : ";
        std::cin >> gameoption1.maximum_allowed_character;

        std::cout << "Nbr caractère par code : ";
        std::cin >> gameoption1.number_of_characters_per_code;

        std::cout << "Nbr attemps : ";
        std::cin >> gameoption1.max_number_of_attempts;

        char choice(0);
        std::cout << "Save Game (T / F) : ";
        std::cin >> choice;
        gameoption1.save_game = (choice == 'T');

        choice = 0;
        std::cout << "Doublons acceptés (T / F) : ";
        std::cin >> choice;
        gameoption1.accept_doublons = (choice == 'T');
    }

    //La methode loadGame_options permet à l'utilisateur de charger les options sauvegardées.
    void loadGame_options(GameOptions& gameoption1)
    {
        std::ifstream fichier("C:/C++/PROJECTS/bulls_and_cows_skeleton/game_options.txt");

        if (fichier) //si le fichier existe.
        {
            std::string ligne;
            while (getline(fichier, ligne))//permet de recuperer chaque ligne du fichier.
            {
                unsigned int count = 0;
                std::string strucElement="";
                std::string value="";
                //grace à cette boucle, nous parcourrons la ligne afin d'identifié l 'element et sa valeur.
                for (char c : ligne)
                {
                    if (count == 0)
                    {
                        strucElement.push_back(c);
                    }
                    else
                    {
                        value.push_back(c);
                    }
                    if (c == '=') //symbole de séparation entre l'element et sa valeur.
                    {
                        count = 1;
                    }
                }
                //affectation des valeurs en fonction de leur element / place dans la structure.
                if (strucElement == "minimum_allowed_character=")
                {
                    gameoption1.minimum_allowed_character = value[0];
                }
                else if (strucElement == "maximum_allowed_character=")
                {
                    gameoption1.maximum_allowed_character = value[0];
                }
                else if (strucElement == "number_of_characters_per_code=")
                {
                    gameoption1.number_of_characters_per_code = std::stoi(value);
                }
                else if (strucElement == "max_number_of_attempts=")
                {
                    gameoption1.max_number_of_attempts = std::stoi(value);
                }
                else if (strucElement == "save_game=")
                {
                    gameoption1.save_game = std::stoi(value);
                }
                else if (strucElement == "accept_doublons=")
                {
                    gameoption1.save_game = std::stoi(value);
                }
            }
        }
        else
        {
            std::cout << "Problème de fichier";
        }
        std::cout << "les options chargées : \n";
        printOptions(gameoption1, std::cout); //afficher les nouvelles options chargées.
    }
} // namespace bulls_and_cows
