#ifndef REVERSI_COMMAND_H
#define REVERSI_COMMAND_H

#include <iostream>
#include <vector>
#include "../server.h"
#include <map>

using namespace std;

class Command {
 public:
  virtual void execute(map<string, Room *> &lobby, vector<string> &args, int clientSocket) = 0;
  virtual ~Command;
};

#endif //REVERSI_COMMAND_H