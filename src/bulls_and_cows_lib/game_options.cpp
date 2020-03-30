
#include "game_options.hpp"
#include "input.hpp"

namespace bulls_and_cows {

    // TODO: define the body of the functions declared in game_options.cpp
    void display_game_options_menu(std::ostream& output_stream)
    {
        output_stream << "#################################\n"
                      << "0 - Back to main menu\n"

    }
    void display_game_options(std::ostream& output_stream, const GameOptions& game_options)// on va mettre en parametre les game option pour y avoir accès à l'affichage le"." est pour voir l'attribut dans la struct
    {
        output_stream << "\n#################################\nHere are the current game_options:\n"
                      << "Maximum number of attempts per game: " << game_options.max_number_of_attempts << "\n"
                      << "Number of characters in a code: " << game_options.number_of_characters_per_code << "\n"
                      << "Range of allowed characters: from '" << game_options.minimum_allowed_character << "' to '"
                      << game_options.maximum_allowed_character << "'\n";
    }

    GameOptionsMenuChoice ask_game_options_menu_choice(std::istream& input_stream)//stream entrant donc demande à lutilisateur
    {
    
        switch (ask_int_or_default(input_stream,-1))
        {
        
            case 0:
                 return GameOptionsMenuChoice::BackToMain;


            default:
                  return GameOptionsMenuChoice::Error;
            
        }
    }
    bool save_game_options(std::ostream& output_file_stream, const GameOptions& game_options)//  Les streams sont pas différent des autres juste qu'ils sont sortant on voit quon va dans un fichier txt
    {
        output_file_stream << "max_number_of_attempts=" << game_options.max_number_of_attempts << "\n"
                           << "number_of_characters_per_code=" << game_options.number_of_characters_per_code << "\n"
                           << "minimum_allowed_character=" << game_options.minimum_allowed_character << "\n"
                           << "maximum_allowed_character=" << game_options.maximum_allowed_character << "\n";
        return true;
    }

    bool load_game_options(std::istream& input_file_stream, GameOptions& game_options)//stream entrant & gameoption
    {
        
       
            std::string line;//string prenant toute les lignes 1 a 1
            while (std::getline(input_file_stream, line))//tant qu'il arrive a recuper une ligne ça sera stocker dans line et il recupere avvec input file stream
            {
                
                std::size_t delimiter = line.find("=");//renvoie la position de = dans la ligne 
                std::string token = line.substr(0, delimiter);//delimiter l'indice du égale sans le prendre & token partie nom qui va de 0 à delimiter. substr pend une partis du string 
                std::string numb = line.substr(delimiter + 1);//on ira jusqu'à la fin du string apres le =
                if (numb != "")//verifie le fichier si il est bien ecris
                {
                    if (token == "max_number_of_attempts")
                        game_options.max_number_of_attempts = std::atoi(numb.c_str());//conversion d'un string en entier avec atoi & c_str transformer un string en tab de char
                    else if (token == "number_of_characters_per_code")
                        game_options.number_of_characters_per_code = std::atoi(numb.c_str());

                    else if (token == "minimum_allowed_character")
                    {
                        game_options.minimum_allowed_character = numb[0];// on stock des char donc on met entre chochet pour recup le premier char du string
                    }

                    else if (token == "maximum_allowed_character")
                    {
                        game_options.maximum_allowed_character = numb[0];
                    }
                    else
                    {
                        std::cout << "Error, file corrupted\n";//si cela correspond pas avec ceux d'avant si il reconnait pas le format il fera erreur
                        break;
                    }
                }
                else
                {
                    std::cout << "Error, file corrupted\n";//correspond à celui de la ligne 58
                    break;//nous fait sortir de l'itération du while 
                }
            }
            return true;
        
    }
} // namespace bulls_and_cows
