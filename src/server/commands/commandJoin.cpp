#include <map>
#include "commandJoin.h"
void CommandJoin::execute(vector<string> &args, int clientSocket) {
  string name = args[0];
  Room *room;
  if (lobby_->contains(name)) {
    room = lobby_->getRoom(name);
    room->setFirstClient(clientSocket);
    room->setStatus(Active);
    // int pthread_create(pthread_t *thread, const pthread_attr_t *attr, void *(*start_routine)(void *), void *args);
  }

  if (room->getFirstClient() != 0 && room->getSecondClient() != 0) {
    // start game
  }
}
CommandJoin::CommandJoin(Lobby &lobby) : lobby_(&lobby) {

}