#include "commandJoin.h"

#include <thread_db.h>
#include <unistd.h>

void CommandJoin::execute(vector<string> &args, int clientSocket) {
  string name = args[0];
  Room *room;
  if (lobby_->contains(name)) {
    room = lobby_->getRoom(name);
    room->setSecondClient(clientSocket);
    room->setStatus(Active);
    if (room->getFirstClient() != 0 && room->getSecondClient() != 0) {
      thread_t id;

      char msg[] = "good";
      ssize_t n = write(room->getFirstClient(), &msg, sizeof(msg));
      n = write(room->getSecondClient(), &msg, sizeof(msg));
      pthread_create(&id, NULL, handleGame_->play, room);
      //TODO delete here the thread after opening it
    }
  }
  //TODO add mutex
}

CommandJoin::CommandJoin(Lobby *lobby, HandleGame * handleGame){
  lobby_ = lobby;
  handleGame_ = handleGame;
}
