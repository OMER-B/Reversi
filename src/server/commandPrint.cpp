#include <unistd.h>
#include <cstring>
#include "commandPrint.h"

#define BUFFER 128
CommandPrint::CommandPrint(Lobby *lobby) {
  lobby_ = lobby;
}

void CommandPrint::execute(vector<string> &args, int clientSocket) {
  char list[BUFFER];
  if(lobby_->isEmpty()) {
    strcpy(list, "There are no games yet.\n");
  } else {
    vector<string> games = lobby_->getListOfRooms();
    //TODO turn this into one string and send
  }
  cout << "Sending list of games to socket: " << clientSocket << test << endl;
  ssize_t n = write(clientSocket, &list, sizeof(list));
  if(n == -1) {
    throw "Error sending list of games";
  }
  if(n==0) {
    throw "could not send list of games";
  }
}