#ifndef REVERSI_COMMAND_H
#define REVERSI_COMMAND_H

#include <iostream>
#include <vector>

using namespace std;

class Command {
 public:
  virtual void execute(string arg, int clientSocket) = 0;
};

#endif //REVERSI_COMMAND_H