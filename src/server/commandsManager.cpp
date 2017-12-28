#include <unistd.h>
#include "commandsManager.h"
#include "commandPlay.h"
#include <sstream>

CommandsManager *CommandsManager::instance_ = 0;
CommandsManager::CommandsManager(Lobby *lobby, HandleGame *handleGame) {
  commandsMap_["join"] = new CommandJoin(lobby, handleGame);
  commandsMap_["list_games"] = new CommandPrint(lobby);
  commandsMap_["close"] = new CommandClose(lobby);
  commandsMap_["start"] = new CommandStart(lobby);
  commandsMap_["play"] = new CommandPlay();
}

CommandsManager::~CommandsManager() {
  map<string, Command *>::iterator it;
  for (it = commandsMap_.begin(); it != commandsMap_.end(); it++) {
    delete it->second;
  }
  delete instance_;
}

void CommandsManager::executeCommand(string command, vector<string> &args, int client) {
  cout << "Received command: " << command << " from socket: " << client << endl;
  commandsMap_[command]->execute(args, client);
}
bool CommandsManager::isLegalCommand(string command, int client) {
  if (commandsMap_.find(command) == commandsMap_.end()) {
    cout << "Unrecognized command received: " << command << endl;
    char invalid[20] = "Invalid command!";
    ssize_t n = write(client, &invalid, sizeof(invalid));
    return false;
  }
  return true;
}

CommandsManager *CommandsManager::getInstance(Lobby *lobby, HandleGame *handleGame) {
  if (!instance_) {
    instance_ = new CommandsManager(lobby, handleGame);
  }
  return instance_;
}
CommandsManager *CommandsManager::getInstance() {
  if (!instance_) {
    return NULL;
  }
  return instance_;
}

std::pair<string, vector<string> > CommandsManager::seperate(string input) {
  stringstream stream(input);
  string command;
  string buffer;
  vector<string> args;

  stream >> command;
  while (stream >> buffer) {
    args.push_back(buffer);
  }
  return pair<string, vector<string> >(command, args);
}
