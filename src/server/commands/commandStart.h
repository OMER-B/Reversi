#ifndef REVERSI_COMMANDSTART_H
#define REVERSI_COMMANDSTART_H

#include "command.h"
#include <vector>
#include <iostream>
using namespace std;

class CommandStart : public Command {
  void execute(map<string, Room *> &lobby, vector<string> &args, int clientSocket);
};

#endif //REVERSI_COMMANDSTART_H