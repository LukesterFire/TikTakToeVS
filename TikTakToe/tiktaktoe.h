#pragma once
#include <string>


using namespace std;

// Method for asking the player yes or no questions
static char getYorN();

class Tiktaktoe {
private:
  int turnCount;
  int selection;
  char currentToken;
  string currentState;
public:  
  Tiktaktoe();
private:
  const int getInput();
  const void drawGame(const string &state);
  const bool checkWin(const string &stateOfBoard, const int &selection, const char &token);
  const void save();
  int load();
public:
  void extLoad();
  void introGame();
  void runGame();
};