#ifndef REVERSI_COMMAND_H
#define REVERSI_COMMAND_H

#include <iostream>
#include <vector>
using namespace std;

class Command {
  virtual void execute(vector<string> args) = 0;
  virtual ~Command;
};

#endif //REVERSI_COMMAND_H
