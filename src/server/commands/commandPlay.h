#ifndef REVERSI_COMMANDPLAY_H
#define REVERSI_COMMANDPLAY_H

#include "command.h"
#include <iostream>
#include <vector>

using namespace std;
class CommandPlay : public Command {
  void execute(vector<string> args);

};

#endif //REVERSI_COMMANDPLAY_H
