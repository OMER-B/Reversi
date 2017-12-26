#ifndef REVERSI_COMMANDSTART_H
#define REVERSI_COMMANDSTART_H

#include "command.h"
#include <vector>
#include <iostream>
using namespace std;

class CommandStart : public Command {
  Lobby *lobby_;
  CommandStart(Lobby &lobby);
  void execute(vector<string> &args, int clientSocket);
};

#endif //REVERSI_COMMANDSTART_H