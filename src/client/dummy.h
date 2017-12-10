#ifndef REVERSI_DUMMY_H
#define REVERSI_DUMMY_H

#include "player.h"
#include "logic.h"
#include "point.h"

class Dummy : public Player {
 private:
  // Holds the next dummy's move.
  Point enemyPoint_;

 public:
  // This will be the next dummy's move.
  void setEnemyPoint(const Point &enemyPoint);

  // Constructor for dummy.
  explicit Dummy(char symbol);

  // Makes move based on the "enemyPoint_" member.
  int makeMove(Board &board, Logic &logic, Display &display);
};

#endif //REVERSI_DUMMY_H
