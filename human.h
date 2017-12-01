#ifndef EX2NEW_PLAYER_H
#define EX2NEW_PLAYER_H

#include "player.h"

class Logic;
class Board;

class Human : public Player {
 public:
  // Constructor for human.
  explicit Human(char symbol);

  // Destructor for Human.
  virtual ~Human();

  // Gets input from the user and calls logic to make the move.
  int makeMove(Board &board, Logic &logic);
};

#endif //EX2NEW_PLAYER_H
