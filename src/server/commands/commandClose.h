#ifndef REVERSI_COMMANDCLOSE_H
#define REVERSI_COMMANDCLOSE_H

#include "command.h"
#include <iostream>
#include <vector>
using namespace std;

class CommandClose : public Command {
  void execute(vector<string> args);
};

#endif //REVERSI_COMMANDCLOSE_H