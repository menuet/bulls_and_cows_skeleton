#include "game.hpp"
#include "board.hpp"
#include "game_options.hpp"
#include "game_solver.hpp"
#include "input.hpp"
#include "main_menu.hpp"
#include "random.hpp"
#include <chrono>
#include <fstream>
#include <iterator>
#include <thread>

namespace bulls_and_cows {

    // La methode checkDoublons permet de verifier qu'un code ne contient pas deux caractères identiques.
    bool checkSameCharInString(std::string const& code, char const charCode)
    {
        auto result = std::find(std::begin(code), std::end(code), charCode);
        if (result != std::end(code))
        {
            return true;
        }
        return false;
    }

    // La methode giveCode permet de générer aléatoirement un code en respectant les options.
    std::string giveCode(const GameOptions& game_options)
    {
        std::string secretCodeUser;
        char charCode{};
        for (int unsigned i = 0; i < game_options.number_of_characters_per_code; i++)
        {
            if (game_options.accept_doublons)
            {
                charCode = generate_random_character(game_options.minimum_allowed_character,
                                                     game_options.maximum_allowed_character);
            }
            else
            {
                do
                {
                    charCode = generate_random_character(game_options.minimum_allowed_character,
                                                         game_options.maximum_allowed_character);
                } while (checkSameCharInString(secretCodeUser, charCode));
            }
            secretCodeUser.push_back(charCode);
        }
        return secretCodeUser;
    }

    // La methode printCode permet d'afficher le code en paramètre.
    void printCode(std::string const& code)
    {
        std::cout << code;
        std::cout << "\n";
    }

    // La methode checkDoublonsString check les doublons dans la string entière
    bool checkDoublonsString(std::string const& code)
    {
        for (int unsigned i = 0; i < code.size(); i++)
        {
            for (int unsigned j = i + 1; j < code.size(); j++)
            {
                if (code[i] == code[j])
                {
                    std::cout << "Il y a deux fois la même lettre, merci de rentrer un nouveau code : \n";
                    return true;
                }
            }
        }
        return false;
    }

    // La methode checkErrorAttemps permet de verifier si le code entré par le user est valide, respect les options.
    bool checkErrorAttemps(std::string const& code, const GameOptions& game_options)
    {
        if (game_options.accept_doublons)
        {
            if (code.size() != game_options.number_of_characters_per_code)
            {
                std::cout << "La taille ne convient pas, merci de rentrer un nouveau code : \n";
                return false;
            }

            for (const char& i : code)
            {
                if (i > game_options.maximum_allowed_character || i < game_options.minimum_allowed_character)
                {
                    std::cout
                        << "Une lettre n'est pas dans la range des options, merci de rentrer un nouveau code : \n";
                    return false;
                }
            }
        }
        else
        {
            if (checkDoublonsString(code))
            {
                return false;
            }
            if (code.size() != game_options.number_of_characters_per_code)
            {
                std::cout << "La taille ne convient pas, merci de rentrer un nouveau code : \n";
                return false;
            }

            for (const char& i : code)
            {
                if (i > game_options.maximum_allowed_character || i < game_options.minimum_allowed_character)
                {
                    std::cout
                        << "Une lettre n'est pas dans la range des options, merci de rentrer un nouveau code : \n";
                    return false;
                }
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
        } while (!checkErrorAttemps(code, game_options));
        return code;
    }

    // La methode giveCowsNumber permet de checker si le code du user possède des similitudes avec le code secret et
    // retourne ce nombre.
    unsigned int giveCowsNumber(std::string const& secretCodeComputer, std::string const& code)
    {
        std::string codeTemp = secretCodeComputer;
        // ignore bulls when counting cows
        for (int i = 0; i < code.size(); i++)
        {
            if (secretCodeComputer[i] == code[i])
            {
                codeTemp[i] = '0';
            }
        }
        printCode(codeTemp);
        unsigned int count{0};
        for (int i = 0; i < code.size(); i++)
        {
            for (int j = 0; j < codeTemp.size(); j++)
            {
                if (code[i] == codeTemp[j] && i!=j)
                {
                    count++;
                    printCode(codeTemp);
                    // To count each character only 1 time, we change their value to a forbidden character
                    codeTemp[j] = '0';
                }
            }
        }
        return count;
    }

    // La methode giveBullsNumber retourne le nombre d'éxactitude entre le code user et le code secret.
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

    // La methode askCodeComputer permet de générer un code lorsque l'ordinateur joue contre lui-meme.
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
            }
        } while (!accept);
        return code;
    }

    void user_plays_against_computer(const GameOptions& game_options)
    {
        std::string secretCodeComputer =
            giveCode(game_options); // nous générons un code aléatoire avec les paramètres demandés dans game_options
        printCode(secretCodeComputer); // permet d'afficher un code, ici le secret code pour débugger
        std::cout << "\n";

        std::vector<FinalBoard> finalBoards; // creation d'un vector de structure : secretCodeUser, bulls, cows.
        finalBoards.push_back(FinalBoard(secretCodeComputer, 0, 0)); // initialisation du vector avec le secretCodeUser.

        GameStatus win = GameStatus::Continue;
        do
        {
            std::string code;
            code = askCodeUser(game_options);

            unsigned int bulls = giveBullsNumber(secretCodeComputer, code);
            unsigned int cows = giveCowsNumber(secretCodeComputer, code);

            finalBoards.emplace_back(code, bulls, cows);

            boardGame(finalBoards, game_options, std::cout);

            if (checkWin(secretCodeComputer, code))
            {
                std::cout << "You win \n";
                win = GameStatus::Win;
            }
            if (finalBoards.size() - 1 == game_options.max_number_of_attempts)
            {
                std::cout << "you lose \n";
                win = GameStatus::Lose;
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

    void computer_plays_against_computer(const GameOptions& game_options)
    {
        std::string secretCodeComputer =
            giveCode(game_options); // nous générons un code aléatoire avec les paramètres demandés dans game_options
        printCode(secretCodeComputer); // permet d'afficher un code, ici le secret code pour débugger
        std::cout << "\n";

        std::vector<FinalBoard> finalBoards; // creation d'un vector de structure : secretCodeUser, bulls, cows.
        finalBoards.push_back(FinalBoard(secretCodeComputer, 0, 0)); // initialisation du vector avec le secretCodeUser.

        GameStatus win = GameStatus::Continue;
        do
        {
            std::string code;
            code = askCodeComputer(game_options, finalBoards);

            unsigned int bulls = giveBullsNumber(secretCodeComputer, code);
            unsigned int cows = giveCowsNumber(secretCodeComputer, code);

            finalBoards.emplace_back(code, bulls, cows);

            boardGame(finalBoards, game_options, std::cout);

            std::this_thread::sleep_for(std::chrono::milliseconds(1000));

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
            boardGame(finalBoards, game_options, monFlux);
        }
    }

    GameOptions configure_game_options(GameOptions& game_options)
    {
        GameOptions gameoption1;
        int menu{0};
        do
        {
            std::cout << "Voici les options : \n";
            std::cout << "1- Afficher les options du jeu : \n";
            std::cout << "2- Modifier les options du jeu : \n";
            std::cout << "0- Revenir au menu principal : \n";
            std::cout << "choix de menu : \n";
            std::cin >> menu;

            switch (menu)
            {
            case 1:
                printOptions(gameoption1);
            case 2:
                modifOptions(gameoption1);
            default:
                break;
            }
        } while (menu == 0);

        return gameoption1;
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
                game_options = configure_game_options(game_options);
                break;
            case MainMenuChoice::Error:
                std::cout << "\nYou did not enter a valid choice, please try again\n";
                break;
            }
        }
    }
} // namespace bulls_and_cows
