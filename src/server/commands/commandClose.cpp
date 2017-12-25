#include <map>
#include <unistd.h>
#include "commandClose.h"

void CommandClose::execute(map<string, Room *> &lobby, vector<string> &args, int clientSocket) {
  string name = args[0];
  if (lobby.find(name) == lobby.end()) {
    // not found
  } else {
    lobby.erase(name);
    close(lobby[name]->firstClient);
    close(lobby[name]->secondClient);
    // close thread (struct has its id)
  }
}