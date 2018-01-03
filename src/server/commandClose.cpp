#include <map>
#include <unistd.h>
#include "commandClose.h"

bool CommandClose::execute(string arg, int clientSocket) {

  pthread_mutex_t closeLock;
  pthread_mutex_init(&closeLock, NULL);

  string name = arg;
  Room *room;
  if (lobby_->contains(name)) {
    pthread_mutex_trylock(&closeLock);

    room = lobby_->getRoom(name);
    room->setStatus(Ended);
    close(room->getFirstClient());
    close(room->getSecondClient());
    for (vector<pthread_t *>::iterator it = threads_->begin();
         it != threads_->end(); ++it) {
      if (**it == room->getThreadID()) {
        threads_->erase(it);
        cout << "Removed thread from vector" << endl;
      }
    }
    lobby_->removeRoom(name);
    pthread_mutex_unlock(&closeLock);

    cout << "Closed room " << name << endl;
  }
  return false;
}

CommandClose::CommandClose(Lobby *lobby, vector<pthread_t *> *threads) : lobby_(
    lobby) {
  threads_ = threads;
}