#include "commandJoin.h"

#include <thread_db.h>
#include <unistd.h>

bool CommandJoin::execute(string name, int clientSocket) {
  pthread_mutex_t joinLock;
  pthread_mutex_init(&joinLock, NULL);
  Room *room;
  ssize_t n;
  cout << "Socket " << clientSocket
       << " requested to join room \'" + name + "\'" << endl;
  if ((lobby_->contains(name))
      && (lobby_->getRoom(name)->getStatus() == Waiting)) {
    pthread_mutex_trylock(&joinLock);
    room = lobby_->getRoom(name);
    room->setSecondClient(clientSocket);
    room->setStatus(Active);
    pthread_mutex_unlock(&joinLock);
    char success[] = "Successfully joined";
    n = write(clientSocket, &success, sizeof(success));
    handleGame_->play(room);
    thread_t id;
    pthread_create(&id, NULL, handleGame_->play, room);
    pthread_join(id, NULL);
    threads_->push_back(&id);
    return false;
  }
  char negative[] = "-1";
  n = write(clientSocket, &negative, sizeof(negative));
  return true;
}

CommandJoin::CommandJoin(Lobby *lobby,
                         HandleGame *handleGame,
                         vector<pthread_t *> *threads) {
  lobby_ = lobby;
  handleGame_ = handleGame;
  threads_ = threads;
}
