#include "commandsManager.h"

CommandsManager::CommandsManager() {
  commandsMap_["print"] = new CommandPrint();
  commandsMap_["close"] = new CommandClose();
  commandsMap_["start"] = new CommandStart();
  commandsMap_["join"] = new CommandJoin();
  commandsMap_["play"] = new CommandPlay();
}

CommandsManager::~CommandsManager() {
  map<string, Command *>::iterator it;
  for (it = commandsMap_.begin(); it != commandsMap_.end(); it++) {
    delete it->second;
  }
}

void CommandsManager::excecuteCommand(string command, vector<string> args) {
  Command *commandObj = commandsMap_[command];
  commandObj->execute(args);
}

