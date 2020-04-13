#include "main_menu.hpp"
#include "input.hpp"

namespace bulls_and_cows {

    void display_main_menu(std::ostream& output_stream)
    {
        output_stream << "Jeu Mastermind\n"
                         "0 - Quitter\n"
                         "1 - Jouer contre l'ordinateur\n"
                         "2 - Regarder jouer l'ordinateur contre lui-meme\n"
                         "3 - Configurer les options\n"
                         "Que souhaitez-vous faire ?  ";
    }

    MainMenuChoice ask_main_menu_choice(std::istream& input_stream)
    {
        const int user_choice = ask_int_or_default(input_stream, -1);
        switch (user_choice)
        {
        case 0:
            return MainMenuChoice::Quit;
        case 1:
            return MainMenuChoice::UserPlaysAgainstComputer;
        case 2:
            return MainMenuChoice::ComputerPlaysAgainstComputer;
        case 3:
            return MainMenuChoice::ConfigureOptions;
        }
        return MainMenuChoice::Error;
    }

} // namespace bulls_and_cows