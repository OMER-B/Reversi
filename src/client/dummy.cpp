#include <cstring>
#include <unistd.h>
#include "dummy.h"
#define BUFFER 128

int Dummy::makeMove(Board &board, Logic &logic, Display &display) {

  char enemyString[BUFFER];
  Point enemyPoint;
  memset(enemyString, 0, sizeof(enemyString));

  ssize_t n = read(clientSocket_, &enemyString, sizeof(enemyString));
  if (strcmp(enemyString, "go") == 0) {
    n = read(clientSocket_, &enemyString, sizeof(enemyString));
  }
  enemyPoint = Point(enemyString).decrease();
  if (n == -1) {
    throw "Error reading enemy point from socket";
  }
  if (strcmp(enemyString, "close") == 0) {
    close(clientSocket_);
    return 2;
  }
  if (strcmp(enemyString, "nomoves") == 0) {
    return 1;
  }
  logic.putNewCell(board, *this, enemyPoint);
  display.printBoard(&board);
  cout << "The enemy chose point " << enemyPoint << "." << endl;
  return 0;
}

void Dummy::setClientSocket(int clientSocket) {
  Dummy::clientSocket_ = clientSocket;
}

Dummy::Dummy(char symbol) : Player(symbol) {}
