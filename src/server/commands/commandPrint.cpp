#include <unistd.h>
#include "commandPrint.h"
void CommandPrint::execute(map<string, Room *> &lobby, vector<string> &args, int clientSocket) {
  string listOfGames;
  map<string, Room *>::iterator it;
  for (it = lobby.begin(); it != lobby.end(); it++) {
    if (it->second->status == Waiting) {
      listOfGames += it->second->name + "\n";
    }
  }
  ssize_t n = write(clientSocket, &listOfGames, listOfGames.size());
}