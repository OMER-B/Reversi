#ifndef REVERSI_COMMANDPLAY_H
#define REVERSI_COMMANDPLAY_H

#include "command.h"
#include <iostream>
#include <vector>

using namespace std;
class CommandPlay : public Command {
  void execute(map<string, Room *> &lobby, vector<string> &args, int clientSocket);
};

#endif //REVERSI_COMMANDPLAY_H