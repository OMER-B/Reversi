#include "commandsManager.h"

CommandsManager::CommandsManager(Lobby *lobby, HandleGame *handleGame) {
  commandsMap_["print"] = new CommandPrint(lobby);
  commandsMap_["close"] = new CommandClose(lobby);
  commandsMap_["start"] = new CommandStart(lobby);
  commandsMap_["join"] = new CommandJoin(lobby, handleGame);
}

CommandsManager::~CommandsManager() {
  map<string, Command *>::iterator it;
  for (it = commandsMap_.begin(); it != commandsMap_.end(); it++) {
    delete it->second;
  }
}

void CommandsManager::executeCommand(string command, vector<string> &args, int client) {
  cout << "command:" << command << endl;
  commandsMap_[command]->execute(args, client);
  cout << "end" << endl;
}