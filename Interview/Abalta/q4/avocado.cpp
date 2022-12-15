/* Author: Angela To
 * Date: 11/29/14
 * File Name: avocado.cpp
 * Description: Question 4
 */

#include <iostream>
#include <string>
#include <unistd.h>
using namespace std;

static int num_avo = 0;
static int end_game = 0;

void print_instr();
void remove_item(std::string player, int num_items);
void game_over(string player);
void fill_the_bucket();
void play_prompt(std::string player);
void bucket_update();
void computer_decide();
std::string who_goes_first();






/* Avocado game DRIVER
 */
int main(int argc, char** argv) {
  std::string first_player;
  print_instr();  

  fill_the_bucket();
 
  first_player = who_goes_first();

  play_prompt(first_player); 

  // Game Over!
  return 0;
}


/* Simple function to display game instructions on start
 */
void print_instr() {
  cout << endl;
  cout << "///////////////////////////////////////////////////////" << endl;
  cout << endl;
  cout << "\t\t AVOCADO BUGKET!" << endl; 
  cout << endl;
  cout << "Directions: Input the number of avocados in the bucket. "<< endl;  
  cout << "You will be playing against the computer. Each round, "  << endl;  
  cout << "select how many avocados you would like to take out of " << endl;
  cout << "the bucket. The player that takes the last avocado out " << endl;
  cout << "of the bucket wins."     << endl;
  cout << endl;
  cout << "///////////////////////////////////////////////////////" << endl;
  cout << endl;
}


/* Initialize the bucket with avocados - the player 
 * chooses how many to fill 
 */
void fill_the_bucket() {
  cout << "How many avocados to begin? ";
  cin >> num_avo;
  while (num_avo < 1) {
      cout << endl;
      cout << "Please enter more than 1 avocado to begin!" << endl;
      cout << "How many avocados to begin? ";
      cin >> num_avo;
  }
  cout << "Number of avocados in bucket: " << num_avo << endl; 
}


/* If num avo in bucket multp. 3 , player begins
 */
std::string who_goes_first() {
  std::string first_player;
  if (num_avo < 3) first_player = "Computer";
  else if (num_avo % 3 == 0)
      first_player = "Player";
  else first_player = "Computer";
  cout << endl << first_player << " goes first" << endl;
  return first_player;  
}


/* Encapsulates the computer's decision making alg
 */
void computer_decide() {
   sleep(1); // shhh... the computer is thinking ...
   // want to leave opponent with a multple of 3 avo
   int num_to_sub = num_avo%3;
   if (num_to_sub != 0) remove_item("Computer", num_to_sub);
   // No other choice but to remove the least, 1
   else remove_item("Computer", 1);
}


/* Prompt the current player until no more avocados
 * remain
 */
void play_prompt(std::string player) {
  if (!end_game) {
      if (player.compare("Computer") == 0) {
          computer_decide();
          play_prompt("Player");
      }
      // Pleayer goes 
      else {
          int num_to_remove;
          cout << endl;
          cout << "Player's turn! ... Number of avocadoes to remove: ";
          cin >> num_to_remove;
          // Check that player's input is valid, else reprompt
          if (num_to_remove > 2 || num_to_remove < 1) {
              cout << "Can only remove one or two avocados at a time." << endl;
              cout << "Please try again." << endl;
              play_prompt("Player"); 
          }
          remove_item("Player", num_to_remove);
          play_prompt("Computer");
      }
  }
}


/* Simple function to output # avocados remaining
 */
void bucket_update() {
   cout << "NUM AVO REMAINING: " << num_avo << endl;
}


/* Remove avocados from bucket, determine remaining
 * number of avocados
 */
void remove_item(string player, int num_items) {
      if (num_avo < num_items) {
          cout << "There are only " << num_avo << " avocados to be removed" << endl;
          return;
      }
      else if (num_avo >= num_items) { // Ensure that there are enough avo to be removed
          cout << endl;
          cout << player << " takes " << num_items << " avocadoes out of the bucket." << endl;
          num_avo -= num_items;
          bucket_update();
          // Last avo removed ?
          if (num_avo == 0) game_over(player);
    }
}


/* Game over, end game
 */
void game_over(string player) {
  cout << endl;
  cout << player << " has removed the last avocado." << endl;
  cout << player << " wins the game!" << endl; 
  cout << endl;
  cout << "GAME OVER!" << endl;
  end_game = 1;
}


