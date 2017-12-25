#include <map>
#include "commandStart.h"
void CommandStart::execute(map<string, Room *> &lobby, vector<string> &args, int clientSocket) {
  Room *room;
  string name = args[0];
  if (lobby.find(name) == lobby.end()) {
    // WRITE -1
  } else {
    room->firstClient = clientSocket;
    room->name = name;
    lobby[name] = room;
  }
}