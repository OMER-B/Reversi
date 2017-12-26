#ifndef REVERSI_COMMANDPRINT_H
#define REVERSI_COMMANDPRINT_H

#include "command.h"
#include "Lobby.h"
#include <vector>
#include <iostream>
using namespace std;

class CommandPrint : public Command {
private:
  Lobby *lobby_;
public:
  CommandPrint(Lobby * lobby);
  void execute(vector<string> &args, int clientSocket);
};

#endif //REVERSI_COMMANDPRINT_H