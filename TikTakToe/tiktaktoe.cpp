#include "tiktaktoe.h"
#include <iostream>
#include <fstream>
#include <limits>
#include <exception>

using namespace std;

// Method for asking the player yes or no questions
static char getYorN() {
  cout << "Y or N\n";
  cout << "Input: ";
  char answer = '?';
  while (answer !='Y' && answer !='N') {
    if (!(cin>>answer)) {
      cin.clear();
      std::cin.ignore(std::numeric_limits<std::streamsize>::max());
    }
  }
  return answer;
}

// Tiktaktoe class definitions

Tiktaktoe::Tiktaktoe() :
  turnCount(0), 
  selection(0), 
  currentToken('?'), 
  currentState("         ") {}

const int Tiktaktoe::getInput() {
  // Input to string type to avoid inputs that would cause errors
  string input;
  cout << "Input: ";
  cin >> input;
  // check for save request
  if (input == "-save") {
    cout << R"(
You can only have one save file at a time.
Saving will overwrite the previous save.
Are you sure you want to save?
)";
    char answer = getYorN();
    if (answer == 'Y') 
      save();
    cout << "\nWould you like to continue your game?\n";
    answer = getYorN();
    if(answer == 'Y') {
      drawGame(this->currentState);
      cout << "Player " << turnCount % 2 + 1 << " make a selection.\n";
      return getInput();
    }
    else {
      cout << endl;
      return -1;
    }
  }
  if (input == "-load") {
    if (turnCount) {
      cout << "Would you like to save your game first?" << endl;
      char answer = getYorN();
      if (answer=='Y') 
        save();
    }
    return load();
  }
  if (input == "-quit") {
    return -1;
  }
  if (input.length() < 2 && input[0] > '0'-1 && input[0] < '9'+1) {
    return input[0] - '0';
  }
  else {
    cout << "Invalid Input!! Try again!\n";
    return getInput();
  }
}

const void Tiktaktoe::drawGame(const string &state) {
  cout << "     |     |     \n";
  cout << "  " << state[0] << "  |  " << state[1] << "  |  " << state[2] << "\n";
  cout << "_____|_____|_____\n";
  cout << "     |     |     \n";
  cout << "  " << state[3] << "  |  " << state[4] << "  |  " << state[5] << "\n";
  cout << "_____|_____|_____\n";
  cout << "     |     |     \n";
  cout << "  " << state[6] << "  |  " << state[7] << "  |  " << state[8] << "\n";
  cout << "     |     |     \n\n";
}

// I used selection as an input to reduce checks, since a new win condition will only ever be in relation to the most recent selection
const bool Tiktaktoe::checkWin(const string &stateOfBoard, const int &selection, const char &token) {
  bool result = false;
  unsigned short column = selection % 3, row = (selection - 1) / 3;

  /*
  bool left = column == 1;
  bool middleC = column == 2;
  bool right = column == 0;
  bool top = row == 0;
  bool middleR = row == 1;
  bool bottom = row == 2;
  */

  // check horizontal
  if (stateOfBoard[column + (3 * row)] == token && stateOfBoard[((column + 1) % 3) + (3 * row)] == token)
    result = true;

  // check vertical
  if (row == 0 && stateOfBoard[selection + 3 - 1] == token && stateOfBoard[selection + 6 - 1] == token)
    result = true;
  if (row == 1 && stateOfBoard[selection - 3 - 1] == token && stateOfBoard[selection + 3 - 1] == token)
    result = true;
  if (row == 2 && stateOfBoard[selection - 6 - 1] == token && stateOfBoard[selection - 3 - 1] == token)
    result = true;

  // check diagonals
  if (selection % 2) {
    // selection is on a diagonal
    if ((selection == 1 || selection == 5 || selection == 9) && stateOfBoard[0] == token && stateOfBoard[4] == token && stateOfBoard[8] == token)
      result = true;
    if ((selection == 3 || selection == 5 || selection == 7) && stateOfBoard[2] == token && stateOfBoard[4] == token && stateOfBoard[6] == token)
      result = true;
  }

  return result;
}
const void Tiktaktoe::save() {
  ofstream save;
  save.open("data.txt");
  string aux = currentState;
  for (int i=0; i<9; i++) {
    if (aux[i] == ' ') 
      aux[i] = '_';
  }
  save << turnCount << selection << currentToken << aux;
  save.close();
  cout << "Game saved!\n";
}

int Tiktaktoe::load() {
  ifstream save;
  char c_aux;
  string s_aux;
  
  save.open("data.txt");
  save.get(c_aux);
  turnCount = c_aux - '0';
  save.get(c_aux);
  selection = c_aux - '0';
  save.get(c_aux);
  currentToken = c_aux;
  save >> s_aux;
  for (int i=0; i<9; i++) {
    if (s_aux[i] == '_') 
      s_aux[i] = ' ';
  }
  currentState = s_aux;
  save.close();
  return getInput();
}

void Tiktaktoe::extLoad() {
  ifstream save;
  char c_aux;
  string s_aux;
  
  save.open("data.txt");
  save.get(c_aux);
  this->turnCount = c_aux - '0';
  save.get(c_aux);
  this->selection = c_aux - '0';
  save.get(c_aux);
  this->currentToken = c_aux;
  save >> s_aux;
  for (int i=0; i<9; i++) {
    if (s_aux[i] == '_') 
      s_aux[i] = ' ';
  }
  this->currentState = s_aux;
  save.close();
  drawGame(currentState);
}
void Tiktaktoe::introGame() {
  Tiktaktoe game;
      cout << R"(
* To save a game at any time, type: -save
* To load a game at any time, type: -load
* To quit,                    type: -quit
)";
  // define the selection inputs
  game.drawGame("789456123");
}
void Tiktaktoe::runGame() {
  // Inform the players how to save
  
  // start game
  for (/*turnCount*/; this->turnCount < 9 && checkWin(this->currentState, this->selection, this->currentToken) != true; this->turnCount++) {

    // prompt player to input their selection
    cout << "Player " << this->turnCount % 2 + 1 << " make a selection.\n";
    this->selection = getInput();
    // check if save and quit was invoked
    if (this->selection == -1)
      break;
    // flip selection grid input right side up for future math
    if (this->selection > 0 && this->selection < 4)
        this->selection += 6;
    else if (this->selection > 6)
        this->selection -= 6;
    
    // define player tokens
    this->currentToken = this->turnCount % 2 ? 'O' : 'X';

    // change the state of the game
    if (this->selection && this->currentState[this->selection - 1] == ' ') {
      this->currentState[this->selection - 1] = this->currentToken;
      drawGame(this->currentState); 
    }
    else {
      if (this->selection) {
        cout << "That space has already been selected.\n";
        cout << "Try another space.\n\n";
      }
      else {
        cout << "Zero isn't a space on the board silly.\n";
        cout << "Try again!\n\n";
      }
      this->turnCount--;
    }
  }

  // check final result and tell the players
  if (this->selection==-1) 
    return;
  if (checkWin(this->currentState, this->selection, this->currentToken))
      cout << "Congrat's! " << this->currentToken << " wins!!!\n";
  else
      cout << "It's a Draw!\n";
}