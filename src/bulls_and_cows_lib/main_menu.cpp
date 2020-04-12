
#include "main_menu.hpp"
#include "input.hpp"

namespace bulls_and_cows {

    void display_main_menu(std::ostream& output_stream)
    {
        output_stream << "Welcome to Bulls And Cows\n"
                         "0 - Quit\n"
                         "1 - Play against the computer\n"
                         "2 - Watch computer playing against itself\n"
                         "3 - Configure options\n"
                         "What is your choice ? ";
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
        default:
            return MainMenuChoice::Error;
        }
       
    }

} // namespace bulls_and_cows
