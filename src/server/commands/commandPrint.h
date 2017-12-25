#ifndef REVERSI_COMMANDPRINT_H
#define REVERSI_COMMANDPRINT_H

#include "command.h"
#include <vector>
#include <iostream>
using namespace std;

class CommandPrint : public Command {
  void execute(map<string, Room *> &lobby, vector<string> &args, int clientSocket);
};

#endif //REVERSI_COMMANDPRINT_H