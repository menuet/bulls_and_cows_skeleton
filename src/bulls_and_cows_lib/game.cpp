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
		  // board creation, adding a random code
		  Board mon_board{};
		  AttemptAndFeedback my_feedback{};
		  mon_board = create_board(game_options);



		  do
		  {
			  std::cout << "\n";
			  display_board(std::cout, game_options, mon_board); //afficher le board



			  my_feedback.attempt = ask_attempt(std::cout, std::cin, game_options, mon_board);



			  while (!validate_attempt(game_options, my_feedback.attempt)) //tester si la tentative est bonne, sinon essayer de nouveau
			  {
				  std::cout << "Your attempt is not valid, try again\n";
				  my_feedback.attempt = ask_attempt(std::cout, std::cin, game_options, mon_board);
			  }


			  // comparer la tentavie avec le code secret, pour voir si c'est bon
			  my_feedback.feedback = compare_attempt_with_secret_code(my_feedback.attempt, mon_board.secret_code);
			  mon_board.attempts_and_feedbacks.push_back(my_feedback);



		  } 
		  while (!(is_end_of_game(game_options, mon_board)) && !(is_win(game_options, mon_board)));
		  std::cout << "\n";
		  display_board(std::cout, game_options, mon_board);

		  if (is_win(game_options, mon_board)) // voir si le joueur a trouver le bon code secret
		  {
			  std::cout << "\n"
				  << "You won the game! The secret code is : " << mon_board.secret_code.value << "\n";
		  }
		  else // si le code secret est faux et que le nb de tentative max est atteint
		  {
			  std::cout << "\n"
				  << "GAME OVER ! The secret code is : " << mon_board.secret_code.value << "\n";
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
		bool menuretour = false;
		std::string path = "C:\DEVCPP\PROJECTS\bulls_and_cows_skeleton\game_options.txt"; // ajouter le chemin du fichier dans lequel les options vont etres enregistrer
		std::ofstream save;
		std::ifstream load_file(path);

		while (!menuretour)

		{
			display_game_options(std::cout, game_options);
			display_game_options_menu(std::cout);
			GameOptionsMenuChoice user_choice = ask_game_options_menu_choice(std::cin);
			switch ((int)user_choice) // casting method, pour transformer la variable user_choice en un int
			// des int vu que le switch n'utilise que des variables des type int

			{
			case 0:
				menuretour = true;
				break;

			case 1:
				std::cout << " 1 - Modify maximum number of attemps per game\n";
				std::cin >> game_options.max_number_of_attempts;
				break;

			case 2:
				std::cout << " 2 - Modify number of character in a code \n";
				std::cin >> game_options.number_of_characters_per_code;
				break;

			case 3:
				std::cout << "3 - Modify Minimun allowed character\n";
				std::cin >> game_options.minimum_allowed_character;
				break;

			case 4:
				std::cout << "4 - Modify Maximum allowed character \n";
				std::cin >> game_options.maximum_allowed_character;
				break;

			case 5:
				
				save.open(path);
				save_game_options(save, game_options);
				save.close();

				break;

			case 6:
				
				load_game_options(load_file, game_options);
				break;

			    default:

				break;
			}
		}
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
				std::cout << "\n GOOD BYE!\n";
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
				std::cout << "\n ERROR! enter a valid choice, try again\n";
				break;
			}
		}
	}
  } // namespace bulls_and_cows