#ifndef REVERSI_COMMANDJOIN_H
#define REVERSI_COMMANDJOIN_H

#include "command.h"
#include <iostream>
#include <vector>
using namespace std;

class CommandJoin : public Command {
  Lobby *lobby_;
  CommandJoin(Lobby &lobby);
  void execute(vector<string> &args, int clientSocket);
};

#endif //REVERSI_COMMANDJOIN_H