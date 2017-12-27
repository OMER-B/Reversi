#include <unistd.h>
#include <cstring>
#include "commandPrint.h"

#define BUFFER 128
CommandPrint::CommandPrint(Lobby *lobby) {
  lobby_ = lobby;
}

void CommandPrint::execute(vector<string> &args, int clientSocket) {
  char test[BUFFER];
  strcpy(test, "testing");
  cout << "Sending list of games to socket: " << clientSocket << test << endl;
  ssize_t n = write(clientSocket, &test, sizeof(test));
  if(n == -1) {
    throw "Error sending list of games";
  }
  if(n==0) {
    throw "could not send list of games";
  }
}