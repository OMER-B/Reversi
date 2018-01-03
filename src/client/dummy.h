#ifndef REVERSI_DUMMY_H
#define REVERSI_DUMMY_H

#include "player.h"
#include "logic.h"
#include "point.h"

class Dummy : public Player {
 private:
  int clientSocket_;
  // Holds the next dummy's move.

 public:
  Dummy(char symbol);

  // Sets the dummys socket.
  void setClientSocket(int clientSocket);

  // Makes move based on the "enemyPoint_" member.
  int makeMove(Board &board, Logic &logic, Display &display);
};

#endif //REVERSI_DUMMY_H
