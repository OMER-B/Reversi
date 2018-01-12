#include <map>
#include <unistd.h>
#include "commandStart.h"

bool CommandStart::execute(string arg, int clientSocket) {

  pthread_mutex_t startLock;
  pthread_mutex_init(&startLock, NULL);
  string name = arg;

  if (lobby_->contains(name)) { // Room name already exists
    char invalid_name[] = "-1";
    cout << "Room start failed - name already exists. Socket: " << clientSocket
         << ", name: " << name << endl;
    ssize_t n = write(clientSocket, &invalid_name, sizeof(invalid_name));
    return true;
  }
  pthread_mutex_trylock(&startLock); //lock the adding and changing of a new room.
  Room *room = lobby_->createRoom(name);
  room->setName(name);
  room->setFirstClient(clientSocket);
  room->setStatus(Waiting);
  pthread_mutex_unlock(&startLock);
  char success[50] = "Successfully opened\n";
  ssize_t n = write(clientSocket, &success, sizeof(success));
  cout << "Opened room: " << name << endl;
  return false;
}

CommandStart::CommandStart(Lobby *lobby) : lobby_(lobby) {
}