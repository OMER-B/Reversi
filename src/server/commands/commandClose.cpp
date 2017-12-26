#include <map>
#include <unistd.h>
#include "commandClose.h"

void CommandClose::execute(vector<string> &args, int clientSocket) {
  string name = args[0];
  if (lobby_->contains(name)) {
    lobby_->removeRoom(name);
    close(lobby_->getRoom(name)->getFirstClient());
    close(lobby_->getRoom(name)->getSecondClient());
  }
}

CommandClose::CommandClose(Lobby &lobby) : lobby_(&lobby) {

}
