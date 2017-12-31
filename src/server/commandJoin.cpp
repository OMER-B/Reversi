#include "commandJoin.h"

#include <thread_db.h>
#include <unistd.h>

bool CommandJoin::execute(string arg, int clientSocket) {
  string name = arg;
  Room *room;
  cout << "Socket " << clientSocket
       << " requested to join room \'" + name + "\'" << endl;
  if (lobby_->contains(name)) {
    pthread_mutex_t joinLock;
    pthread_mutex_trylock(&joinLock);
    bool canJoin = lobby_->getRoom(name)->getStatus() == Waiting;
    pthread_mutex_unlock(&joinLock);
    if (canJoin) {
      room = lobby_->getRoom(name);
      room->setSecondClient(clientSocket);
      room->setStatus(Active);
      char success[] = "Successfully joined\n";
      ssize_t n = write(clientSocket, &success, sizeof(success));
      if (room->getFirstClient() != 0 && room->getSecondClient() != 0) {
        thread_t id;
        pthread_create(&id, NULL, handleGame_->play, room);
        pthread_join(id, NULL);
        //TODO delete here the thread after opening it
      }
      cout << "Room name: " + lobby_->getRoom(name)->getName() << ", clients: "
           << lobby_->getRoom(name)->getFirstClient()
           << ", " << lobby_->getRoom(name)->getSecondClient() << ", status: "
           << lobby_->getRoom(name)->getStatus()
           << endl;
    } else {
      char invalid[] = "Room does not exist.\n";
      ssize_t n = write(clientSocket, &invalid, sizeof(invalid));
      return true;
    }
  } else {
    char invalid[] = "Room does not exist.\n";
    ssize_t n = write(clientSocket, &invalid, sizeof(invalid));
    char negative[] = "-1";
    n = write(clientSocket, &negative, sizeof(negative));
    return true;
  }
  return false;
}

CommandJoin::CommandJoin(Lobby *lobby, HandleGame *handleGame) {
  lobby_ = lobby;
  handleGame_ = handleGame;
}
