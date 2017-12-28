#include <unistd.h>
#include <cstring>
#include "commandPrint.h"

#define BUFFER 128
CommandPrint::CommandPrint(Lobby *lobby) {
  lobby_ = lobby;
}

void CommandPrint::execute(string arg, int clientSocket) {
  char list[BUFFER];
  string listOfRooms;
  if (lobby_->isEmpty()) {
    strcpy(list, "There are no games yet.\n");
  } else {
    vector<string> games = lobby_->getListOfRooms();
    for (int i = 0; i < games.size(); i++) {
      listOfRooms += games[i] + ", ";
    }
    listOfRooms += "\n";
    strcpy(list, listOfRooms.c_str());
    //TODO turn this into one string and send
  }
  cout << "Sending to socket " << clientSocket << " list of rooms: " << listOfRooms << endl;
  ssize_t n = write(clientSocket, &list, sizeof(list));
  if (n == -1) {
    throw "Error sending list of games";
  }
  if (n == 0) {
    throw "could not send list of games";
  }
}