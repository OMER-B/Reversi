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

class CommandsManager { // class is singleton
 private:
  CommandsManager(Lobby *lobby, HandleGame *handleGame);
  map<string, Command *> commandsMap_;
  static CommandsManager *instance_;

 public:
  static CommandsManager *getInstance(Lobby *lobby, HandleGame *handleGame);
  static CommandsManager *getInstance();
  bool isLegalCommand(string command, int client);
  void executeCommand(string command, string arg, int client);
  std::pair<string, string> seperate(string input);
  ~CommandsManager();
};

#endif //REVERSI_COMMANDSMANAGER_H