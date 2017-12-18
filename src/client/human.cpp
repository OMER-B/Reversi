#include <limits>
#include <iostream>
#include "human.h"
#include "logic.h"

using namespace std;

Human::Human(char symbol) : Player(symbol) {}

Human::~Human() {}

int Human::makeMove(Board &board, Logic &logic, Display &display) {
  Point newCell = getInput(board, logic, display);
  if (newCell.getX() != -1) {
    logic.putNewCell(board, *this, newCell);
    return 0;
  }
  return 1;
}

Point Human::getInput(Board &board, Logic &logic, Display &display) {
  display.printBoard(&board);
  cout << getSymbol() << ", it's your turn." << endl;
  vector<Point> possibleMoves = logic.getOptionalMoves(board, *this);
  if (possibleMoves.empty()) {
    cout << "You don't have any moves. Trying next player." << endl;
    return Point(-1, -1);
  }
  cout << "Possible moves: ";
  for (vector<Point>::iterator it = possibleMoves.begin();
       it != possibleMoves.end(); ++it) {
    cout << *it;
  }
  int moveX = -1, moveY = -1;
  while (true) {
    cout << endl << "Enter your move 'row col': ";
    cin >> moveX >> moveY;

    // Check if input is an integer.
    if (cin.fail()) {
      cin.clear();
      cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    // Minus one for indexes.
    moveX--;
    moveY--;
    if (board.inBoundaries(moveX, moveY)
        && logic.isOptionInList(Point(moveX, moveY), possibleMoves)) {
      break;
    }
  }
  return Point(moveX, moveY);
}