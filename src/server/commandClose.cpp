#include <map>
#include <unistd.h>
#include "commandClose.h"

void CommandClose::execute(string arg, int clientSocket) {
  string name = arg;
  if (lobby_->contains(name)) {
    lobby_->removeRoom(name);
    close(lobby_->getRoom(name)->getFirstClient());
    close(lobby_->getRoom(name)->getSecondClient());
    lobby_->getRoom(name)->setStatus(Ended);
  }
}

CommandClose::CommandClose(Lobby *lobby) : lobby_(lobby) {

}
