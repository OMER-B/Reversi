#include "commandJoin.h"

#include <thread_db.h>
#include <unistd.h>

void CommandJoin::execute(vector<string> &args, int clientSocket) {
  string name = args[0];
  Room *room;
  cout << "Socket " << clientSocket << " requested to join room \'" + name + "\'" << endl;
  if (lobby_->contains(name)) {
    room = lobby_->getRoom(name);
    room->setSecondClient(clientSocket);
    room->setStatus(Active);
    char success[] = "Successfully joined\n";
    ssize_t n = write(clientSocket, &success, sizeof(success));
    if (room->getFirstClient() != 0 && room->getSecondClient() != 0) {
      thread_t id;
      pthread_create(&id, NULL, handleGame_->play, room);
      //TODO delete here the thread after opening it
    }
    cout << "Room name: " + lobby_->getRoom(name)->getName() << ", clients: " << lobby_->getRoom(name)->getFirstClient()
         << ", " << lobby_->getRoom(name)->getSecondClient() << ", status: " << lobby_->getRoom(name)->getStatus()
         << endl;
  } else {
    char invalid[] = "Room does not exist.\n";
    ssize_t n = write(clientSocket, &invalid, sizeof(invalid));
    char negative[] = "-1";
    n = write(clientSocket, &negative, sizeof(negative));
    cout << "Socket " << clientSocket << " asked to join a room which does not exist." << endl;
  }
  //TODO add mutex
}

CommandJoin::CommandJoin(Lobby *lobby, HandleGame *handleGame) {
  lobby_ = lobby;
  handleGame_ = handleGame;
}
