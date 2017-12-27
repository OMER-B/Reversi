#include <map>
#include <unistd.h>
#include "commandStart.h"

void CommandStart::execute(vector<string> &args, int clientSocket) {
  //TODO add mutex
  string name = args[0];
  if (lobby_->contains(name)) { // Room name already exists
    char invalid_name[50] = "Name is already taken (-1)\n";
    cout << "Room start failed - name already exists. Socket: " << clientSocket << ", name: " << name << endl;
    ssize_t n = write(clientSocket, &invalid_name, sizeof(invalid_name));
    return;
  }
  Room *room = lobby_->createRoom(name);

  room->setName(name);
  room->setFirstClient(clientSocket);
  room->setStatus(Waiting);
  char success[50] = "Successfully opened\n";
  ssize_t n = write(clientSocket, &success, sizeof(success));
  //TODO add mutex
  cout << "Room name: \'" << name << "\' (should be \'" << args[0] << "\')" << endl;
}

CommandStart::CommandStart(Lobby *lobby) : lobby_(lobby) {
}