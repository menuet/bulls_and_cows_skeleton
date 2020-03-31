
#include "board.hpp"
#include "random.hpp"

namespace bulls_and_cows {

    // TODO: define the body of the functions declared in board.cpp

    // Create a board and with a new random secret code composed of allowed characters
    Board create_board(const GameOptions& game_options){
        Board b;

        // on va declarer une classe string sc pour la concatenation de tout ce que la fonction generate_random_character renvoie.
        std::string sc = "";
        for (int i = 0; i < game_options.number_of_characters_per_code, i++){

             // concatenation.
             sc = sc + generate_random_character(game_options.minimum_allowed_character, game_options.maximum_allowed_character)


        }

        // attribution du resultat de la concatenation au membre secret_code.
        b.secret_code.value= sc;

        return b;

        
    }



    // Validate that a user-entered code contains proper number of allowed characters
    bool validate_attempt(const GameOptions& game_options, const Code& attempt){
        bool att= false;
        // comparaison du nombre de caracteres de l essai et celui du secret_code

        if (attempt.value.size == game_options.number_of_characters_per_code ){
            att = true;
            std::cout << "proper number of allowed character" << endl;
        }
        else{
            att= false
            std::cout << " no proper number of allowed character" << endl;
           // std::cout << "number of allowed character is "+ game_options.number_of_characters_per_code << endl;
        }
        return att;
        //-----------------------------------------------------------------------------------------
        

        // on verifie que les caracteres du attempt soient compris entre les min et max allowed character
        //  pour chaque valeur i de attempt on compare avec les min et max allowed character
        bool att2= true;

        int i = 0;
        while (att2 ==true &&  i < game_options.number_of_characters_per_code){
             att2= (attempt.value[i] > game_options.minimum_allowed_character && attempt.value[i]< game_options.maximum_allowed_character ){
             i++; 
            
         }
        return att2;
        
    }



    // Compare a user-entered code with the secret code and give the corresponding number of bulls and cows
    Feedback compare_attempt_with_secret_code(const Code& attempt, const Code& secret_code){
        Feedback f;
        // range for : pour parcourir tous les characteres aue l utilisateur a entre 
        for (int i: attempt.value){

            // range for : pour parcourir tous les characteres du code secret
            for (int j: secret_code.value){
                // 1) on verifie que le charactere est present dans la le code  2) et qu'il est bien place
                if (attempt.value[i] == secret_code.value[j] && i ==j ){
                    f.bulls++;
                }

                else {
                    // 1) on verifie que le charactere est present dans le code  2) mais qu'il est mal place
                    if (attempt.value[i] == secret_code.value[j] && i !=j ){
                        f.cows++;
                    }  
                    
                    else{
                        // si le charactere ne fait pas partie du code
                        return 0;
                    }
                }
                
            }
        return f;
        }
    }


} // namespace bulls_and_cows
