
#include "game_options.hpp"
#include <fstream>
#include <string>
#include <vector>
#include <array>
#include <sstream>

using namespace std; 
namespace bulls_and_cows {

    //fonction qui permet de diviser un string en vecteur de string. on l utilise dans load_game_options
    vector<string> split(string strToSplit, char delimeter)
    {
        stringstream ss(strToSplit);
        string item;
        vector<string> splittedStrings;
        while (getline(ss, item, delimeter))
        {
            splittedStrings.push_back(item);
        }
        return splittedStrings;
    }

   bool save_game_options(std::ostream& output_file_stream, const GameOptions& game_options)
    {
       string Path; //contient le chemin jusqu'au fichier de sauvegarde
       cout << "Choisissez le chemin de sauvegarde du fichier" << endl;
       cin >> Path;

       string Data = "max_number_of_attempts=" + to_string(game_options.max_number_of_attempts) + "\n";
       Data += "number_of_characters_per_code=" + to_string(game_options.number_of_characters_per_code) + "\n";
       Data += "minimum_allowed_character=" + to_string(game_options.minimum_allowed_character) + "\n";
       Data += "maximum_allowed_character=" + to_string(game_options.maximum_allowed_character) + "\n"; //contient la data de la game_option

       output_file_stream << Data; // pour valider le test

       //code pour ecrire dans un fichier (copier colle stackoverflow)
       ofstream myfile;
       myfile.open(Path);
       myfile << Data;
       myfile.close();

       return true; //function doit retourner un bool donc voila
   }

      bool load_game_options(std::istream& input_file_stream, GameOptions& game_options)
   {
          string Path; //contient le chemin jusqu'au fichier de sauvegarde
          cout << "Choisissez le chemin du fichier a importer" << endl;
          cin >> Path;

          ifstream inFile;
          inFile.open(Path); // on ouvre le fichier 

          if (!inFile) //verification qu il s est bien ouvert
          {
              cerr << "Impossible d'ouvrir ce fichier";
              return false;
          }
          string str; //va contenire chaque ligne 
              while (getline(inFile, str)) // on parcours les lignes 1 par 1
          {
              vector<string> tokens = split(str, '=');
              //on remplit le game_options en fonctions des valeurs du fichier
              if (tokens[0] == "max_number_of_attempts")
              {
                  game_options.max_number_of_attempts = stoi(tokens[1]);
              }
              else if (tokens[0] == "number_of_characters_per_code")
              {
                  game_options.number_of_characters_per_code = stoi(tokens[1]);
              }
              else if (tokens[0] == "minimum_allowed_character")
              {
                  game_options.minimum_allowed_character = (char)(stoi(tokens[1])); //    stoi("65") -> 65 | (char)65 -> 'A'   
              }
              else if (tokens[0] == "maximum_allowed_character")
              {
                  game_options.maximum_allowed_character = (char)(stoi(tokens[1]));
              }
              
          }

       return true;
   }

   
   GameOptionsMenuChoice ask_game_options_menu_choice(std::istream& input_stream)
   {
       int x;
       input_stream >> x;
       GameOptionsMenuChoice choice = (GameOptionsMenuChoice)x;
       return choice;
   }

      void display_game_options(std::ostream& output_stream, const GameOptions& game_options)
   {
          output_stream << "VOICI LES GAME OPTIONS:" << endl;
       output_stream << " max_number_of_attempts = " << game_options.max_number_of_attempts << endl;
          output_stream << " number_of_characters_per_code = " << game_options.number_of_characters_per_code << endl;
       output_stream << " minimum_allowed_character = " << game_options.minimum_allowed_character << endl;
          output_stream << " maximum_allowed_character = " << game_options.maximum_allowed_character << endl;
      }

      void display_game_options_menu(std::ostream& output_stream)
      {
          output_stream << "que voulez vous changer ? " << endl;
          output_stream << "0 - retour au jeu " << endl;
          output_stream << "1 - max_number_of_attempts" << endl;
          output_stream << "2 - number_of_characters_per_code" << endl;
          output_stream << "3 - minimum_allowed_character" << endl;
          output_stream << "4 - maximum_allowed_character" << endl;
          output_stream << "5 - sauvegarder les options actuelle" << endl;
          output_stream << "6 - charger des options pres enregistrer" << endl;
      }

} // namespace bulls_and_cows
