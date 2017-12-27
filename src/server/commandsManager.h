#ifndef REVERSI_COMMANDSMANAGER_H
#define REVERSI_COMMANDSMANAGER_H

#include <map>
#include "command.h"
#include "commandJoin.h"
#include "commandStart.h"
#include "commandClose.h"
#include "commandPrint.h"
#include "HandleGame.h"
#include "Lobby.h"


class CommandsManager {
 private:
  map<string, Command * > commandsMap_;
 public:
  CommandsManager(Lobby *lobby, HandleGame *handleGame);

  bool isLegalCommand(string command, int client);
  void executeCommand(string command, vector<string> &args, int client);

  ~CommandsManager();
};

#endif //REVERSI_COMMANDSMANAGER_H