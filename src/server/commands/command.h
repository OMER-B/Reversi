#ifndef REVERSI_COMMAND_H
#define REVERSI_COMMAND_H

#include <iostream>
#include <vector>

using namespace std;

class Command {
 public:
  virtual void execute(vector<string> &args, int clientSocket) = 0;
};

#endif //REVERSI_COMMAND_H