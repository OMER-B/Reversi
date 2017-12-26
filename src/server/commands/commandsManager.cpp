#include "commandsManager.h"

CommandsManager::CommandsManager() {
  commandsMap_["print"] = new CommandPrint();
  commandsMap_["close"] = new CommandClose(lobby);
  commandsMap_["start"] = new CommandStart(lobby);
  commandsMap_["join"] = new CommandJoin(lobby);
}

CommandsManager::~CommandsManager() {
  map<string, Command *>::iterator it;
  for (it = commandsMap_.begin(); it != commandsMap_.end(); it++) {
    delete it->second;
  }
}

void CommandsManager::excecuteCommand(string command, vector<string> &args, int client, map<string, Room *> &lobby) {
  Command *commandObj = commandsMap_[command];
  commandObj->execute(lobby, args, client);
}