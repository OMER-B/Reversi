#ifndef EX3_COMPUTER_H
#define EX3_COMPUTER_H

#include "player.h"

class Computer : public Player {
 public:
  // Constructor for the computer.
  explicit Computer(char symbol);

  // Destructor for Computer.
  ~Computer();

  // Calls the AI function from logic.
  int makeMove(Board &board, Logic &logic);
};

#endif //EX3_COMPUTER_H
