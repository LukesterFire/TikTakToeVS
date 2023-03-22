#include <iostream>

using namespace std;

// create a function to get input from the players
const int getInput() {
  // input to string type to avoid inputs that would cause errors
  string str;
  cin >> str;
  if (str.length() < 2 && str[0] > '0'-1 && str[0] < '9'+1) {
    return str[0] - '0';
  }
  else {
    cout << "Invalid Input!! Try again!\n";
    return getInput();
  }
}

// create a funtion to draw the game
void drawGame(const string &state) {
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

// create a function to check if someone won
// used selection as input to reduce checks since a new win condition will only ever be in relation to the most recent selection
bool checkWin(const string &stateOfBoard, const int &selection, const char &token) {
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

int main() {
  // welcome the players!
  cout << "Enjoy this game of TIK TAK TOE\n";

  // define the selection inputs
  string currentState = "789456123";
  drawGame(currentState);

  // clear the game board and intitialize important variables
  currentState = "         ";
  int selection = 0;
  char currentToken = '?';

  // start game
  for (unsigned short turnCount = 0; turnCount < 9 && checkWin(currentState, selection, currentToken) != true; turnCount++) {

    // who's turn is it?
    unsigned short turn = turnCount % 2;

    // prompt player to input their selection
    cout << "Player " << turn + 1 << " make a selection.\n";
    selection = getInput();

    // flip selection grid input right side up for future math
    if (selection > 0 && selection < 4)
        selection += 6;
    else if (selection > 6)
        selection -= 6;
    
    // define player tokens
    enum token:char { X ='X', O = 'O'};
    switch (turn) {
      case(0) : currentToken = token::O; break;
      case(1) : currentToken = token::X; break;
    }

    // change the state of the game
    if (selection && currentState[selection - 1] == ' ') {
      currentState[selection - 1] = currentToken;
      drawGame(currentState);
    }
    else {
      if (selection) {
        cout << "That space has already been selected.\n";
        cout << "Try another space.\n\n";
      }
      else {
        cout << "Zero isn't a space on the board silly.\n";
        cout << "Try again!\n\n";
      }
      turnCount--;
    }
  }

  // check final result and tell the players
  if (checkWin(currentState, selection, currentToken))
      cout << "Congrat's! " << currentToken << " wins!!!\n";
  else
      cout << "It's a Draw!\n";
}