#include "game.hpp"
#include "board.hpp"
#include "game_options.hpp"
#include "game_solver.hpp"
#include "input.hpp"
#include "main_menu.hpp"
#include "random.hpp"
#include <algorithm>
#include <chrono>
#include <fstream>
#include <iterator>
#include <thread>

namespace bulls_and_cows {

    // La methode checkDoublons permet de verifier qu'un code ne contient pas deux caract�res identiques.
    bool checkSameCharInString(std::string const& code, char const charCode)
    {
        auto result = std::find(std::begin(code), std::end(code), charCode);
        if (result != std::end(code))
        {
            // Retourne vrai si un charact�re du code et le charact�re (charCode) sont identiques.
            return true;
        }
        return false;
    }

    // La methode giveCode permet de g�n�rer al�atoirement un code en respectant les options.
    std::string giveCode(const GameOptions& game_options)
    {
        std::string secretCodeUser;
        char charCode{};
        for (int unsigned i = 0; i < game_options.number_of_characters_per_code; i++)
        {
            if (game_options.accept_doublons)
            {
                // Permet de g�n�rer al�atoirement un charact�re entre deux lettres choisies dans les options du jeu.
                charCode = generate_random_character(game_options.minimum_allowed_character,
                                                     game_options.maximum_allowed_character);
            }
            else
            {
                do
                {
                    charCode = generate_random_character(game_options.minimum_allowed_character,
                                                         game_options.maximum_allowed_character);
                    // Tant qu'il y a un doublon, on cherche un nouveau charact�re.
                } while (checkSameCharInString(secretCodeUser, charCode));
            }
            // Permet de rajouter le nouveau charact�re au secretCode.
            secretCodeUser.push_back(charCode);
        }
        return secretCodeUser;
    }

    // La methode printCode permet d'afficher le code en param�tre.
    void printCode(std::string const& code)
    {
        std::cout << code;
        std::cout << "\n";
    }

    // La methode checkDoublonsString check les doublons dans la string enti�re
    bool checkDoublonsString(std::string const& code)
    {
        std::string codeTemp = code;
        std::sort(codeTemp.begin(), codeTemp.end());
        return std::adjacent_find(codeTemp.begin(), codeTemp.end()) != codeTemp.end();
        // Retourne true si le code contient un ou plusieurs doublons.
    }

    // La methode checkErrorAttemps permet de verifier si le code entr� par le user est valide, respect les options.
    bool checkErrorAttemps(std::string const& code, const GameOptions& game_options)
    {
        if (!game_options.accept_doublons && checkDoublonsString(code))
        {
            // Si les doublons sont refus�s et qu'il y a un doublon alors retourne false.
            return false;
        }

        if (code.size() != game_options.number_of_characters_per_code)
        {
            std::cout << "La taille ne convient pas, merci de rentrer un nouveau code : \n";
            // Si taille est diff�rente des param�tres alors retourne false.
            return false;
        }

        for (const char& i : code)
        {
            if (i > game_options.maximum_allowed_character || i < game_options.minimum_allowed_character)
            {
                std::cout << "Une lettre n'est pas dans la range des options, merci de rentrer un nouveau code : \n";
                // Si les lettres sont hors range de param�tres alors retourne false.
                return false;
            }
        }
        return true;
    }

    // La methode askCodeUser permet au user de saisir un code, verification du code par checkErrorAttemps.
    std::string askCodeUser(const GameOptions& game_options)
    {
        std::string code;
        do
        {
            std::cout << "Rentrez votre code : ";
            std::cin >> code;
            // tant que le code rentr� par le user poss�de une erreur, on lui redemande un nouveau code.
        } while (!checkErrorAttemps(code, game_options));
        return code;
    }

    // La methode giveCowsNumber permet de checker si le code du user poss�de des similitudes avec le code secret et
    // retourne ce nombre.
    unsigned int giveCowsNumber(std::string const& secretCodeComputer, std::string code)
    {
        std::string codeTemp = secretCodeComputer;
        // on cherche les bulls pour les enlever afin de ne pas les compter dans le calcul de cows.
        for (int i = 0; i < code.size(); i++)
        {
            if (secretCodeComputer[i] == code[i])
            {
                code[i] = '1';
                codeTemp[i] = '0';
            }
        }
        unsigned int count{0};
        for (int i = 0; i < code.size(); i++)
        {
            for (int j = 0; j < codeTemp.size(); j++)
            {
                if (code[i] == codeTemp[j] && i != j)
                {
                    count++;
                    // lorsque l'on a compt� une cow alors on l'enl�ve du code pour ne pas la compter une seconde fois.
                    code[i] = '1';
                    codeTemp[j] = '0';
                }
            }
        }
        return count;
    }

    // La methode giveBullsNumber retourne le nombre d'�xactitude entre le code user et le code secret.
    unsigned int giveBullsNumber(std::string const& secretCodeComputer, std::string const& code)
    {
        int count{0};
        for (int unsigned i = 0; i < code.size(); i++)
        {
            if (secretCodeComputer[i] == code[i])
            {
                count++;
            }
        }
        return count;
    }

    // La methode checkWin permet de retourner un bool pour verifier la victoire ou la defaite d'un joueur.
    bool checkWin(std::string const& secretCodeComputer, std::string const& code)
    {
        return secretCodeComputer == code;
    }

    // La methode askCodeComputer permet de g�n�rer un code lorsque l'ordinateur joue contre lui-meme.
    std::string askCodeComputer(const GameOptions& game_options, std::vector<FinalBoard> const& finalBoard)
    {
        std::string code;
        bool accept{true};
        do
        {
            code = giveCode(game_options);
            for (unsigned int i = 1; i < finalBoard.size(); i++)
            {
                if (code == finalBoard[i].secretCodeUser)
                {
                    accept = false;
                }
                else
                {
                    accept = true;
                }
            }
        } while (!accept);
        return code;
    }

    void user_plays_against_computer(const GameOptions& game_options)
    {
        std::string secretCodeComputer =
            giveCode(game_options); // nous g�n�rons un code al�atoire avec les param�tres demand�s dans game_options.
        printCode(secretCodeComputer); // permet d'afficher un code, ici le secret code pour d�bugger.
        std::cout << "\n";

        std::vector<FinalBoard> finalBoards; // creation d'un vector de structure : secretCodeUser, bulls, cows.
        finalBoards.push_back(FinalBoard(secretCodeComputer, 0, 0)); // initialisation du vector avec le secretCodeUser.

        GameStatus win = GameStatus::Continue;
        do
        {
            std::string code;
            code = askCodeUser(game_options);

            unsigned int bulls = giveBullsNumber(secretCodeComputer, code); // retourne le nombre de bulls.
            unsigned int cows = giveCowsNumber(secretCodeComputer, code);   // retourne le nombre de cows.

            finalBoards.emplace_back(code, bulls, cows); // on fill la list avec les infos du tour.

            boardGame(finalBoards, game_options, std::cout); // permet d'afficher le resultat dans la console.

            if (checkWin(secretCodeComputer, code)) // condition de victoire.
            {
                std::cout << "You win \n";
                win = GameStatus::Win;
            }
            if (finalBoards.size() - 1 == game_options.max_number_of_attempts) // condition de d�faite.
            {
                std::cout << "you lose \n";
                win = GameStatus::Lose;
            }
        } while (win == GameStatus::Continue);

        if (game_options.save_game == true) // si l'utilisateur choisit d'enregistrer sa partie
        {
            std::ofstream monFlux("C:/C++/PROJECTS/bulls_and_cows_skeleton/save.txt");
            if (monFlux)
            {
                boardGame(finalBoards, game_options, monFlux);
            }
        }
    }

    void computer_plays_against_computer(const GameOptions& game_options)
    {
        std::vector<std::string> allPossibilities = createAllPossibilities(game_options);
        std::string secretCodeComputer =
            giveCode(game_options); // nous g�n�rons un code al�atoire avec les param�tres demand�s dans game_options
        printCode(secretCodeComputer); // permet d'afficher un code, ici le secret code pour d�bugger
        std::cout << "\n";

        std::vector<FinalBoard> finalBoards; // creation d'un vector de structure : secretCodeUser, bulls, cows.
        finalBoards.push_back(FinalBoard(secretCodeComputer, 0, 0)); // initialisation du vector avec le secretCodeUser.

        GameStatus win = GameStatus::Continue;
        do
        {
            std::string code = randomInPossibilities(allPossibilities);
            
            unsigned int bulls = giveBullsNumber(secretCodeComputer, code);
            unsigned int cows = giveCowsNumber(secretCodeComputer, code);

            finalBoards.emplace_back(code, bulls, cows);
            boardGame(finalBoards, game_options, std::cout);
            std::cout << "nombre de possibilites restantes : " << allPossibilities.size() << "\n";
            deleteIncorrectPoissibilities(allPossibilities, code, bulls, cows);

            std::this_thread::sleep_for(std::chrono::milliseconds(500));

            if (checkWin(secretCodeComputer, code))
            {
                std::cout << "You win \n";
                win = GameStatus::Win;
            }
            if (finalBoards.size() - 1 == game_options.max_number_of_attempts)
            {
                win = GameStatus::Lose;
                std::cout << "you lose \n";
            }

        } while (win == GameStatus::Continue);

        if (game_options.save_game == true)
        {
            std::ofstream monFlux("C:/C++/PROJECTS/bulls_and_cows_skeleton/save.txt");
            if (monFlux)
            {
                boardGame(finalBoards, game_options, monFlux);
            }
        }
    }

    void configure_game_options(GameOptions& game_options)
    {
        int menu{0};

        std::cout << "\nVoici les options : \n";
        std::cout << "1- Afficher les options du jeu : \n";
        std::cout << "2- Modifier les options du jeu : \n";
        std::cout << "3- Sauvegarder les options du jeu en cours : \n";
        std::cout << "4- Charg� les options deja sauvegarder dans un fichier : \n";
        std::cout << "5- Quitter : \n";
        std::cout << "Choix de menu : \n";
        std::cin >> menu;

        // utilisation de if au lieu de switch, pour initialiser la variable monFlux seulement lors du print dans le
        // fichier.
        if (menu == 1)
        {
            printOptions(game_options, std::cout);
        }
        else if (menu == 2)
        {
            modifOptions(game_options);
        }
        else if (menu == 3)
        {
            std::ofstream monFlux("C:/C++/PROJECTS/bulls_and_cows_skeleton/game_options.txt");
            if (monFlux)
            {
                printOptions(game_options, monFlux);
                std::cout << "Options bien enregistre\n";
            }
            else
                std::cout << "fichier introuvable\n";
        }
        else if (menu == 4)
        {
            loadGame_options(game_options);
        }
        else
            std::cout << "retour vers le menu";
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
