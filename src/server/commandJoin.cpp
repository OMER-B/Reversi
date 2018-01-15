#include "commandJoin.h"
#include "../tools.h"

#include <thread_db.h>
#include <unistd.h>
#include <cstring>


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
    char success[BUFFER];
    strcpy(success, "Successfully joined");
    n = write(clientSocket, &success, sizeof(success));

    Task *game = new Task(handleGame_->play, room);
    pool_->addTask(game);
    
    return false;
  }
  char negative[] = "-1";
  n = write(clientSocket, &negative, sizeof(negative));
  return true;
}

CommandJoin::CommandJoin(Lobby *lobby,
                         HandleGame *handleGame,
                         ThreadPool *pool) {
  lobby_ = lobby;
  handleGame_ = handleGame;
  pool_ = pool;
}
