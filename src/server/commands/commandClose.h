#ifndef REVERSI_COMMANDCLOSE_H
#define REVERSI_COMMANDCLOSE_H

#include "command.h"
#include <iostream>
#include <vector>
using namespace std;

class CommandClose : public Command {
  void execute(map<string, Room *> &lobby, vector<string> &args, int clientSocket);
};

#endif //REVERSI_COMMANDCLOSE_H