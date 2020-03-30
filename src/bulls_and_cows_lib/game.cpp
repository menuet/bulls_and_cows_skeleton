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

namespace bulls_and_cows {

    void user_plays_against_computer(const GameOptions& game_options)
    {
        Board board = create_board(game_options);
        AttemptAndFeedback attempt_and_feedback;

        do
        {
            display_board(std::cout, game_options, board);

            attempt_and_feedback.attempt = ask_attempt(std::cout, std::cin, game_options, board);

            attempt_and_feedback.feedback =
                compare_attempt_with_secret_code(attempt_and_feedback.attempt, board.secret_code);

            board.attempts_and_feedbacks.push_back(attempt_and_feedback);
        }

        while (!is_end_of_game(game_options, board) && !is_win(game_options, board));

        display_board(std::cout, game_options, board);

        if (is_win(game_options, board))
        {
            std::cout << "Bravo ! Vous avez gagne la partie !" << std::endl;
        }

        else
        {
            std::cout << "Dommage ! Vous avez perdu..." << std::endl;
        }
    }

    void computer_plays_against_computer(const GameOptions& game_options)
    {
        std::cout
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
               "    Display a message telling if the computer won or lost\n";
    }

    void configure_game_options(GameOptions& game_options)
    {
        std::string path = "./save.txt";
        std::ofstream save_file;
        std::ifstream load_file(path);
        GameOptionsMenuChoice op;

        do
        {
            std::cout << "\n#################################\n";
            display_game_options(std::cout, game_options);
            std::cout << "\n#################################\n";
            display_game_options_menu(std::cout);
            GameOptionsMenuChoice choice = ask_game_options_menu_choice(std::cin);
            op = choice;

            switch (choice)
            {
            case GameOptionsMenuChoice::ModifyMaximumNumberOfAttempts:
                std::cout << "\nEntrez le nombre maximum de tentatives autorisees :\n";
                game_options.max_number_of_attempts = ask_int_or_default(std::cin, game_options.max_number_of_attempts);
                break;
            case GameOptionsMenuChoice::ModifyNumberOfCharactersPerCode:
                std::cout << "\nEntrez le nombre de caracteres pour le code secret :\n";
                game_options.number_of_characters_per_code =
                    ask_int_or_default(std::cin, game_options.number_of_characters_per_code);
                break;
            case GameOptionsMenuChoice::ModifyMinimumAllowedCharacter:
                std::cout << "\nEntrez le caractere minimum autorise pour le code secret :\n";
                char min;
                min = ask_char_or_default(std::cin, game_options.minimum_allowed_character);

                if (min >= game_options.maximum_allowed_character)
                {
                    std::cout << "\nLe caractere minimum ne peut pas être superieur compare au caractere maximum\n";
                }

                else
                    game_options.minimum_allowed_character = min;
                break;
            case GameOptionsMenuChoice::ModifyMaximumAllowedCharacter:
                std::cout << "\nEntrez le caractere maximum autorise pour le code secret :\n";
                char max;
                max = ask_char_or_default(std::cin, game_options.maximum_allowed_character);

                if (max <= game_options.minimum_allowed_character)
                {
                    std::cout << "\nLe caractere maximum ne peut pas être inferieur compare au caractere minimum\n";
                }

                else
                    game_options.maximum_allowed_character = max;
                break;
            case GameOptionsMenuChoice::SaveOptions:
                save_file.open(path);

                if (!save_game_options(save_file, game_options))
                {
                    std::cout << "Erreur avec le fichier en ecriture\n";
                }

                save_file.close();
                break;
            case GameOptionsMenuChoice::LoadOptions:
                load_file.seekg(0, std::ios::beg);

                if (!load_game_options(load_file, game_options))
                {
                    std::cout << "Erreur avec le fichier en lecture\n";
                }
                break;
            case GameOptionsMenuChoice::Error:
                std::cout << "Vous n'avez pas rentre un choix valide, veuillez reessayer\n";
                break;
            }
        }

        while (op != GameOptionsMenuChoice::BackToMain);
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
                std::cout << "\nAu revoir !\n";
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
                std::cout << "\nVous n'avez pas entre un choix valide, veuillez reessayer\n";
                break;
            }
        }
    }

} // namespace bulls_and_cows