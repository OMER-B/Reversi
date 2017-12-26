#ifndef REVERSI_COMMANDCLOSE_H
#define REVERSI_COMMANDCLOSE_H

#include "command.h"
#include "../Lobby.h"
#include <iostream>
#include <vector>
using namespace std;

class CommandClose : public Command {
private:
  Lobby *lobby_;
public:
  CommandClose(Lobby *lobby);

  void execute(vector<string> &args, int clientSocket);
};

#endif //REVERSI_COMMANDCLOSE_H