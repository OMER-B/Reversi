#ifndef REVERSI_COMMANDSMANAGER_H
#define REVERSI_COMMANDSMANAGER_H

#include <map>
#include "../Lobby.h"
#include "commandClose.h"
#include "commandPrint.h"
#include "commandJoin.h"
#include "commandStart.h"

class CommandsManager {
 private:
  map<string, Command *> commandsMap_;
 public:
  CommandsManager();

  void excecuteCommand(string command, vector<string> &args, int client, map<string, Room *> &lobby);

  ~CommandsManager();
};

#endif //REVERSI_COMMANDSMANAGER_H