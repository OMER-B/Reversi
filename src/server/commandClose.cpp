#include <map>
#include <unistd.h>
#include "commandClose.h"

bool CommandClose::execute(string arg, int clientSocket) {
  string name = arg;
  if (lobby_->contains(name)) {
    lobby_->getRoom(name)->setStatus(Ended);
    close(lobby_->getRoom(name)->getFirstClient());
    close(lobby_->getRoom(name)->getSecondClient());
    lobby_->removeRoom(name);
    cout << "Closed room " << name << endl;
  }
  return false;
}

CommandClose::CommandClose(Lobby *lobby) : lobby_(lobby) {

}