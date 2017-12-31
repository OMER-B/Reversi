#include <limits>
#include <iostream>
#include <cstring>
#include "human.h"
#include "logic.h"

#define BUFFER 15

using namespace std;

Human::Human(char symbol) : Player(symbol) {}

Human::~Human() {}

int Human::makeMove(Board &board, Logic &logic, Display &display) {
  display.printBoard(&board);
  char input[BUFFER];
  getInput(board, logic, display, input);
  if (strcmp(input, "close") == 0) {
    return 2;
  }
  if (strcmp(input, "nomoves") == 0) {
    return 1;
  }
  Point newCell = Point(input).decrease();
  if (board.inBoundaries(newCell)) {
    logic.putNewCell(board, *this, newCell);
    return 0;
  }
  return 1;
}

void Human::getInput(Board &board,
                     Logic &logic,
                     Display &display,
                     char *buffer) {
  memset(buffer, 0, sizeof(buffer));
  cout << getSymbol() << ", it's your turn." << endl;
  vector<Point> possibleMoves = logic.getOptionalMoves(board, *this);
  if (possibleMoves.empty()) {
    cout << "You don't have any moves. Type -1." << endl
         << "If enemy did not make a move type 0." << endl;
    strcpy(buffer, "nomoves");
    return;
  } else {
    cout << "Possible moves: ";
    for (vector<Point>::iterator it = possibleMoves.begin();
         it != possibleMoves.end(); ++it) {
      cout << *it;
    }
    cout << endl;
  }
  Point result;
  do {
    cout << "Enter your move 'row col':" << endl;
    cin.getline(buffer, sizeof(buffer));
  } while (!isvalid(possibleMoves, buffer));
}

bool Human::isvalid(vector<Point> possibleMoves, char *input) {
  if (strcmp(input, "close") == 0) {
    return true;
  }
  Point result = Point(input).decrease();
  for (vector<Point>::iterator it = possibleMoves.begin();
       it != possibleMoves.end(); ++it) {
    if (result == *it) {
      return true;
    }
  }
  return false;
}