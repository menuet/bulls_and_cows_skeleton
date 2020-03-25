//
 //  main.cpp
 //  Mastermind
 //
 //  Created by KHALIFA FARES on 3/19/20.
 //  Copyright © 2020 Art is Social. All rights reserved
 //

 #include <iostream>
 #include <string>
 #include <cstdlib>
 #include <ctime>

 using namespace std;

 bool validGuess (string guess){
     //validGuess is a simple function which determines if a player's guess is even in the realm of possible answers
     if(guess.length() != 8){//if the player inputted a guess that isn't four characters long, it's already wrong, so reject it
         return false;
     }
     for(int j = 0; j < 8; j++){
         //if the guess is four letters long, go through it letter by letter and make sure each letter is a w, W, b, or B
         if(toupper(guess[j]) != 'W' && toupper(guess[j]) != 'B'){
             return false;//if any letter of the guess isn't one of those four, the guess is invalid
         }
     }

     return true;
     //if we pass both of these checks, we have ourselves a valid guess from the player, so let the main method know

 }

 string upperCaseifier(string s){
     //really simple function to make every letter of an input string uppercase
     for(int x = 0; x < s.length(); x++){
         s[x] = toupper(s[x]);
     }

     return s;
 }

 bool hintGenerator(string guess, char* solution, int numW, int numB){
     //hintGenerator both creates the hints that the codebreaker will recieve, and also checks to see if the codebreaker has guessed the code
     bool exactlyAlike = true;//assume the guess is in fact correct until proven otherwise
     int rightColorAndPlacement = 0;//and also keep running totals of the number of pegs that are right color/right spot, and those that are right color/wrong spot, for use in the hints
     int rightColorWrongSpot = 0;

     int wrongWhiteGuessed = 0;
     int wrongBlackGuessed = 0;//these counter variables will track the number of incorrectly-placed pegs that are white and black, for use in the second hint
     for(int i = 0; i < 8; i++){//for every letter of the guess
         if(guess[i] == solution[i]){//check to see if it matches with the corresponding peg in the code. If it does
             rightColorAndPlacement++;//increment the number of perfectly right pegs by one
             if(guess[i] == 'W'){//We also need to keep track of if the perfectly correct peg is white or black. This comes into play to provide the second hint
                 numW--;
             }
             else if(guess[i]== 'B'){
                 numB--;
             }
         }
         else{//if the peg in the guess and the corresponding peg in the code are not the same
             exactlyAlike = false;//then we have found a contradiction to the two codes being the same, and change exactlyAlike to reflect that
             if(guess[i] == 'W' ){//then, we record that we have an incorrect peg that is either white or black in our two counter variables
                 wrongWhiteGuessed++;
             }
             else if(guess[i]== 'B' ){
                 wrongBlackGuessed++;
             }
         }


     }

     /* Now that we've fully iterated over the two codes, we have the exact number of perfect pegs in our player's guess. How, then, do we get the number of pegs which are of the right color, but wrong spot?
     *  We compare the number of white and black pegs remaining unguessed in the code against the number of white and black pegs the player guessed that were not matches.
     * If the number of incorrect pegs of color X is greater than or equal to the number of pegs of color X remaining in the solution, then we note that all remaining pegs of color X have been identified, if not
     * properly placed. If the number of incorrect pegs of color X is less than the number of pegs of color X remaining in the solution, we only return the number of pegs of color X that the player managed to
     * include in their solution.
     */


     if (wrongWhiteGuessed >= numW) {
         rightColorWrongSpot += numW;
     }
     else {
         rightColorWrongSpot += wrongWhiteGuessed;
     }

     if (wrongBlackGuessed >= numB) {
         rightColorWrongSpot += numB;
     }
     else {
         rightColorWrongSpot += wrongBlackGuessed;
     }

     cout << "You have " << rightColorAndPlacement << " pegs of the correct color and position." << endl;//Then we produce our two hints for the player
     cout << "You have " << rightColorWrongSpot << " pegs that are the right color, but in the wrong position." << endl << endl;

     return exactlyAlike;//and return whether or not their guess was right
 }


 int main(){
     string choice = "";

     cout << "Welcome to Bulls & Cows." << endl;




     /* Most of my input validation takes the above form, where a single cin statement is followed by a while loop, with the conditional "as long as input isn't this or this or this or this"
     * I'm not 100% a fan of this, but it's a little cleaner to read than a do-while loop, because were I to use a do-while loop, I'd need another conditional inside to determine whether or not
     * to show an error message. This way, everything involving the user inputting something correct is all nice and snug together in a single block of code
     */


     char solution [8];// First we initialize a solution character array of length 4
     bool repeat = true;//we also set up repeat, which will determine for how long players want to keep playing the game
     do{    //I'm using a do-while loop here to contain the game, since I know players will want to play at least once.
         int numBlack = 0;
         int numWhite = 0;//Set up counter variables to hold the number of black pegs and white pegs in the solution.
         srand(time(0));//Also, seed our random number generator using the time.

         for (int i = 0; i < 8; i++){//for every character in our code
             if(rand() % 2 == 0){//generate a random number, then determine if it's odd or even
                 solution[i] = 'W';//using that data, we randomly assign every peg in the solution array to be white or black
                 numWhite++;//we also adjust our counter variables accordingly
             }
             else{
                 solution[i] = 'B';
                 numBlack++;
             }
         }

         string guess;
         bool correct = false;
         int k = 0;
         //Now that the code has been generated by our codemaker, time to let the player have at it
         while (k < guesses && !correct){//this while loop is basically a for loop that players can break out of early if they guess the code
             //I guess a break statement would have allowed me to just use a for loop, but I like having all of the break conditions right there in my loop header
             cout << "Enter a guess: ";//Prompt the user for a guess
             cin >> guess;
             while (!validGuess(guess)){//Once we have a guess, we validate it using the validGuess function. If it's not valid, we keep prompting until we get one that is
                 cout << "Invalid input. Please enter a four-character input consisting solely of B and W" << endl;
                 cout << "Enter a guess: ";
                 cin >> guess;
             }

             correct = hintGenerator(upperCaseifier(guess), solution, numWhite, numBlack);//now, take an all-uppercase version of the guess, the codemaker's code, and the total white and black pegs in the code
             //and run them through hintGenerator to create the hints, and also to determine if the codebreaker has successfully broken the code

             if(correct){//If they're right, then go ahead and tell them they one
                 cout << "That's exactly it, you win!" << endl;
             }
             else{//If they're not right, let them know, and tell them how many guesses they have left
                 cout << "That's not it, sadly! You have " << guesses-k << " guesses left!" << endl;
             }

             k++;//increment the iterator for our weird, janky for-loop
         }

         if(!correct){//if we ended up breaking out of the while loop due to running out of guesses, instead of by guessing correctly, print the loss statement
             cout << "You're all out of guesses! I win!" << endl;
             cout << "My code was ";
             for (int q = 0; q < 8; q++){//Also, we print out the code, to give users the catharsis of at least seeing the right code
                 cout << solution[q];
             }
             cout << "!" << endl;
         }

         cout << "Play again? (y/n) "; //Now that the game is complete, prompt the user to see if they want to play again
         string repeatchoice = "";
         cin >> repeatchoice;

         while(repeatchoice != "y" && repeatchoice != "Y" && repeatchoice != "n" && repeatchoice != "N"){//like all other user input, let's go ahead and validate this too
             cout << "Invalid input. Enter either 'y' or 'n': ";
             cin >> repeatchoice;
         }

         if(repeatchoice == "n" || repeatchoice == "N"){
             repeat = false;
         }//if our player says they don't wanna play anymore, we reverse repeat so we can break our do-while loop. If they do wanna continue, we do nothing, and let the loop...well, loop.

     }while(repeat);
 }
