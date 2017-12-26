#include <map>
#include <unistd.h>
#include "commandStart.h"
void CommandStart::execute(vector<string> &args, int clientSocket) {
  string name = args[0];
  if (lobby_->contains(name)) { // Room name already exists
    int invalid_name = -1;
    cout << "Room start failed - name already exists. Socket: " << clientSocket << ", name: " << name << endl;
    ssize_t n = write(clientSocket, &invalid_name, sizeof(invalid_name));
    return;
  }
  Room *room;
  room->setName(name);
  room->setFirstClient(clientSocket);
  room->setStatus(Waiting);
  lobby_->addRoom(*room);
}

CommandStart::CommandStart(Lobby &lobby) : lobby_(&lobby) {
}