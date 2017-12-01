#include "computer.h"
#include "logic.h"

Computer::Computer(char symbol) : Player(symbol) {}

Computer::~Computer() {}

int Computer::makeMove(Board &board, Logic &logic) {
  Point move = logic.aiMove(*this, board);
  if (move.getY() == -1 && move.getX() == -1) {
    cout << getSymbol() << " doesn't have any moves. Trying next player."
         << endl;
    return 1;
  }
  cout << "The computer placed '" << getSymbol() << "' on "
       << move << "." << endl;
  return 0;
}


