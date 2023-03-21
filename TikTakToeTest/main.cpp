#include <iostream>
#include <vector>

using namespace std;

// create a function to get input from the players
int getInput() {
    // input to string type to avoid inputs that would cause errors
    string str;
    cin >> str;
    if (str.length() < 2 && str[0] > 47 && str[0] < 58) {
        return str[0] - '0';
    }
    else {
        cout << "Invalid Input!! Try again!\n";
        cin.clear();
        return getInput();
    }
}

// create a funtion to draw the game
void drawGame(string state) {
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
bool checkWin(string stateOfBoard, unsigned short selection, char token) {
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
    char currentPlayerToken = '?';

    // start game
    for (unsigned short turnCount = 0; turnCount < 9 && checkWin(currentState, selection, currentPlayerToken) != true; turnCount++) {

        // who's turn is it?
        unsigned short turn = turnCount%2;

        // prompt player to input their selection
        cout << "Player " << turn + 1 << " make a selection.\n";
        selection = getInput();

        // flip selection grid input upside down for future math
        if (selection > 0 && selection < 4)
            selection += 6;
        else if (selection > 6)
            selection -= 6;
        
        enum TokenEnum { X ='X', O = 'O'};

        // define player tokens
        if (!turn)
            currentPlayerToken = TokenEnum::X;
        else
            currentPlayerToken = TokenEnum::O;

        // change the state of the game
        if (selection && currentState[selection - 1] == ' ') {
            currentState[selection - 1] = currentPlayerToken;
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
    if (checkWin(currentState, selection, currentPlayerToken))
        cout << "Congrat's! " << currentPlayerToken << " wins!!!\n";
    else
        cout << "It's a Draw!\n";
}