#include "consoleDisplay.h"

using namespace std;

ConsoleDisplay::~ConsoleDisplay() {}

void ConsoleDisplay::printBoard(Board *board) {
  int x = board->getX();
  int y = board->getY();
  cout << "+";

  for (int j = 0; j <= y; j++) {
    cout << "---+";
  }
  cout << endl;

  cout << "|   | ";
  for (int i = 0; i < x; i++) {
    cout << i + 1 << " | ";
  }
  cout << endl;
  cout << "+";

  for (int j = 0; j <= y; j++) {
    cout << "---+";
  }
  cout << endl;

  for (int i = 0; i < y; i++) {
    cout << "| " << i + 1 << " | ";
    for (int j = 0; j < x; j++) {
      cout << board->getCell(i, j)->getSymbol() << " | ";
    }
    cout << endl << "+";
    for (int k = 0; k <= y; k++) {
      cout << "---+";
    }
    cout << endl;
  }
}