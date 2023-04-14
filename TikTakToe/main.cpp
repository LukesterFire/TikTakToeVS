#include "tiktaktoe.h"
#include <iostream>
#include <fstream>
#include <limits>

struct dirent *ent;

static bool menuDisplayed = false;

int main() {
  char input[10];
  string newG = "-New Game";
  string load = "-Load";
  string quit = "-Quit";
  while (input != quit) {
    if (!menuDisplayed) {
      std::cout << R"(TIK TAK TOE
* A keypad is recommended to play this game
    
    Enter a selection from the following options
)";
    /*
    if (saveFileAvailable) {
      std::cout << "-Continue";
    }
    */
      std::cout << R"(
-New Game
-Load
-Quit


Input: )";
    }
    menuDisplayed = true;
    // while (/*there is stuff in cin*/) {
    //   string aux;
    //   cin >> aux;
    //   input += aux;
    // }
    std::cin.getline(input, 10);
    cin.clear();
    //cin.ignore(numeric_limits<streamsize>::max(), '\n');
    if(input == newG) {
      Tiktaktoe game;
      game.introGame();
      game.runGame();
      menuDisplayed = false;
    }
    if(input==load) {
      Tiktaktoe game;
      game.extLoad();
      game.runGame();
      menuDisplayed = false;
    }
  }
}