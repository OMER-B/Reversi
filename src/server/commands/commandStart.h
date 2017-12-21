#ifndef REVERSI_COMMANDSTART_H
#define REVERSI_COMMANDSTART_H

#include "command.h"
#include <vector>
#include <iostream>
using namespace std;

class CommandStart : public Command {
  void execute(vector<string> args);
};

#endif //REVERSI_COMMANDSTART_H
