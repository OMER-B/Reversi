#ifndef REVERSI_COMMANDJOIN_H
#define REVERSI_COMMANDJOIN_H

#include "command.h"
#include <iostream>
#include <vector>
using namespace std;

class CommandJoin : public Command {
  void execute(vector<string> args);
};

#endif //REVERSI_COMMANDJOIN_H
